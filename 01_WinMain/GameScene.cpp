#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"

#include <fstream>

#include "Ground.h"
#include "Camera.h"
void GameScene::Init(){
	SoundPlayer::GetInstance()->LoadFromFile(L"Main", Resources(L"theme.mp3"),true);
	SoundPlayer::GetInstance()->LoadFromFile(L"Game", Resources(L"game.mp3"), true);

	mPlayer = new Player("Player");
	mPlayer->Init();

	SoundPlayer::GetInstance()->Play(L"Game",0.2f);
	
	//FileManager::GetInstance()->LoadMap(L"Test00", mGroundList, TileSize);
	//FileManager::GetInstance()->LoadMap(L"Test01", mDecoList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test02", mItemList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test03", mObjectList, TileSize);

	//Ground»ý¼º
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, new Ground("Ground"));

	//camera
	Camera* camera = new Camera();
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, camera);

	ObjectManager::GetInstance()->Init();
	mToolButton  = new Button(L"Tool",  L"Tool",  550, 50, 200, 50, bind(&GameScene::Tool, this));
}

void GameScene::Release(){
	mPlayer->Release();
	SafeDelete(mPlayer);
	SafeDelete(mToolButton);

	ObjectManager::GetInstance()->FindObject("Ground")->SetIsDestroy(true);
}

void GameScene::Update(){
	ObjectManager::GetInstance()->Update();
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

	//Ground
	ObjectManager::GetInstance()->Render(hdc);
	//
	for (int y = 0; y < TileCountY; ++y) {
		for (int x = 0; x < TileCountX; ++x) {
				//mGroundList[y][x]->MoveRender(hdc, 100, 200);
				//mDecoList[y][x]->MoveRender(hdc, 100, 200);
			if (mItemList[y][x] != NULL)
				mItemList[y][x]->MoveRender(hdc, 100, 200);
			if(mObjectList[y][x] != NULL)
				mObjectList[y][x]->MoveRender(hdc, 100, 200);
		}
	}

	mToolButton->Render(hdc);
	mPlayer->Render(hdc);
}

void GameScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"Game");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
}