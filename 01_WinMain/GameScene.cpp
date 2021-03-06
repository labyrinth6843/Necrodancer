#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Button.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include <fstream>

#include "Ground.h"
#include "Wall.h"
#include "Item.h"
#include "Enemy.h"

#include "Camera.h"
void GameScene::Init(){
	Beat::GetInstance()->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, new Player("Player", 6, 5));
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");

	SoundPlayer::GetInstance()->Play(L"zone1_1",0.2f);
	SoundPlayer::GetInstance()->Play(L"zone1_1_shopkeeper", 0.2f * temp->DistanceShopkeeper());
	Beat::GetInstance()->SetMusic(L"zone1_1",L"zone1_1");

	//게임씬에서 사용할 오브젝트들 생성
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Ground, new Ground("Ground", L"Scene1_00"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Wall, new Wall("Wall", L"Scene1_01", L"Scene1_02"));
	Wall* tempWall = (Wall*)ObjectManager::GetInstance()->FindObject("Wall");
	tempWall->SetGroundPtr("Ground");	//생성 서순이 꼬일 경우를 대비해서 만듬
	
	//몬스터
	EnemyManager::LoadEnemy(L"Scene1_04");

	//아이템
	ItemManager::LoadItem(L"Scene1_03");

	//camera
	Camera* camera = new Camera();

	camera->SetTarget(ObjectManager::GetInstance()->FindObject("Player"));
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, camera);

	ObjectManager::GetInstance()->Init();
	mToolButton  = new Button(L"Tool",  L"Tool", 1200, 10, 200, 50, bind(&GameScene::Tool, this));

	//Hud
	HUD->SetPlayerPtr();
	HUD->SetHp();

	//테스트모드
	BEAT->SetIsLoop(true);

	//데이터저장
	PDATA->CopyPlayer(ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"));
}

void GameScene::Release(){
	SafeDelete(mToolButton);
	HUD->Release();
	BEAT->Release();
	ObjectManager::GetInstance()->AllDestroy();	//함수 구성은 같은데 Release를 사용하면 Player가 nullptr
	CameraManager::GetInstance()->SetMainCamera(nullptr);
}

void GameScene::Update(){
	ObjectManager::GetInstance()->Update();
	HUD->Update();
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
	HUD->Render(hdc);
	COMBO->Render(hdc);
	BEAT->Render(hdc);

	NextStage();
}

void GameScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"zone1_1");
	SoundPlayer::GetInstance()->Stop(L"zone1_1_shopkeeper");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
	PDATA->Release();
}

void GameScene::NextStage()
{
	Ground* ground = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground");
	Player* player = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (ground->NextStage(player->GetX() / TileSize, player->GetY() / TileSize))
	{
		SoundPlayer::GetInstance()->Stop(L"zone1_1");
		SoundPlayer::GetInstance()->Stop(L"zone1_1_shopkeeper");
		SceneManager::GetInstance()->LoadScene(L"BossScene");
		PDATA->CopyPlayer(ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"));
	}
}