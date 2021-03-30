#include "pch.h"

Hud::Hud()
{
	mItemSlot[0] = { IMAGEMANAGER->FindImage(L"SlotShovel"), 50.f, 50.f, nullptr, false };	//삽
	mItemSlot[1] = { IMAGEMANAGER->FindImage(L"SlotWeapon"), 50.f, 50.f, nullptr, false };	//무기
	mItemSlot[2] = { IMAGEMANAGER->FindImage(L"SlotArmor"), 50.f, 50.f, nullptr, false };	//방어구
	mItemSlot[3] = { IMAGEMANAGER->FindImage(L"SlotTorch"), 50.f, 50.f, nullptr, false };	//횃불

	mHudSize = 64;
	mItemSize = 50;
}

void Hud::Render(HDC hdc)
{
	//아이템 슬롯
	for(int i = 0; i < 4; ++i)
	{
		if (mItemSlot[i].Item)
		{
			FrameImage temp = mItemSlot[i].Item->GetFrameImage();
			mItemSlot[i].Image->ScaleRender(hdc, mItemSlot[i].Left, mItemSlot[i].Top, mHudSize, mHudSize);
			temp.Image->ScaleFrameRender(hdc, mItemSlot[i].Left + 7.f, mItemSlot[i].Top + 12.f,
				temp.FrameX, temp.FrameY, mItemSize, mItemSize);
		}
	}
	for (int i = 0; i < mHp.size(); ++i)
	{
		if (mHp[i].Image)
		{
			mHp[i].Image->ScaleFrameRender(hdc, mHp[i].PositionX, mHp[i].PositionY, mHp[i].FrameX, mHp[i].FrameY, mHudSize, mHudSize);
		}
	}
}

void Hud::Update()
{
}

void Hud::Release()
{
	mItemSlot[0].Item = nullptr;
	mItemSlot[1].Item = nullptr;
	mItemSlot[2].Item = nullptr;
	mItemSlot[3].Item = nullptr;

	mItemSlot[0].IsShow = false;
	mItemSlot[1].IsShow = false;
	mItemSlot[2].IsShow = false;
	mItemSlot[3].IsShow = false;

	mPlayerPtr = nullptr;
}

void Hud::ItemEquip(Item* item)
{
	switch(item->GetType())
	{
	case ItemType::Shovel:
		mItemSlot[0].Item = item;
		mItemSlot[0].IsShow = true;
		break;
	case ItemType::Weapon:
		mItemSlot[1].Item = item;
		mItemSlot[1].IsShow = true;
		break;
	case ItemType::Armor:
		mItemSlot[2].Item = item;
		mItemSlot[2].IsShow = true;
		break;
	case ItemType::Torch:
		mItemSlot[3].Item = item;
		mItemSlot[3].IsShow = true;
		break;
	}
	SortSlot();
}

void Hud::ItemRemove(Item* item)
{
	switch (item->GetType())
	{
	case ItemType::Shovel:
		mItemSlot[0].Item = nullptr;
		mItemSlot[0].IsShow = false;
		break;
	case ItemType::Weapon:
		mItemSlot[1].Item = nullptr;
		mItemSlot[1].IsShow = false;
		break;
	case ItemType::Armor:
		mItemSlot[2].Item = nullptr;
		mItemSlot[2].IsShow = false;
		break;
	case ItemType::Torch:
		mItemSlot[3].Item = nullptr;
		mItemSlot[3].IsShow = false;
		break;
	}
	SortSlot();
}

void Hud::SetHp()
{
	//GameScene Init 혹은 최대체력 상태에서 체력칸을 늘릴때 호출,
	mMaxHp = mPlayerPtr->GetHp();
	for (float i = 0.f; i < mMaxHp / 2.f; i += 1.f)
	{
		FrameImage temp = { IMAGEMANAGER->FindImage(L"HUDHealth"), WINSIZEX - 200.f - mHudSize * i, 50.f,  0, 0, mHudSize, mHudSize };
		mHp.push_back(temp);
	}
}

void Hud::SortSlot()
{
	float endLeft = 50.f;

	if (mItemSlot[0].IsShow)
	{
		mItemSlot[0].Left = endLeft;
		endLeft += 25.f + mHudSize;
	}
	if (mItemSlot[1].IsShow)
	{
		mItemSlot[1].Left = endLeft;
		endLeft += 25.f + mHudSize;
	}
	if (mItemSlot[2].IsShow)
	{
		mItemSlot[2].Left = endLeft;
		endLeft += 25.f + mHudSize;
	}
	if (mItemSlot[3].IsShow)
	{
		mItemSlot[3].Left = endLeft;
		endLeft += 25.f + mHudSize;
	}
}
