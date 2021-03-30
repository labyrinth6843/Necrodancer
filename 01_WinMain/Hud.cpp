#include "pch.h"

Hud::Hud()
{
	mItemSlot[0] = { IMAGEMANAGER->FindImage(L"SlotShovel"), 50.f, 50.f, nullptr, false };	//»ð
	mItemSlot[1] = { IMAGEMANAGER->FindImage(L"SlotWeapon"), 50.f, 50.f, nullptr, false };	//¹«±â
	mItemSlot[2] = { IMAGEMANAGER->FindImage(L"SlotArmor"), 50.f, 50.f, nullptr, false };	//¹æ¾î±¸
	mItemSlot[3] = { IMAGEMANAGER->FindImage(L"SlotTorch"), 50.f, 50.f, nullptr, false };	//È¶ºÒ

	mSlotSize = 64;
	mItemSize = 50;
}

void Hud::Render(HDC hdc)
{
	if (mItemSlot[0].Item)
	{
		FrameImage temp = mItemSlot[0].Item->GetFrameImage();
		mItemSlot[0].Image->ScaleRender(hdc, mItemSlot[0].Left, mItemSlot[0].Top, mSlotSize, mSlotSize);
		temp.Image->ScaleFrameRender(hdc, mItemSlot[0].Left + 7.f, mItemSlot[0].Top + 12.f,
			temp.FrameX, temp.FrameY, mItemSize , mItemSize);
	}
	if (mItemSlot[1].Item)
	{
		FrameImage temp = mItemSlot[1].Item->GetFrameImage();
		mItemSlot[1].Image->ScaleRender(hdc, mItemSlot[1].Left, mItemSlot[1].Top, mSlotSize, mSlotSize);
		temp.Image->ScaleFrameRender(hdc, mItemSlot[1].Left + 7.f, mItemSlot[1].Top + 12.f,
			temp.FrameX, temp.FrameY, mItemSize, mItemSize);
	}
	if (mItemSlot[2].Item)
	{
		FrameImage temp = mItemSlot[2].Item->GetFrameImage();
		mItemSlot[2].Image->ScaleRender(hdc, mItemSlot[2].Left, mItemSlot[2].Top, mSlotSize, mSlotSize);
		temp.Image->ScaleFrameRender(hdc, mItemSlot[2].Left + 7.f, mItemSlot[2].Top + 12.f,
			temp.FrameX, temp.FrameY, mItemSize, mItemSize);
	}
	if (mItemSlot[3].Item)
	{
		FrameImage temp = mItemSlot[3].Item->GetFrameImage();
		mItemSlot[3].Image->ScaleRender(hdc, mItemSlot[3].Left, mItemSlot[3].Top, mSlotSize, mSlotSize);
		temp.Image->ScaleFrameRender(hdc, mItemSlot[3].Left + 7.f, mItemSlot[3].Top + 12.f,
			temp.FrameX, temp.FrameY , mItemSize, mItemSize);
	}
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

void Hud::SortSlot()
{
	float endLeft = 50.f;

	if (mItemSlot[0].IsShow)
	{
		mItemSlot[0].Left = endLeft;
		endLeft += 25.f + mSlotSize;
	}
	if (mItemSlot[1].IsShow)
	{
		mItemSlot[1].Left = endLeft;
		endLeft += 25.f + mSlotSize;
	}
	if (mItemSlot[2].IsShow)
	{
		mItemSlot[2].Left = endLeft;
		endLeft += 25.f + mSlotSize;
	}
	if (mItemSlot[3].IsShow)
	{
		mItemSlot[3].Left = endLeft;
		endLeft += 25.f + mSlotSize;
	}
}
