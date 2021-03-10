#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"

#include <fstream>

void GameScene::Init(){
	SoundPlayer::GetInstance()->LoadFromFile(L"Main", Resources(L"theme.mp3"),true);
	SoundPlayer::GetInstance()->LoadFromFile(L"Game", Resources(L"game.mp3"), true);

	mPlayer = new Player("Player");
	mPlayer->Init();

	SoundPlayer::GetInstance()->Play(L"Game",0.2f);

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			mGroundList[y][x] = new Tile(
				nullptr,
				100 + TileSize * x,
				200 + TileSize * y,
				TileSize,
				TileSize,
				0,
				0
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
	int i = 0;
	ifstream loadStream(L"../04_Data/Test0" + to_wstring(i) + L".txt");
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
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
				int frameX;
				int frameY;
				int type;

				string buffer;

				getline(loadStream, buffer, ',');
				key = buffer;
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
	mToolButton  = new Button(L"Tool",  L"Tool",  550, 50, 200, 50, bind(&GameScene::Tool, this));
}

void GameScene::Release(){
	mPlayer->Release();
	SafeDelete(mPlayer);
	SafeDelete(mToolButton);
}

void GameScene::Update(){
	mPlayer->Update();
	mToolButton->Update();
}

void GameScene::Render(HDC hdc){
	HBRUSH Brush = CreateSolidBrush(RGB(66, 66, 66));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, Brush);

	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	RenderRect(hdc, rc);

	SelectObject(hdc, oldBrush);
	DeleteObject(Brush);

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			if(mGroundList[y][x] != NULL)
				mGroundList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			if (mDecoList[y][x] != NULL)
				mDecoList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			if (mItemList[y][x] != NULL)
				mItemList[y][x]->Render(hdc);
		}
	}

	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
			if (mObjectList[y][x] != NULL)
				mObjectList[y][x]->Render(hdc);
		}
	}

	mToolButton->Render(hdc);
	mPlayer->Render(hdc);
}

void GameScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"Game");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
}