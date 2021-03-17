#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"

#include <fstream>

#include "Ground.h"
#include "Camera.h"
void GameScene::Init(){
	Beat::GetInstance()->Init();

	SoundPlayer::GetInstance()->LoadFromFile(L"Main", Resources(L"theme.mp3"),true);
	SoundPlayer::GetInstance()->LoadFromFile(L"Game", Resources(L"game.mp3"), true);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, new Player("Player"));

	SoundPlayer::GetInstance()->Play(L"zone1_1",0.2f);
	SoundPlayer::GetInstance()->Play(L"zone1_1_shopkeeper", 0.2f);
	Beat::GetInstance()->SetMusic(L"zone1_1",L"zone1_1");
	
	FileManager::GetInstance()->LoadMap(L"Test00", mGroundList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test01", mWallList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test02", mDecoList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test03", mItemList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test04", mObjectList, TileSize);

	//Ground»ý¼º
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, new Ground("Ground"));

	//camera
	Camera* camera = new Camera();
	camera->SetTarget(ObjectManager::GetInstance()->FindObject("Player"));
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, camera);

	ObjectManager::GetInstance()->Init();
	mToolButton  = new Button(L"Tool",  L"Tool",  550, 50, 200, 50, bind(&GameScene::Tool, this));
}

void GameScene::Release(){
	SafeDelete(mToolButton);
	Beat::GetInstance()->Release();
	ObjectManager::GetInstance()->FindObject("Ground")->SetIsDestroy(true);
}

void GameScene::Update(){
	Beat::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();
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
	Beat::GetInstance()->Render(hdc);
}

void GameScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"zone1_1");
	SoundPlayer::GetInstance()->Stop(L"zone1_1_shopkeeper");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
}