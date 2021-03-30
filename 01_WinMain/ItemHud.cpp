#include "pch.h"

void Hud::ItemEquip(Item* item)
{
	switch (item->GetType())
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