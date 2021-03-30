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

	void ItemEquip(Item* item);		//������ ���Կ� �߰� : mItemSlot �� Item* ���� + IsShow = true
	void ItemRemove(Item* item);	//�������� ���Կ��� ����

private:
	void SortSlot();	//�������� �����ϰų� ������(����� ����)�� ȣ��
};
#define HUD Hud::GetInstance()