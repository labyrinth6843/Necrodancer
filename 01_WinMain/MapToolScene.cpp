#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"
#include "Image.h"
#include "Button.h"
#include <fstream>

void MapToolScene::Init()
{
	//Image LoadFromFile은 필터 -> LoadImage.cpp로 옮김

	for (int i = 0; i < 18; i++) {
		wstring wstr = to_wstring(i);
		mPalleteList.push_back(wstr);
	}

	mMaxSizeX = TileCountX;
	mMaxSizeY = TileCountY;
	mMinIndexX = 0;
	mMinIndexY = 0;

	mMoveX = 100;
	mMoveY = 200;

	//Tile* List들 vector화 필요
	vector<Tile*> GList;
	vector<Tile*> DList;
	vector<Tile*> IList;
	vector<Tile*> OList;
	for (int y = 0; y < mMaxSizeY; ++y)
	{
		for (int x = 0; x < mMaxSizeX; ++x)
		{
			GList.push_back(new Tile(ImageManager::GetInstance()->FindImage(L"0"), TileSize * x , TileSize * y , TileSize, TileSize, 2, 5));
			DList.push_back(new Tile(nullptr, TileSize * x , TileSize * y , TileSize, TileSize, 0, 0));
			IList.push_back(new Tile(nullptr, TileSize * x, TileSize * y, TileSize, TileSize, 0, 0));
			OList.push_back(new Tile(nullptr, TileSize * x, TileSize * y, TileSize, TileSize, 0, 0));
		}
		mGroundList.push_back(GList);
		mDecoList.push_back(DList);
		mItemList.push_back(IList);
		mObjectList.push_back(OList);
		
		DList.clear();
		DList.shrink_to_fit();
		IList.clear();
		IList.shrink_to_fit();
		OList.clear();
		OList.shrink_to_fit();
		GList.clear();
		GList.shrink_to_fit();
	}

	int palleteStartX = WINSIZEX / 2 + 140;
	int palleteStartY = 200;
	for (int y = 0; y < 10; ++y)	{
		for (int x = 0; x < 5; ++x){
			mPallete[y][x].Image = ImageManager::GetInstance()->FindImage(mPalleteList[mCurrentPage]);
			mPallete[y][x].PositionX = palleteStartX + TileSize * x;
			mPallete[y][x].PositionY = palleteStartY + TileSize * y;
			mPallete[y][x].Width = TileSize;
			mPallete[y][x].Height = TileSize;
			mPallete[y][x].Rc = RectMake(mPallete[y][x].PositionX,	mPallete[y][x].PositionY, mPallete[y][x].Width, mPallete[y][x].Height);
			mPallete[y][x].FrameX = x;
			mPallete[y][x].FrameY = y;

			if(mCurrentPage < 10)
				mPallete[y][x].Layer = TileLayer::Ground;
			else if (mCurrentPage < 15)
				mPallete[y][x].Layer = TileLayer::Deco;
			else if (mCurrentPage < 17)
				mPallete[y][x].Layer = TileLayer::Item;
			else if (mCurrentPage < 18)
				mPallete[y][x].Layer = TileLayer::GameObject;
		}
	}

	mButtonList.insert(make_pair(L"Undo", new Button(L"Undo", L"Undo",  50, 50, 200, 50, bind(&MapToolScene::Undo, this))));
	mButtonList.insert(make_pair(L"Redo", new Button(L"Redo", L"Redo", 150, 50, 200, 50, bind(&MapToolScene::Redo, this))));

	mButtonList.insert(make_pair(L"Save", new Button(L"Save", L"Save", 250, 50, 200, 50, bind(&MapToolScene::Save, this))));
	mButtonList.insert(make_pair(L"Load", new Button(L"Load", L"Load", 350, 50, 200, 50, [this]() 
		{
			FileManager::GetInstance()->LoadMap(L"Test00", mGroundList, TileSize);
			FileManager::GetInstance()->LoadMap(L"Test01", mDecoList, TileSize);
			FileManager::GetInstance()->LoadMap(L"Test02", mItemList, TileSize);
			FileManager::GetInstance()->LoadMap(L"Test03", mObjectList, TileSize);
			mMaxSizeY = mGroundList.size();
			mMaxSizeX = mGroundList[mMaxSizeY - 1].size();
			mInputX = to_string(mMaxSizeX);
			mInputY = to_string(mMaxSizeY);
		}
	)));

	mButtonList.insert(make_pair(L"Clear", new Button(L"Clear", L"Clear", 450, 50, 200, 50, bind(&MapToolScene::Clear, this))));
	mButtonList.insert(make_pair(L"Play", new Button(L"Play", L"Play", 550, 50, 200, 50, bind(&MapToolScene::Play, this))));

	mButtonList.insert(make_pair(L"Ground", new Button(L"Ground", L"Ground", 650, 150, 200, 50, bind(&MapToolScene::GroundPallete, this))));
	mButtonList.insert(make_pair(L"Wall", new Button(L"Wall", L"Wall", 775, 150, 220, 50, bind(&MapToolScene::WallPallete, this))));
	mButtonList.insert(make_pair(L"Deco", new Button(L"Deco", L"Deco", 875, 150, 200, 50, bind(&MapToolScene::DecoPallete, this))));
	mButtonList.insert(make_pair(L"Item", new Button(L"Item", L"Item", 975, 150, 200, 50, bind(&MapToolScene::ItemPallete, this))));
	mButtonList.insert(make_pair(L"Object", new Button(L"Object", L"Object", 1075, 150, 200, 50, bind(&MapToolScene::ObjectPallete, this))));
	
	mButtonList.insert(make_pair(L"Prev", new Button(L"Prev", L"Prev", 800, 600, 200, 50, bind(&MapToolScene::PrevPallete, this))));
	mButtonList.insert(make_pair(L"Next", new Button(L"Next", L"Next", 900, 600, 200, 50, bind(&MapToolScene::NextPallete, this))));

	//선택 툴
	mButtonList.insert(make_pair(L"SelectMod", new Button(L"", L"Select", 80, 100, 60, 25, [this]()
		{
			mDragMod = false;
			mSelectMod = !mSelectMod;
			mSelectIndex.clear();
			mSelectIndex.shrink_to_fit();
		})));
	mButtonList.insert(make_pair(L"DragMod", new Button(L"", L"Drag", 160, 100, 60, 25, [this]()
		{
			mSelectRectShow = false;
			mSelectMod = false;
			mDragMod = !mDragMod;
			mSelectIndex.clear();
			mSelectIndex.shrink_to_fit();
		})));

	mSelectRectShow = false;
	mSelectMod = false;
	mDragMod = false;
	mShowGrid = true;

	//SetSize 관련 변수들
	mInputX = to_string(TileCountX);
	mInputY = to_string(TileCountY);

	mButtonList.insert(make_pair(L"Set", new Button(L"",L"Set", 475, 100, 50, 25, bind(&MapToolScene::SetSize, this))));
	mButtonList.insert(make_pair(L"SizeX", new Button(L"", L"", 300, 100, 50, 25, [this]() { mIsInput = 1; })));
	mButtonList.insert(make_pair(L"SizeY", new Button(L"", L"", 370, 100, 50, 25, [this]() { mIsInput = 2; })));
	mIsInput = 0;

	mButtonList.insert(make_pair(L"LeftMove", new Button(L"",L"",50, 200 + TileSize*5, 25, 50, bind(&MapToolScene::ButtonMove,this,VK_LEFT,5))));
	mButtonList.insert(make_pair(L"RightMove", new Button(L"", L"", 150 + TileSize*10 , 200 + TileSize * 5, 25, 50, bind(&MapToolScene::ButtonMove, this, VK_RIGHT, 5))));
	mButtonList.insert(make_pair(L"UpMove", new Button(L"", L"", 100 + TileSize * 5, 175, 50, 25, bind(&MapToolScene::ButtonMove, this, VK_UP, 5))));
	mButtonList.insert(make_pair(L"DownMove", new Button(L"", L"", 100 + TileSize * 5, 225 + TileSize * 10, 50, 25, bind(&MapToolScene::ButtonMove, this, VK_DOWN, 5))));

	mCurrentPallete = mPallete[0][0];
}

void MapToolScene::Release(){
	for (int y = 0; y < mMaxSizeY; ++y){
		for (int x = 0; x < mMaxSizeY; ++x){
			SafeDelete(mGroundList[y][x]);
			SafeDelete(mDecoList[y][x]);
			SafeDelete(mItemList[y][x]);
			SafeDelete(mObjectList[y][x]);
		}
	}
	mGroundList.clear();
	mGroundList.shrink_to_fit();
	mDecoList.clear();
	mDecoList.shrink_to_fit();
	mItemList.clear();
	mItemList.shrink_to_fit();
	mObjectList.clear();
	mObjectList.shrink_to_fit();

	ButtonIt iter = mButtonList.begin();
	for (; iter != mButtonList.end(); ++iter){
		SafeDelete(iter->second);
	}
	mButtonList.clear();
}

void MapToolScene::Update(){

	//팔레트
	int palleteStartX = WINSIZEX / 2+140;
	int palleteStartY = 200;
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 5; ++x) {
			mPallete[y][x].Image = ImageManager::GetInstance()->FindImage(wstring(mPalleteList[mCurrentPage]));
			mPallete[y][x].PositionX = palleteStartX + TileSize * x;
			mPallete[y][x].PositionY = palleteStartY + TileSize * y;
			mPallete[y][x].Width = TileSize;
			mPallete[y][x].Height = TileSize;
			mPallete[y][x].Rc = RectMake(mPallete[y][x].PositionX, mPallete[y][x].PositionY, mPallete[y][x].Width, mPallete[y][x].Height);
			mPallete[y][x].FrameX = x;
			mPallete[y][x].FrameY = y;
			if (mCurrentPage < 5)
				mPallete[y][x].Layer = TileLayer::Ground;
			else if (mCurrentPage < 10)
				mPallete[y][x].Layer = TileLayer::Deco;
			else if (mCurrentPage < 15)
				mPallete[y][x].Layer = TileLayer::Item;
			else if (mCurrentPage < 17)
				mPallete[y][x].Layer = TileLayer::GameObject;
		}
	}

	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)){
		//{{ 팔레트 픽~
		for (int y = 0; y < 10; ++y)	{
			for (int x = 0; x < 5; ++x){
				if (PtInRect(&mPallete[y][x].Rc, _mousePosition)){
					mCurrentPallete = mPallete[y][x];
				}
			}
		}
		// }}
	}


	// {{ 타일 그리기~
	if (Input::GetInstance()->GetKey(VK_LBUTTON)){
		if (_mousePosition.x > mMoveX && _mousePosition.y > mMoveY)
		{

			int indexX = (_mousePosition.x - mMoveX) / TileSize + mMinIndexX;
			int indexY = (_mousePosition.y - mMoveY) / TileSize + mMinIndexY;

			if (indexX >= mMinIndexX && indexX < mMinIndexX + TileCountX && indexX < mMaxSizeX &&
				indexY >= mMinIndexY && indexY < mMinIndexY + TileCountY && indexY < mMaxSizeY)
			{

				if (mSelectMod)
				{
					bool check = true;
					POINT temp = { indexX, indexY };
					for (int i = 0; i < mSelectIndex.size(); ++i)
					{
						if (mSelectIndex[i].x == temp.x && mSelectIndex[i].y == temp.y)
						{
							check = false;
							break;
						}
					}
					if(check)
						mSelectIndex.push_back(temp);
				}
				else if (mDragMod)
				{
					mSelectRect.right = _mousePosition.x;
					mSelectRect.bottom = _mousePosition.y;
				}
				else
				{
					if ((mGroundList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
						mGroundList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
						mGroundList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
						(mCurrentPallete.Layer == TileLayer::Ground))
					{
						TileSave com;
						com.Set(mGroundList[indexY][indexX]->GetImage()->GetKeyName(),
							mGroundList[indexY][indexX]->GetFrameIndexX(), mGroundList[indexY][indexX]->GetFrameIndexY(),indexX,indexY);
						IBrushTile* command = new IBrushTile(mGroundList, com, mCurrentPallete);
						PushCommand(command);
					}
					else if ((mDecoList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
						mDecoList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
						mDecoList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) && 
						(mCurrentPallete.Layer == TileLayer::Deco))
					{
						TileSave com;
						com.Set(mDecoList[indexY][indexX]->GetImage()->GetKeyName(),
							mDecoList[indexY][indexX]->GetFrameIndexX(), mDecoList[indexY][indexX]->GetFrameIndexY(), indexX, indexY);
						IBrushTile* command = new IBrushTile(mDecoList, com, mCurrentPallete);
						PushCommand(command);
					}
					if ((mItemList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
						mItemList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
						mItemList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
						(mCurrentPallete.Layer == TileLayer::Item))
					{
						TileSave com;
						com.Set(mItemList[indexY][indexX]->GetImage()->GetKeyName(),
							mItemList[indexY][indexX]->GetFrameIndexX(), mItemList[indexY][indexX]->GetFrameIndexY(), indexX, indexY);
						IBrushTile* command = new IBrushTile(mItemList, com, mCurrentPallete);
						PushCommand(command);
					}
					if ((mObjectList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
						mObjectList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
						mObjectList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
						(mCurrentPallete.Layer == TileLayer::GameObject))
					{
						TileSave com;
						com.Set(mObjectList[indexY][indexX]->GetImage()->GetKeyName(),
							mObjectList[indexY][indexX]->GetFrameIndexX(), mObjectList[indexY][indexX]->GetFrameIndexY(), indexX, indexY);
						IBrushTile* command = new IBrushTile(mObjectList, com, mCurrentPallete);
						PushCommand(command);
					}
				}
			}
		}
	}

	if (mDragMod)
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)) {
			int indexX = (_mousePosition.x - mMoveX) / TileSize + mMinIndexX;
			int indexY = (_mousePosition.y - mMoveY) / TileSize + mMinIndexY;

			if (indexX >= mMinIndexX && indexX < mMinIndexX + TileCountX && indexX < mMaxSizeX &&
				indexY >= mMinIndexY && indexY < mMinIndexY + TileCountY && indexY < mMaxSizeY)
			{
				//mSelectRect의 left,top을 설정
				mSelectRect.left = _mousePosition.x-1;
				mSelectRect.top = _mousePosition.y-1;
				mSelectRect.right = _mousePosition.x;
				mSelectRect.bottom = _mousePosition.y;
				mSelectRectShow = true;
			}
		}
		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON)) {
			int indexX = (_mousePosition.x - mMoveX) / TileSize + mMinIndexX;
			int indexY = (_mousePosition.y - mMoveY) / TileSize + mMinIndexY;

			mSelectRect.right = _mousePosition.x;
			mSelectRect.bottom = _mousePosition.y;
			if (indexX >= mMinIndexX && indexX < mMaxSizeX &&
				indexY >= mMinIndexY && indexY < mMaxSizeY)
			{
				if (mSelectRect.bottom < mSelectRect.top)
				{
					LONG temp = mSelectRect.top;
					mSelectRect.top = mSelectRect.bottom;
					mSelectRect.bottom = temp;
				}
				if (mSelectRect.right < mSelectRect.left)
				{
					LONG temp = mSelectRect.left;
					mSelectRect.left = mSelectRect.right;
					mSelectRect.right = temp;
				}
				//mSelectRect와 충돌하는 타일의 인덱스를 mSelectIndex에 저장
				for (int y = 0; y < TileCountY; ++y) 
				{
					if (y >= mMaxSizeY)
						break;
					for (int x = 0; x < TileCountX; ++x)
					{
						if (x >= mMaxSizeX)
							break;
						POINT pos = { x * TileSize + TileSize/2 + mMoveX , y * TileSize + TileSize/2 + mMoveY };
						if (PtInRect(&mSelectRect, pos))
						{
							POINT index = { x + mMinIndexX, y + mMinIndexY};
							bool check = true;
							if(index.x >= mMaxSizeX || index.y >= mMaxSizeY)
								bool check = false;
							for (int i = 0; i < mSelectIndex.size(); ++i)
							{
								if (check && mSelectIndex[i].x == index.x && mSelectIndex[i].y == index.y)
								{
									check = false;
									break;
								}
							}
							if (check)
								mSelectIndex.push_back(index);
						}
					}
				}
			}
			mSelectRectShow = false;
		}
	}
	if (Input::GetInstance()->GetKeyDown('H'))	//격자 표시
		mShowGrid = !mShowGrid;
	if (Input::GetInstance()->GetKey(VK_CONTROL)) {
		if (Input::GetInstance()->GetKeyDown('Z'))
			Undo();
		if (Input::GetInstance()->GetKeyDown('Y'))
			Redo();
	}

	ButtonIt iter = mButtonList.begin();
	for (; iter != mButtonList.end(); ++iter)
	{
		iter->second->Update();
	}

	CanvasMove();
}

void MapToolScene::Render(HDC hdc){
	//배경
	HBRUSH Brush = CreateSolidBrush(RGB(66, 66, 66));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, Brush);
	
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	RenderRect(hdc, rc);
	
	SelectObject(hdc, oldBrush);
	DeleteObject(Brush);

	//타일 출력
	int posY = 0;
	for (int y = mMinIndexY; y < mMinIndexY + TileCountY; ++y) {
		int posX = 0;
		if (y >= mMaxSizeY)
			break;
		for (int x = mMinIndexX; x < mMinIndexX + TileCountX; ++x) {
			if (x >= mMaxSizeX)
				break;
			mGroundList[y][x]->PositionRender(hdc, posX * TileSize + mMoveX, posY * TileSize + mMoveY);
			mDecoList[y][x]->PositionRender(hdc, posX * TileSize + mMoveX, posY * TileSize + mMoveY);
			mItemList[y][x]->PositionRender(hdc, posX * TileSize + mMoveX, posY * TileSize + mMoveY);
			mObjectList[y][x]->PositionRender(hdc, posX * TileSize + mMoveX, posY * TileSize + mMoveY);

			posX++;
		}
		posY++;
	}
	//격자
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (mShowGrid)
			{
				RECT temp = RectMake(100 + TileSize * x, 200 + TileSize * y, TileSize, TileSize);
				Gizmo::GetInstance()->DrawRect(hdc, temp, Gizmo::Color::Blue);
			}
		}
	}
	//선택표시
	Image* select = IMAGEMANAGER->FindImage(L"SelectTile");
	for (int i = 0; i < mSelectIndex.size(); ++i)
	{
		int posX = (mSelectIndex[i].x - mMinIndexX)* TileSize + mMoveX;
		int posY = (mSelectIndex[i].y - mMinIndexY)* TileSize + mMoveY;
		
		if (posX < mMoveX || posY < mMoveY)
			continue;
		if (posX >= TileSize*TileCountX + mMoveX || posY >= TileSize* TileCountY + mMoveY)
			continue;
		
		select->AlphaRender(hdc, posX, posY, 0.5f);
	}
	//드래그 범위 표시 Rect
	if (mSelectRectShow)
	{
		HBRUSH nullbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HPEN redpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HBRUSH prevbrush = (HBRUSH)SelectObject(hdc,nullbrush);
		HPEN prevpen = (HPEN)SelectObject(hdc, redpen);

		RenderRect(hdc, mSelectRect);

		SelectObject(hdc,prevbrush);
		SelectObject(hdc, prevbrush);
		DeleteObject(nullbrush);
		DeleteObject(redpen);
	}

	//팔레트
	for (int y = 0; y < 10; ++y)	{
		for (int x = 0; x < 5; ++x)	{
			mPallete[y][x].Image->ScaleFrameRender
			(hdc,
				mPallete[y][x].Rc.left,
				mPallete[y][x].Rc.top,
				mPallete[y][x].FrameX,
				mPallete[y][x].FrameY,
				mPallete[y][x].Width,
				mPallete[y][x].Height
			);
		}
	}
	//선택된 타일 미리보기
	mCurrentPallete.Image->ScaleFrameRender(hdc, 600, 200, mCurrentPallete.FrameX, mCurrentPallete.FrameY, 50, 50);
	Gizmo::GetInstance()->DrawRect(hdc, RectMake(600, 200, 50, 50), Gizmo::Color::Black);

	//버튼
	ButtonIt iter = mButtonList.begin();
	for (; iter != mButtonList.end(); ++iter)
	{
		iter->second->Render(hdc);
	}

	//Size 입출력, 버튼위치 변경시 아래 x,y값도 변경해줄것
	RECT rcX = mButtonList.find(L"SizeX")->second->GetRect();
	wstring x;
	x.assign(mInputX.begin(), mInputX.end());
	TextOut(hdc, rcX.left + 5,rcX.top + 5, x.c_str(), x.length());
	RECT rcY = mButtonList.find(L"SizeY")->second->GetRect();
	wstring y;
	y.assign(mInputY.begin(), mInputY.end());
	TextOut(hdc, rcY.left + 5, rcY.top + 5, y.c_str(), y.length());
}

void MapToolScene::Save(){
	int i = 0;
	ofstream saveStream(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (saveStream.is_open()){
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < mMaxSizeY; ++y){
			for (int x = 0; x < mMaxSizeX; ++x){
				string str;
				wstring keyName;
				if(mGroundList[y][x]->GetImage() != nullptr)
					keyName = mGroundList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str() << ",";
				saveStream << x << ",";
				saveStream << y << ",";
				saveStream << mGroundList[y][x]->GetFrameIndexX() << ",";
				saveStream << mGroundList[y][x]->GetFrameIndexY() << ",";
				saveStream << (int)(mGroundList[y][x]->GetTileType());
				saveStream << endl;
			}
		}
	}
	i++;
	saveStream.close();
	saveStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (saveStream.is_open()) {
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < mMaxSizeY; ++y) {
			for (int x = 0; x < mMaxSizeX; ++x) {
				string str;
				wstring keyName;
				if (mDecoList[y][x]->GetImage() != nullptr)
					keyName = mDecoList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str() << ",";
				saveStream << x << ",";
				saveStream << y << ",";
				saveStream << mDecoList[y][x]->GetFrameIndexX() << ",";
				saveStream << mDecoList[y][x]->GetFrameIndexY() << ",";
				saveStream << (int)(mDecoList[y][x]->GetTileType());
				saveStream << endl;
			}
		}
	}
	i++;
	saveStream.close();
	saveStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (saveStream.is_open()) {
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < mMaxSizeY; ++y) {
			for (int x = 0; x < mMaxSizeX; ++x) {
				string str;
				wstring keyName;
				if (mItemList[y][x]->GetImage() != nullptr)
					keyName = mItemList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str() << ",";
				saveStream << x << ",";
				saveStream << y << ",";
				saveStream << mItemList[y][x]->GetFrameIndexX() << ",";
				saveStream << mItemList[y][x]->GetFrameIndexY() << ",";
				saveStream << (int)(mItemList[y][x]->GetTileType()) << endl;
			}
		}
	}
	i++;
	saveStream.close();
	saveStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (saveStream.is_open()) {
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < mMaxSizeY; ++y) {
			for (int x = 0; x < mMaxSizeX; ++x) {
				string str;
				wstring keyName;
				if (mObjectList[y][x]->GetImage() != nullptr)
					keyName = mObjectList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str()<< ",";
				saveStream << x << ",";
				saveStream << y << ",";
				saveStream << mObjectList[y][x]->GetFrameIndexX()<< ",";
				saveStream << mObjectList[y][x]->GetFrameIndexY()<< ",";
				saveStream << (int)(mObjectList[y][x]->GetTileType());
				saveStream << endl;
			}
		}
	}
	saveStream.close();
}

void MapToolScene::Load(){	//이제 사용 안함
	int i = 0;
	ifstream loadStream(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (loadStream.is_open()){
		for (int y = 0; y < TileCountY; ++y){
			for (int x = 0; x < TileCountX; ++x){
				string key;
				int posx;
				int posy;
				int frameX;
				int frameY;
				int type;

				string buffer;
				
				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				posx = stoi(buffer);
				getline(loadStream, buffer, ',');
				posy = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				getline(loadStream, buffer);
				type = stoi(buffer);

				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mGroundList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mGroundList[y][x]->SetFrameIndexX(frameX);
				mGroundList[y][x]->SetFrameIndexY(frameY);
				mGroundList[y][x]->SetTileType((TileType)type);
			}
		}
	}
	i++;
	loadStream.close();
	loadStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (loadStream.is_open()) {
		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string key;
				int indexX;
				int indexY;
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				indexX = stoi(buffer);
				getline(loadStream, buffer, ',');
				indexY = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				getline(loadStream, buffer);
				type = stoi(buffer);

				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mDecoList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mDecoList[y][x]->SetFrameIndexX(frameX);
				mDecoList[y][x]->SetFrameIndexY(frameY);
				mDecoList[y][x]->SetTileType((TileType)type);
			}
		}
	}
	i++;
	loadStream.close();
	loadStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (loadStream.is_open()) {
		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string key;
				int indexX;
				int indexY;
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				indexX = stoi(buffer);
				getline(loadStream, buffer, ',');
				indexY = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				getline(loadStream, buffer);
				type = stoi(buffer);

				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mItemList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mItemList[y][x]->SetFrameIndexX(frameX);
				mItemList[y][x]->SetFrameIndexY(frameY);
				mItemList[y][x]->SetTileType((TileType)type);
			}
		}
	}
	i++;
	loadStream.close();
	loadStream.open(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (loadStream.is_open()) {
		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string key;
				int indexX;
				int indexY;
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				indexX = stoi(buffer);
				getline(loadStream, buffer, ',');
				indexY = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				getline(loadStream, buffer);
				type = stoi(buffer);

				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mObjectList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				mObjectList[y][x]->SetFrameIndexX(frameX);
				mObjectList[y][x]->SetFrameIndexY(frameY);
				mObjectList[y][x]->SetTileType((TileType)type);
			}
		}
	}
}

void MapToolScene::Clear(){
	for (int y = 0; y < mMaxSizeY; ++y) {
		for (int x = 0; x < mMaxSizeX; ++x) {
			mDecoList[y][x]->SetImage(nullptr);
			mItemList[y][x]->SetImage(nullptr);
			mObjectList[y][x]->SetImage(nullptr);
/*
			mGroundList[y][x]->SetImage(nullptr);
*/
			mGroundList[y][x] = new Tile(
				ImageManager::GetInstance()->FindImage(L"0"),
				TileSize * x,
				TileSize * y,
				TileSize,
				TileSize,
				2,
				5
			);
		}
	}
}


void MapToolScene::GroundPallete(){
	mCurrentPage = 0;
}

void MapToolScene::WallPallete(){
	mCurrentPage = 5;
}

void MapToolScene::DecoPallete(){
	mCurrentPage = 10;
}

void MapToolScene::ItemPallete(){
	mCurrentPage = 15;
}

void MapToolScene::ObjectPallete(){
	mCurrentPage = 17;
}

void MapToolScene::PrevPallete(){
	if (mCurrentPage == 0)
		mCurrentPage = mPalleteList.size() - 1;
	else mCurrentPage--;
}

void MapToolScene::NextPallete(){
	if (mCurrentPage == mPalleteList.size() - 1)
		mCurrentPage = 0;
	else mCurrentPage++;
}


void MapToolScene::Play() {
	SceneManager::GetInstance()->LoadScene(L"GameScene");
}