#pragma once
#include "Image.h"
#include "GameObject.h"
#include "Animation.h"

enum class WeaponType {
	None,
	Dagger,
	Broadsword,
	Spear,
	Rapier,
	Bow,
	End
};

enum class ArmorType {
	None,
	Leather,
	Chainmail,
	Plate,
	HeavyPlate,
	Obsidian,
	Glass,
	Karate,
	End
};

class Player:public GameObject{
	Image* mHeadImage;
	Image* mBodyImage;

	bool direction = true;

	Animation* mHeadLeftAnimation;
	Animation* mHeadRightAnimation;
	Animation* mBodyLeftAnimation;
	Animation* mBodyRightAnimation;

	Animation* mCurrentHeadAnimation;
	Animation* mCurrentBodyAnimation;
	
	float mHp = 6;
	float mDef = 0;
	int mShovelPower = 1;
	int mWeaponPower = 1;
	bool mIsArmor = false;
	ArmorType mArmorType = ArmorType::None;
	WeaponType mWeaponType = WeaponType::Dagger;

	int mCoin = 0;
	float StartX;
	float StartY;
	int StartIndexX;
	int StartIndexY;
	float EndX;
	float EndY;
	int EndIndexX;
	int EndIndexY;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Move(int x, int y);
	void Dig(GameObject* object);
	void Attack(GameObject* object);
	void Equip(GameObject* object);

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	float GetDmg() { return mWeaponPower; }
	float GetDef() { return mDef; }

	POINT GetIndex() { return { StartIndexX, StartIndexY }; }
	float GetndexX() { return StartIndexX; }
	float GetndexY() { return StartIndexY; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};