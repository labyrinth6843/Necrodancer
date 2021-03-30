#include "pch.h"
#include "ItemManager.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Ground.h"
void ItemManager::LoadItem(wstring filename)	//filename : 로드할 맵의 아이템
{
	vector<vector<Tile*>> itemList;	//Test03.txt
	//아이템을 생성할 위치 정보를 담은 타일맵 로드
	FileManager::LoadMap(L"Test03", itemList, TileSize, TileSize);
	int mapSizeY = itemList.size();
	int mapSizeX = itemList.size();

	//아이템 생성
	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			if (itemList[y][x]->GetImage())
			{
				wstring palletname = itemList[y][x]->GetImage()->GetKeyName();

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
					if (palletname == L"ItemPallet1")
					{
						switch (itemList[y][x]->GetFrameIndexX())
						{
						case 0:	//대거
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Dagger, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 1:	//브로드소드
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Broadsword, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 2: //레이피어
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Rapier, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 3: //창
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Spear, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 4: //롱소드
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Longsword, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;

						}
					}
					else if (palletname == L"ItemPallet2")
					{
						switch (itemList[y][x]->GetFrameIndexX())
						{
						case 0:	//활
							temp = new Weapon(itemList[y][x]->GetX(), itemList[y][x]->GetY(), WeaponType::Bow, mt, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						}
					}
					
				}
				//방어구
				if (itemList[y][x]->GetFrameIndexY() >= 0 && itemList[y][x]->GetFrameIndexY() < 2)
				{
					Armor* temp;
					if (itemList[y][x]->GetFrameIndexY() == 0)
					{
						switch (itemList[y][x]->GetFrameIndexX())
						{
						case 1:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Leather, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 2:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Chain, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 3:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Plate, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 4:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::HeavyPlate, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						default:
							break;
						}
					}
					else if (itemList[y][x]->GetFrameIndexY() == 1)
					{
						switch (itemList[y][x]->GetFrameIndexX())
						{
						case 1:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Karate, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 2:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Glass, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						case 3:
							temp = new Armor(itemList[y][x]->GetX(), itemList[y][x]->GetY(), ArmorMaterial::Obsidian, ItemState::NotOwned);
							ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)temp);
							break;
						default:
							break;
						}
					}
				}
				//토치(횃불)
			}
		}
	}
}
