﻿#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"
#include "EnemyManager.h"

#include <fstream>

#include "Ground.h"
#include "Wall.h"
#include "Item.h"
#include "Enemy.h"

#include "Camera.h"
void GameScene::Init(){
	Beat::GetInstance()->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, new Player("Player"));

	SoundPlayer::GetInstance()->Play(L"zone1_1",0.2f);
	SoundPlayer::GetInstance()->Play(L"zone1_1_shopkeeper", 0.2f);
	Beat::GetInstance()->SetMusic(L"zone1_1",L"zone1_1");
	EnemyManager* mEnemyManager = new EnemyManager;
	mEnemyManager->LoadEnemy();
	//게임씬에서 사용할 오브젝트들 생성
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Ground, new Ground("Ground"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Wall, new Wall("Wall"));
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, new Wall("Item"));
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, new Enemy("Monster"));
	
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
	BEAT->Release();
	ObjectManager::GetInstance()->FindObject("Player")->SetIsDestroy(true);
	ObjectManager::GetInstance()->FindObject("Ground")->SetIsDestroy(true);
}

void GameScene::Update(){
	ObjectManager::GetInstance()->Update();
	BEAT->Update();
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

	mToolButton->Render(hdc);
	COMBO->Render(hdc);
	BEAT->Render(hdc);

}

void GameScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"zone1_1");
	SoundPlayer::GetInstance()->Stop(L"zone1_1_shopkeeper");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
}