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
	//채울 타일을 선택 했을 경우
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
	//채울 타일 선택을 안했을 경우
	else
	{
		//모드를 변환 한 후, MapToolScene::Update에서 mFillMod == true일때 Paint()를 호출한다
		mFillMod = !mFillMod;
	}
}

void MapToolScene::Paint()
{
	//채우고 싶은 시작점을 클릭
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
		int indexX = (_mousePosition.x - mMoveX) / TileSize + mMinIndexX;
		int indexY = (_mousePosition.y - mMoveY) / TileSize + mMinIndexY;

		//시작점이 찍을 수 있는 인덱스인지 체크
		if (indexX >= mMinIndexX && indexX < mMinIndexX + TileCountX && indexX < mMaxSizeX &&
			indexY >= mMinIndexY && indexY < mMinIndexY + TileCountY && indexY < mMaxSizeY)
		{


			//시작점의 정보가 현재 선택한 팔레트와 하나라도 같지 않으면
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
	queue<Tile*> tempQueue;	//floodfill용 큐
	vector<TileSave> saveVector;	//타일 데이터 저장벡터

	tempQueue.emplace(tileList[indexY][indexX]);
	Tile init = *mGroundList[indexY][indexX];

	//검사가 종료될때까지
	while (tempQueue.empty() == false) {
		Tile* check = tempQueue.front();
		tempQueue.pop();

		//check의 index
		int checkIndexX = check->GetX() / TileSize;
		int checkIndexY = check->GetY() / TileSize;

		//index 확인
		if (checkIndexX < mMinIndexX || checkIndexX >= mMaxSizeX)
			continue;
		if (checkIndexY < mMinIndexX || checkIndexY >= mMaxSizeY)
			continue;

		//확장할 조건 : 모든 정보가 시작점과 같으면
		if (check->GetImage() == init.GetImage() &&
			check->GetFrameIndexX() == init.GetFrameIndexX() &&
			check->GetFrameIndexY() == init.GetFrameIndexY()) {

			//타일 정보 저장
			TileSave save;
			save.Set(tileList[checkIndexY][checkIndexX]->GetImage()->GetKeyName(),
				tileList[checkIndexY][checkIndexX]->GetFrameIndexX(),
				tileList[checkIndexY][checkIndexX]->GetFrameIndexY(),
				checkIndexX, checkIndexY);

			saveVector.push_back(save);

			//저장 정보를 넘겼으니 floodfill을 하기위해 이미지를 변경한다
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
	//검사가 종료됐으니 저장한 정보를 넘긴다
	IBrushTile* command = new IBrushTile(tileList, saveVector, mCurrentPallete);
	//위의 과정에서 excute는 사실상 실행됐으니 mCommandList에만 추가해준다
	mCommandList.emplace(command);
}