#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"

void MapToolScene::PushCommand(ICommand* command) {
	command->Execute();
	mCommandList.emplace(command);
}

void MapToolScene::Undo() {
	if (mCommandList.size() == 0)
		return;

	mReCommandList.emplace(mCommandList.top());
	mCommandList.top()->Undo();
	mCommandList.pop();
}

void MapToolScene::Redo() {
	if (mReCommandList.size() == 0)
		return;

	mCommandList.emplace(mReCommandList.top());
	mReCommandList.top()->Redo();
	mReCommandList.pop();
}

void MapToolScene::Fill()
{
	//ä�� Ÿ���� ���� ���� ���
	if (mSelectIndex.size() > 0)
	{
		vector<TileSave> save;

		if(mCurrentPallete.Layer == TileLayer::Ground)
		{
			for (int i = 0; i < mSelectIndex.size(); ++i)
			{
				TileSave temp;
				temp.Set(mGroundList[mSelectIndex[i].y][mSelectIndex[i].x]->GetImage()->GetKeyName(),
					mGroundList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexX(),
					mGroundList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexY(),
					mSelectIndex[i].x, mSelectIndex[i].y);
				save.push_back(temp);
			}
			IBrushTile* command = new IBrushTile(mGroundList, save, mCurrentPallete);
			PushCommand(command);
		}
		else if (mCurrentPallete.Layer == TileLayer::Deco)
		{
			for (int i = 0; i < mSelectIndex.size(); ++i)
			{
				TileSave temp;
				temp.Set(mDecoList[mSelectIndex[i].y][mSelectIndex[i].x]->GetImage()->GetKeyName(),
					mDecoList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexX(),
					mDecoList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexY(),
					mSelectIndex[i].x, mSelectIndex[i].y);
				save.push_back(temp);
			}
			IBrushTile* command = new IBrushTile(mDecoList, save, mCurrentPallete);
			PushCommand(command);
		}
		else if (mCurrentPallete.Layer == TileLayer::Item)
		{
			for (int i = 0; i < mSelectIndex.size(); ++i)
			{
				TileSave temp;
				temp.Set(mItemList[mSelectIndex[i].y][mSelectIndex[i].x]->GetImage()->GetKeyName(),
					mItemList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexX(),
					mItemList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexY(),
					mSelectIndex[i].x, mSelectIndex[i].y);
				save.push_back(temp);
			}
			IBrushTile* command = new IBrushTile(mItemList, save, mCurrentPallete);
			PushCommand(command);
		}
		else if (mCurrentPallete.Layer == TileLayer::GameObject)
		{
			for (int i = 0; i < mSelectIndex.size(); ++i)
			{
				TileSave temp;
				temp.Set(mObjectList[mSelectIndex[i].y][mSelectIndex[i].x]->GetImage()->GetKeyName(),
					mObjectList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexX(),
					mObjectList[mSelectIndex[i].y][mSelectIndex[i].x]->GetFrameIndexY(),
					mSelectIndex[i].x, mSelectIndex[i].y);
				save.push_back(temp);
			}
			IBrushTile* command = new IBrushTile(mObjectList, save, mCurrentPallete);
			PushCommand(command);
		}
		mFillMod = false;
	}
	//ä�� Ÿ�� ������ ������ ���
	else
	{
		//��带 ��ȯ �� ��, MapToolScene::Update���� mFillMod == true�϶� Paint()�� ȣ���Ѵ�
		mFillMod = !mFillMod;
	}
}

void MapToolScene::Paint()
{
	//ä��� ���� �������� Ŭ��
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
		int indexX = (_mousePosition.x - mMoveX) / TileSize + mMinIndexX;
		int indexY = (_mousePosition.y - mMoveY) / TileSize + mMinIndexY;

		//�������� ���� �� �ִ� �ε������� üũ
		if (indexX >= mMinIndexX && indexX < mMinIndexX + TileCountX && indexX < mMaxSizeX &&
			indexY >= mMinIndexY && indexY < mMinIndexY + TileCountY && indexY < mMaxSizeY)
		{


			//�������� ������ ���� ������ �ȷ�Ʈ�� �ϳ��� ���� ������
			if ((mGroundList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
				mGroundList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
				mGroundList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY)
				)
			{
				if (mCurrentPallete.Layer == TileLayer::Ground)
					FloodFill(mGroundList,indexX,indexY);
				else if (mCurrentPallete.Layer == TileLayer::Deco)
					FloodFill(mDecoList, indexX, indexY);
				else if (mCurrentPallete.Layer == TileLayer::Item)
					FloodFill(mItemList, indexX, indexY);
				else if (mCurrentPallete.Layer == TileLayer::GameObject)
					FloodFill(mObjectList, indexX, indexY);
			}
		}
	}
}

void MapToolScene::FloodFill(vector<vector<Tile*>>& tileList, int indexX, int indexY)
{
	queue<Tile*> tempQueue;	//floodfill�� ť
	vector<TileSave> saveVector;	//Ÿ�� ������ ���庤��

	tempQueue.emplace(tileList[indexY][indexX]);
	Tile init = *mGroundList[indexY][indexX];

	//�˻簡 ����ɶ�����
	while (tempQueue.empty() == false) {
		Tile* check = tempQueue.front();
		tempQueue.pop();

		//check�� index
		int checkIndexX = check->GetX() / TileSize;
		int checkIndexY = check->GetY() / TileSize;

		//index Ȯ��
		if (checkIndexX < mMinIndexX || checkIndexX >= mMaxSizeX)
			continue;
		if (checkIndexY < mMinIndexX || checkIndexY >= mMaxSizeY)
			continue;

		//Ȯ���� ���� : ��� ������ �������� ������
		if (check->GetImage() == init.GetImage() &&
			check->GetFrameIndexX() == init.GetFrameIndexX() &&
			check->GetFrameIndexY() == init.GetFrameIndexY()) {

			//Ÿ�� ���� ����
			TileSave save;
			save.Set(tileList[checkIndexY][checkIndexX]->GetImage()->GetKeyName(),
				tileList[checkIndexY][checkIndexX]->GetFrameIndexX(),
				tileList[checkIndexY][checkIndexX]->GetFrameIndexY(),
				checkIndexX, checkIndexY);

			saveVector.push_back(save);

			//���� ������ �Ѱ����� floodfill�� �ϱ����� �̹����� �����Ѵ�
			check->SetImage(mCurrentPallete.Image);
			check->SetFrameIndexX(mCurrentPallete.FrameX);
			check->SetFrameIndexY(mCurrentPallete.FrameY);

			if (checkIndexX + 1 < mMaxSizeX)
				tempQueue.emplace(tileList[checkIndexY][checkIndexX + 1]);
			if (checkIndexX - 1 >= 0)
				tempQueue.emplace(tileList[checkIndexY][checkIndexX - 1]);
			if (checkIndexY + 1 < mMaxSizeY)
				tempQueue.emplace(tileList[checkIndexY + 1][checkIndexX]);
			if (checkIndexY - 1 >= 0)
				tempQueue.emplace(tileList[checkIndexY - 1][checkIndexX]);
		}
	}
	//�˻簡 ��������� ������ ������ �ѱ��
	IBrushTile* command = new IBrushTile(tileList, saveVector, mCurrentPallete);
	//���� �������� excute�� ��ǻ� ��������� mCommandList���� �߰����ش�
	mCommandList.emplace(command);
}