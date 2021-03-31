#include "pch.h"
#include "BossScene.h"
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
void BossScene::Init() {
	Beat::GetInstance()->Init();

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, new Player("Player", 10, 10));
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");

	SoundPlayer::GetInstance()->Play(L"kingconga", 0.2f);
	Beat::GetInstance()->SetMusic(L"kingconga", L"boss_1");

	//���Ӿ����� ����� ������Ʈ�� ����
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Ground, new Ground("Ground", L"Test00"));
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Wall, new Wall("Wall", L"Test01", L"Test02"));
	Wall* tempWall = (Wall*)ObjectManager::GetInstance()->FindObject("Wall");
	tempWall->SetGroundPtr("Ground");	//���� ������ ���� ��츦 ����ؼ� ����

	//����
	EnemyManager::LoadEnemy(L"Test04");

	//������
	ItemManager::LoadItem(L"Test03");

	//camera
	Camera* camera = new Camera();

	camera->SetTarget(ObjectManager::GetInstance()->FindObject("Player"));
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, camera);

	ObjectManager::GetInstance()->Init();
	mToolButton = new Button(L"Tool", L"Tool", 550, 50, 200, 50, bind(&BossScene::Tool, this));

	//Hud
	HUD->SetPlayerPtr();
	HUD->SetHp();

	//�׽�Ʈ���
	BEAT->SetIsLoop(true);

	//���������� �׽�Ʈ
	PDATA->LoadPlayer(ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"));
}

void BossScene::Release() {
	SafeDelete(mToolButton);
	HUD->Release();
	BEAT->Release();
	ObjectManager::GetInstance()->AllDestroy();	//�Լ� ������ ������ Release�� ����ϸ� Player�� nullptr
	CameraManager::GetInstance()->SetMainCamera(nullptr);
}

void BossScene::Update() {
	ObjectManager::GetInstance()->Update();
	HUD->Update();
	BEAT->Update();
	mToolButton->Update();
}

void BossScene::Render(HDC hdc) {
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

void BossScene::Tool() {
	SoundPlayer::GetInstance()->Stop(L"kingconga");
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
	PDATA->Release();
}

void BossScene::NextStage()
{
	Ground* ground = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground");
	Player* player = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (ground->NextStage(player->GetX() / TileSize, player->GetY() / TileSize))
	{
		Tool();
		PDATA->CopyPlayer(ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"));
	}
}