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

	//Tile* List들 vector화 필요
	/*
	vector<Tile*> XList;
	for (int y = 0; y < mMaxSizeY; ++y)
	{
		for (int x = 0; x < mMaxSizeX; ++x)
		{
			XList.push_back(new Tile(nullptr, TileSize * x, TileSize * y, TileSize, TileSize, 0, 0));
		}
		mGroundList.push_back(XList);
		mDecoList.push_back(XList);
		mItemList.push_back(XList);
		mObjectList.push_back(XList);
		XList.clear();	//넣어주고 비워주기
		XList.shrink_to_fit();
	}
	*/
	for (int y = 0; y < TileCountY; ++y){
		for (int x = 0; x < TileCountX; ++x){
			mGroundList[y][x] = new Tile(
				ImageManager::GetInstance()->FindImage(L"0"),
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				2,
				5
			);
			mDecoList[y][x] = new Tile(
				nullptr,
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				0,
				0
			);
			mItemList[y][x] = new Tile(
				nullptr,
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				0,
				0
			);
			mObjectList[y][x] = new Tile(
				nullptr,
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				0,
				0
			);
		}
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
	mButtonList.insert(make_pair(L"Load", new Button(L"Load", L"Load", 350, 50, 200, 50, bind(&MapToolScene::Load, this))));
	mButtonList.insert(make_pair(L"Clear", new Button(L"Clear", L"Clear", 450, 50, 200, 50, bind(&MapToolScene::Clear, this))));
	mButtonList.insert(make_pair(L"Play", new Button(L"Play", L"Play", 550, 50, 200, 50, bind(&MapToolScene::Play, this))));

	mButtonList.insert(make_pair(L"Ground", new Button(L"Ground", L"Ground", 650, 150, 200, 50, bind(&MapToolScene::GroundPallete, this))));
	mButtonList.insert(make_pair(L"Wall", new Button(L"Wall", L"Wall", 775, 150, 220, 50, bind(&MapToolScene::WallPallete, this))));
	mButtonList.insert(make_pair(L"Deco", new Button(L"Deco", L"Deco", 875, 150, 200, 50, bind(&MapToolScene::DecoPallete, this))));
	mButtonList.insert(make_pair(L"Item", new Button(L"Item", L"Item", 975, 150, 200, 50, bind(&MapToolScene::ItemPallete, this))));
	mButtonList.insert(make_pair(L"Object", new Button(L"Object", L"Object", 1075, 150, 200, 50, bind(&MapToolScene::ObjectPallete, this))));
	
	mButtonList.insert(make_pair(L"Prev", new Button(L"Prev", L"Prev", 800, 600, 200, 50, bind(&MapToolScene::PrevPallete, this))));
	mButtonList.insert(make_pair(L"Next", new Button(L"Next", L"Next", 900, 600, 200, 50, bind(&MapToolScene::NextPallete, this))));

	mCurrentPallete = mPallete[0][0];
	
	mShowGrid = true;

	//SetSize 관련 변수들
	mMaxSizeX = TileCountX;
	mMaxSizeY = TileCountY;
	mInputX = to_string(TileCountX);
	mInputY = to_string(TileCountY);

	mButtonList.insert(make_pair(L"Set", new Button(L"",L"Set", 475, WINSIZEY - 175, 50, 25, bind(&MapToolScene::SetSize, this))));
	mButtonList.insert(make_pair(L"SizeX", new Button(L"", L"", 300, WINSIZEY - 175, 50, 25, [this]() { mIsInput = 1; })));
	mButtonList.insert(make_pair(L"SizeY", new Button(L"", L"", 370, WINSIZEY - 175, 50, 25, [this]() { mIsInput = 2; })));
	mIsInput = 0;
}

void MapToolScene::Release(){
	for (int y = 0; y < TileCountY; ++y){
		for (int x = 0; x < TileCountX; ++x){
			SafeDelete(mGroundList[y][x]);
			SafeDelete(mDecoList[y][x]);
			SafeDelete(mItemList[y][x]);
			SafeDelete(mObjectList[y][x]);
		}
	}

	ButtonIt iter = mButtonList.begin();
	for (; iter != mButtonList.end(); ++iter){
		SafeDelete(iter->second);
	}
	mButtonList.clear();
}

void MapToolScene::Update(){
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
		int indexX = (_mousePosition.x-100) / TileSize;
		int indexY = (_mousePosition.y-200) / TileSize;

		if (indexX >= 0 && indexX < TileCountX &&
			indexY >= 0 && indexY < TileCountY)
		{
			if ((mGroundList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
				mGroundList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
				mGroundList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
				(mCurrentPallete.Layer == TileLayer::Ground))
			{
				IBrushTile* command = new IBrushTile(mGroundList[indexY][indexX],mCurrentPallete);
				PushCommand(command);
			}
			else if ((mDecoList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
				mDecoList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
				mDecoList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) && 
				(mCurrentPallete.Layer == TileLayer::Deco))
			{
				IBrushTile* command = new IBrushTile(mDecoList[indexY][indexX], mCurrentPallete);
				PushCommand(command);
			}
			if ((mItemList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
				mItemList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
				mItemList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
				(mCurrentPallete.Layer == TileLayer::Item))
			{
				IBrushTile* command = new IBrushTile(mItemList[indexY][indexX], mCurrentPallete);
				PushCommand(command);
			}
			if ((mObjectList[indexY][indexX]->GetImage() != mCurrentPallete.Image ||
				mObjectList[indexY][indexX]->GetFrameIndexX() != mCurrentPallete.FrameX ||
				mObjectList[indexY][indexX]->GetFrameIndexY() != mCurrentPallete.FrameY) &&
				(mCurrentPallete.Layer == TileLayer::GameObject))
			{
				IBrushTile* command = new IBrushTile(mObjectList[indexY][indexX], mCurrentPallete);
				PushCommand(command);
			}
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
	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mGroundList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mDecoList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mItemList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mObjectList[y][x]->Render(hdc);
		}
	}

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

		for (int y = 0; y < TileCountY; ++y){
			for (int x = 0; x < TileCountX; ++x){
				string str;
				wstring keyName;
				if(mGroundList[y][x]->GetImage() != nullptr)
					keyName = mGroundList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str();
				saveStream << ", (";
				saveStream << mGroundList[y][x]->GetFrameIndexX();
				saveStream << ", ";
				saveStream << mGroundList[y][x]->GetFrameIndexY();
				saveStream << "), ";
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

		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string str;
				wstring keyName;
				if (mDecoList[y][x]->GetImage() != nullptr)
					keyName = mDecoList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str();
				saveStream << ", (";
				saveStream << mDecoList[y][x]->GetFrameIndexX();
				saveStream << ", ";
				saveStream << mDecoList[y][x]->GetFrameIndexY();
				saveStream << "), ";
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

		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string str;
				wstring keyName;
				if (mItemList[y][x]->GetImage() != nullptr)
					keyName = mItemList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str();
				saveStream << ", (";
				saveStream << mItemList[y][x]->GetFrameIndexX();
				saveStream << ", ";
				saveStream << mItemList[y][x]->GetFrameIndexY();
				saveStream << "), ";
				saveStream << (int)(mItemList[y][x]->GetTileType());
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

		for (int y = 0; y < TileCountY; ++y) {
			for (int x = 0; x < TileCountX; ++x) {
				string str;
				wstring keyName;
				if (mObjectList[y][x]->GetImage() != nullptr)
					keyName = mObjectList[y][x]->GetImage()->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str();
				saveStream << ", (";
				saveStream << mObjectList[y][x]->GetFrameIndexX();
				saveStream << ", ";
				saveStream << mObjectList[y][x]->GetFrameIndexY();
				saveStream << "), ";
				saveStream << (int)(mObjectList[y][x]->GetTileType());
				saveStream << endl;
			}
		}
	}
}

void MapToolScene::Load(){
	int i = 0;
	ifstream loadStream(L"../04_Data/Test0" + to_wstring(i) + L".txt");
	if (loadStream.is_open()){
		for (int y = 0; y < TileCountY; ++y){
			for (int x = 0; x < TileCountX; ++x){
				string key;
				int frameX;
				int frameY;
				int type;

				string buffer;
				
				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, '(');
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ' ');
				getline(loadStream, buffer, ')');
				frameY = stoi(buffer);
				getline(loadStream, buffer, ' ');
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, '(');
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ' ');
				getline(loadStream, buffer, ')');
				frameY = stoi(buffer);
				getline(loadStream, buffer, ' ');
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, '(');
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ' ');
				getline(loadStream, buffer, ')');
				frameY = stoi(buffer);
				getline(loadStream, buffer, ' ');
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, '(');
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ' ');
				getline(loadStream, buffer, ')');
				frameY = stoi(buffer);
				getline(loadStream, buffer, ' ');
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
	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mDecoList[y][x]->SetImage(nullptr);
			mItemList[y][x]->SetImage(nullptr);
			mObjectList[y][x]->SetImage(nullptr);

			mGroundList[y][x] = new Tile(
				ImageManager::GetInstance()->FindImage(L"0"),
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				2,
				5
			);
		}
	}
}

void MapToolScene::PushCommand(ICommand* command){
	command->Execute();
	mCommandList.emplace(command);
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

void MapToolScene::Undo(){
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

void MapToolScene::Play() {
	SceneManager::GetInstance()->LoadScene(L"GameScene");
}