﻿#include "pch.h"
#include "ItemManager.h"
#include "Item.h"
#include "Weapon.h"
#include "Ground.h"
void ItemManager::LoadItem(wstring filename)	//filename : 로드할 맵의 아이템
{
	Ground* gptr = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground,"Ground");
	vector<vector<Tile*>> itemList;	//Test03.txt
	//아이템을 생성할 위치 정보를 담은 타일맵 로드
	FileManager::LoadMap(L"Test03", itemList, TileSize, TileSize);
	int mapSizeY = itemList.size();
	int mapSizeX = itemList.size();

	//카메라 클리핑을 위한 정보 -> 다른방법도 생각해봄 일단 보류

	//아이템 생성
	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			if (itemList[y][x]->GetImage())
			{
				//팔레트의 빈 이미지가 채워진 타일이라면
				if (itemList[y][x]->GetFrameIndexX() == 0 && itemList[y][x]->GetFrameIndexY() == 0)
				{
					//이미지를 비우고 컨티뉴
					itemList[y][x]->SetImage(nullptr);
					continue;
				}

				//빈 이미지가 채워진 타일이라면 아이템을 생성한다
				//무기
				if (itemList[y][x]->GetFrameIndexY() > 2 && itemList[y][x]->GetFrameIndexY() < 9)
				{
					WeaponMaterial mt;
					//무기의 재질을 판별한다
					switch (itemList[y][x]->GetFrameIndexY())
					{
					case 3:
						mt = WeaponMaterial::Basic;
						break;
					case 4:
						mt = WeaponMaterial::Blood;
						break;
					case 5:
						mt = WeaponMaterial::Glass;
						break;
					case 6:
						mt = WeaponMaterial::Gold;
						break;
					case 7:
						mt = WeaponMaterial::Titanium;
						break;
					case 8:
						mt = WeaponMaterial::Obsidian;
						break;

					}
					Weapon* temp;
					//무기의 종류를 판별하고 생성한다
					switch (itemList[y][x]->GetFrameIndexX())
					{
					case 0:	//대거
						temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Dagger, mt, ItemState::NotOwned);
						temp->SetGroundPtr(gptr);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Item,(GameObject*)temp);
						break;
					case 1:	//브로드소드
						temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Broadsword, mt, ItemState::NotOwned);
						temp->SetGroundPtr(gptr);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
						break;
					case 2: //레이피어
						temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Rapier, mt, ItemState::NotOwned);
						temp->SetGroundPtr(gptr);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
						break;
					case 3: //창
						temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Spear, mt, ItemState::NotOwned);
						temp->SetGroundPtr(gptr);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
						break;
					case 4: //롱소드
						temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Longsword, mt, ItemState::NotOwned);
						temp->SetGroundPtr(gptr);
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
						break;
					}
				}
				//방어구
				//토치(횃불)
			}
		}
	}
}
