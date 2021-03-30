#pragma once
#include "Item.h"

class Player;
class Hud
{
	Singleton(Hud);
private:
	struct Slot {
		Image* Image;
		float Left;
		float Top;

		Item* Item;
		bool IsShow = false;
	};
private:
	//아이템 슬롯
	Slot mItemSlot[4];

	float mHudSize;
	float mItemSize;

	//체력
	Player* mPlayerPtr;
	vector<FrameImage> mHp;
	float mMaxHp;
public:
	Hud();
	void Render(HDC hdc);
	void Update();
	void Release();

	//아이템 슬롯
	void ItemEquip(Item* item);		//아이템 슬롯에 추가 : mItemSlot 에 Item* 삽입 + IsShow = true
	void ItemRemove(Item* item);	//아이템을 슬롯에서 제거

	//체력
	void SetHp();
	//골드
public:
	void SetPlayerPtr()
	{
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"))
			mPlayerPtr = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	}


private:
	void SortSlot();	//아이템을 습득하거나 버릴때(현재는 없음)시 호출
};
#define HUD Hud::GetInstance()