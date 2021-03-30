#pragma once
#include "Item.h"
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
	Slot mItemSlot[4];

	float mSlotSize;
	float mItemSize;
public:
	Hud();
	void Render(HDC hdc);
	void Release();

	void ItemEquip(Item* item);		//아이템 슬롯에 추가 : mItemSlot 에 Item* 삽입 + IsShow = true
	void ItemRemove(Item* item);	//아이템을 슬롯에서 제거

private:
	void SortSlot();	//아이템을 습득하거나 버릴때(현재는 없음)시 호출
};
#define HUD Hud::GetInstance()