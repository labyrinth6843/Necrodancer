#pragma once
class Item;
class Weapon;
class ItemManager
{
	int mMinIndexX;
	int mMinIndexY;
	int mMaxIndexX;
	int mMaxIndexY;

public:
	void LoadItem(wstring filename);
};

