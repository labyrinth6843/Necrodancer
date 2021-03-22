#include "pch.h"
#include "EnemyManager.h"

void EnemyManager::LoadEnemy()
{
	vector<vector<Tile*>> mEnemyList;
	FileManager::LoadMap(L"Test04", mEnemyList, TileSize);

	int mMapSizeY = mEnemyList.size();
	int mMapSizeX = mEnemyList[0].size();

	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			if (mEnemyList[y][x]->GetImage() != NULL)
			{
				if (mEnemyList[y][x]->GetFrameIndexX() != 0 || mEnemyList[y][x]->GetFrameIndexY() != 0)
				{
					//이미지 프레임으로 뽑지 말고 이중 벡터로 좌표값 받아서 맵으로 해볼 생각 하기
					if (mEnemyList[y][x]->GetFrameIndexX() == 1 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						mEnemyList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"Zombie"));
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 2 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						GreenSlime* greenslime = new GreenSlime("GreenSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, (GameObject*)greenslime);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 3 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						BlueSlime* blueslime = new BlueSlime("BlueSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, (GameObject*)blueslime);
					}

					else if (mEnemyList[y][x]->GetFrameIndexX() == 4 && mEnemyList[y][x]->GetFrameIndexY() == 0) {
						YellowSlime* yellowslime = new YellowSlime("YellowSlime", x, y);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, (GameObject*)yellowslime);
					}
				}
			}
		}
	}
}
