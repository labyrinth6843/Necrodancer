#include "pch.h"
#include "EnemyManager.h"

void EnemyManager::LoadEnemy()
{
	vector<vector<Tile*>> mEnemyList;
	FileManager::LoadMap(L"Test04", mEnemyList, TileSize);

	int mMapSizeY = mEnemyList.size();
	int mMapSizeX = mEnemyList[0].size();

	//여유 있으면 각 프레임 정보를 저장하는 키를 따로 빼서
	//스위치문으로 돌릴 것
	//프레임 안 맞는 거 있으면 계속 돌아서 별로

	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			if (mEnemyList[y][x]->GetImage() != NULL)
			{
				if (mEnemyList[y][x]->GetFrameIndexX() != 0 || mEnemyList[y][x]->GetFrameIndexY() != 0)
				{
					if (mEnemyList[y][x]->GetFrameIndexX() == 1 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						Zombie* zombie = new Zombie("Zombie", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)zombie);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 2 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						GreenSlime* greenslime = new GreenSlime("GreenSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)greenslime);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 3 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						BlueSlime* blueslime = new BlueSlime("BlueSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)blueslime);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 4 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						YellowSlime* yellowslime = new YellowSlime("YellowSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)yellowslime);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 0 && mEnemyList[y][x]->GetFrameIndexY() == 1) {
						WhiteSkeleton* whiteskeleton = new WhiteSkeleton("WhiteSkeleton", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)whiteskeleton);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 1 && mEnemyList[y][x]->GetFrameIndexY() == 1) {
						YellowSkeleton* yellowskeleton = new YellowSkeleton("YellowSkeleton", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)yellowskeleton);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 2 && mEnemyList[y][x]->GetFrameIndexY() == 1) {
						BlackSkeleton* blackskeleton = new BlackSkeleton("BlackSkeleton", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)blackskeleton);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 3 && mEnemyList[y][x]->GetFrameIndexY() == 1) {
						GreyBat* greybat = new GreyBat("Bat", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)greybat);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 4 && mEnemyList[y][x]->GetFrameIndexY() == 1) {
						RedBat* redbat = new RedBat("RedBat", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)redbat);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 0 && mEnemyList[y][x]->GetFrameIndexY() == 2) {
						DireBat* direbat = new DireBat("DireBat", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)direbat);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 1 & mEnemyList[y][x]->GetFrameIndexY() == 2) {
						//Minotaur* minotaur = new Minotaur("Minotaur", x, y);
						//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)minotaur);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 2 & mEnemyList[y][x]->GetFrameIndexY() == 2) {
						//Nightmare* nightmare = new Nightmare("Nightmare", x, y);
						//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, (GameObject*)nightmare);
					}
					else if (mEnemyList[y][x]->GetFrameIndexX() == 3 && mEnemyList[y][x]->GetFrameIndexY() == 2) {
						//Dragon* dragon = new Dragon("Dragon", x, y);
						//ObjectManager::GetInstance()->AddObejct(ObjectLayer::Enemy, (GameObject*)dragon);
					}
				}
			}
		}
	}
}