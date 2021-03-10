#include "pch.h"
#include "Image.h"

#pragma comment(lib, "msimg32.lib")

void Image::LoadAllImage()//MainGame::Init에서 단 한번 실행 된다
{
	//{{ 버튼 관련 이미지 ~
	ImageManager::GetInstance()->LoadFromFile(L"Save", Resources(L"Save.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Load", Resources(L"Load.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Undo", Resources(L"Undo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Redo", Resources(L"Redo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Clear", Resources(L"Clear.bmp"), 88, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Play", Resources(L"Play.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Tool", Resources(L"Tool.bmp"), 72, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Ground", Resources(L"Ground.bmp"), 104, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Wall", Resources(L"Wall.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Deco", Resources(L"Deco.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Item", Resources(L"Item.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Object", Resources(L"Object.bmp"), 104, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Prev", Resources(L"Prev.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Next", Resources(L"Next.bmp"), 72, 48, 1, 2, false);
	//}}


	//{{ 맵 + 오브젝트 관련 이미지 ~
		//바닥
	ImageManager::GetInstance()->LoadFromFile(L"0", Resources(L"Stage1Ground.bmp"), 80, 96, 5, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"1", Resources(L"Stage2Ground.bmp"), 80, 96, 5, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"2", Resources(L"Stage3Ground.bmp"), 80, 96, 5, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"3", Resources(L"Stage4Ground.bmp"), 80, 96, 5, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"4", Resources(L"Stage5Ground.bmp"), 80, 96, 5, 6, true);
	//벽
	ImageManager::GetInstance()->LoadFromFile(L"5", Resources(L"Stage1Wall.bmp"), 80, 48, 5, 3, true);
	ImageManager::GetInstance()->LoadFromFile(L"6", Resources(L"Stage2Wall.bmp"), 80, 48, 5, 3, true);
	ImageManager::GetInstance()->LoadFromFile(L"7", Resources(L"Stage3Wall.bmp"), 80, 48, 5, 3, true);
	ImageManager::GetInstance()->LoadFromFile(L"8", Resources(L"Stage4Wall.bmp"), 80, 48, 5, 3, true);
	ImageManager::GetInstance()->LoadFromFile(L"9", Resources(L"Stage5Wall.bmp"), 80, 48, 5, 3, true);
	//장식
	ImageManager::GetInstance()->LoadFromFile(L"10", Resources(L"Stage1Deco.bmp"), 80, 64, 5, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"11", Resources(L"Stage2Deco.bmp"), 80, 64, 5, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"12", Resources(L"Stage3Deco.bmp"), 80, 64, 5, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"13", Resources(L"Stage4Deco.bmp"), 80, 64, 5, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"14", Resources(L"Stage5Deco.bmp"), 80, 64, 5, 4, true);
	//아이템
	ImageManager::GetInstance()->LoadFromFile(L"15", Resources(L"ItemList1.bmp"), 80, 144, 5, 9, true);
	ImageManager::GetInstance()->LoadFromFile(L"16", Resources(L"ItemList2.bmp"), 80, 144, 5, 9, true);
	//적
	ImageManager::GetInstance()->LoadFromFile(L"17", Resources(L"Enemy.bmp"), 80, 80, 5, 5, true);

	//}}
}