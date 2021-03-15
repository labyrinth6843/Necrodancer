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

	ImageManager::GetInstance()->LoadFromFile(L"Paint", Resources(L"Paint.bmp"), 88, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Pencil", Resources(L"Pencil.bmp"), 104, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Select", Resources(L"Select.bmp"), 104, 48, 1, 2, false);
	//}}

	//{{ 맵 + 오브젝트 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"SelectTile", Resources(L"SelectTile.bmp"), 32, 32, true);
	ImageManager::GetInstance()->LoadFromFile(L"Black", Resources(L"black.bmp"), 1183, 736, true);
	////바닥
	//ImageManager::GetInstance()->LoadFromFile(L"0", Resources(L"Stage1Ground.bmp"), 80, 96, 5, 6, true);
	//ImageManager::GetInstance()->LoadFromFile(L"1", Resources(L"Stage2Ground.bmp"), 80, 96, 5, 6, true);
	//ImageManager::GetInstance()->LoadFromFile(L"2", Resources(L"Stage3Ground.bmp"), 80, 96, 5, 6, true);
	//ImageManager::GetInstance()->LoadFromFile(L"3", Resources(L"Stage4Ground.bmp"), 80, 96, 5, 6, true);
	//ImageManager::GetInstance()->LoadFromFile(L"4", Resources(L"Stage5Ground.bmp"), 80, 96, 5, 6, true);
	////벽
	//ImageManager::GetInstance()->LoadFromFile(L"5", Resources(L"Stage1Wall.bmp"), 80, 48, 5, 3, true);
	//ImageManager::GetInstance()->LoadFromFile(L"6", Resources(L"Stage2Wall.bmp"), 80, 48, 5, 3, true);
	//ImageManager::GetInstance()->LoadFromFile(L"7", Resources(L"Stage3Wall.bmp"), 80, 48, 5, 3, true);
	//ImageManager::GetInstance()->LoadFromFile(L"8", Resources(L"Stage4Wall.bmp"), 80, 48, 5, 3, true);
	//ImageManager::GetInstance()->LoadFromFile(L"9", Resources(L"Stage5Wall.bmp"), 80, 48, 5, 3, true);
	////장식
	//ImageManager::GetInstance()->LoadFromFile(L"10", Resources(L"Stage1Deco.bmp"), 80, 64, 5, 4, true);
	//ImageManager::GetInstance()->LoadFromFile(L"11", Resources(L"Stage2Deco.bmp"), 80, 64, 5, 4, true);
	//ImageManager::GetInstance()->LoadFromFile(L"12", Resources(L"Stage3Deco.bmp"), 80, 64, 5, 4, true);
	//ImageManager::GetInstance()->LoadFromFile(L"13", Resources(L"Stage4Deco.bmp"), 80, 64, 5, 4, true);
	//ImageManager::GetInstance()->LoadFromFile(L"14", Resources(L"Stage5Deco.bmp"), 80, 64, 5, 4, true);
	////아이템
	//ImageManager::GetInstance()->LoadFromFile(L"15", Resources(L"ItemList1.bmp"), 80, 144, 5, 9, true);
	//ImageManager::GetInstance()->LoadFromFile(L"16", Resources(L"ItemList2.bmp"), 80, 144, 5, 9, true);
	////적
	//ImageManager::GetInstance()->LoadFromFile(L"17", Resources(L"Enemy.bmp"), 80, 80, 5, 5, true);
	//}}

	//{{ 팔레트 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"GroundPallet", Resources(L"Pallet/GroundPallet.bmp"), 130, 26, 5, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"WallPallet", Resources(L"Pallet/WallPallet.bmp"), 130, 130, 5, 5, true);
	ImageManager::GetInstance()->LoadFromFile(L"ItemPallet", Resources(L"Pallet/ItemPallet.bmp"), 130, 234, 5, 9, true);
	ImageManager::GetInstance()->LoadFromFile(L"MonsterPallet", Resources(L"Pallet/MonsterPallet.bmp"), 130, 52, 5, 2, true);
	//}}

	//{{ 아이템 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Weapon", Resources(L"Item/Weapon.bmp"), 243, 324, 9, 12, true);
	ImageManager::GetInstance()->LoadFromFile(L"Armor", Resources(L"Item/Armor.bmp"), 260, 52, 10, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Torch", Resources(L"Item/Torch.bmp"), 189, 54, 7, 2, true);
	//}}

	//{{ 캐릭터 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Head", Resources(L"Character/Head.bmp"), 112, 22, 8, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Body", Resources(L"CharacterBody.bmp"), 136, 150, 8, 10, true);
	//}}

	//{{ 적 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Zombie", Resources(L"Enemy/Zombie.bmp"), 320, 150, 16, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime1", Resources(L"Enemy/Slime1.bmp"), 104, 104, 4, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime2", Resources(L"Enemy/Slime2.bmp"), 104, 104, 4, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime3", Resources(L"Enemy/Slime3.bmp"), 208, 104, 8, 5, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton1", Resources(L"Enemy/Skeleton1.bmp"), 208, 208, 8, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton2", Resources(L"Enemy/Skeleton2.bmp"), 234, 208, 9, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton3", Resources(L"Enemy/Skeleton3.bmp"), 234, 208, 9, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Nightmare1", Resources(L"Enemy/Nightmare1.bmp"), 285, 84, 5, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Nightmare2", Resources(L"Enemy/Nightmare2.bmp"), 285, 84, 5, 2, true);
	//}}

	//{{ NPC 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"ShopKeeper", Resources(L"NPC/ShopKeeper.bmp"), 376, 76, 8, 2, true);
	//}}

	//{{ 맵 타일
	ImageManager::GetInstance()->LoadFromFile(L"GroundTile", Resources(L"Tile/GroundTile.bmp"), 156, 52, 6, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"WallTile", Resources(L"Tile/WallTile.bmp"), 125, 240, 5, 5, true);
	//}}
}