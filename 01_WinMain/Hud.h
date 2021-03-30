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
	//������ ����
	Slot mItemSlot[4];

	float mHudSize;
	float mItemSize;

	//ü��
	Player* mPlayerPtr;
	vector<FrameImage> mHp;
	float mMaxHp;
public:
	Hud();
	void Render(HDC hdc);
	void Update();
	void Release();

	//������ ����
	void ItemEquip(Item* item);		//������ ���Կ� �߰� : mItemSlot �� Item* ���� + IsShow = true
	void ItemRemove(Item* item);	//�������� ���Կ��� ����

	//ü��
	void SetHp();
	//���
public:
	void SetPlayerPtr()
	{
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"))
			mPlayerPtr = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	}


private:
	void SortSlot();	//�������� �����ϰų� ������(����� ����)�� ȣ��
};
#define HUD Hud::GetInstance()