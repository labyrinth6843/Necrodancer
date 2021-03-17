#pragma once
#include "Image.h"
#include "GameObject.h"
#include "Animation.h"

class Player:public GameObject{
	Image* mHeadImage;
	Image* mBodyImage;

	bool mIsArmor = false;
	int mArmorType = 0;

	bool direction = true;

	Animation* mHeadLeftAnimation;
	Animation* mHeadRightAnimation;
	Animation* mBodyLeftAnimation;
	Animation* mBodyRightAnimation;

	Animation* mCurrentHeadAnimation;
	Animation* mCurrentBodyAnimation;
	
	float mHp = 6;
	float mDmg = 1;
	float mDef = 0;

	int mCoin = 0;
	int initIndexX;
	int initIndexY;
	float destIndexX;
	float destIndexY;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Move(int x, int y);
	void Dig();
	void Attack();
	void Equip();

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	float GetDmg() { return mDmg; }

	float GetDef() { return mDef; }

	POINT GetPos() { return { initIndexX, initIndexY }; }
	float GetPosX() { return initIndexX; }
	float GetPosY() { return initIndexY; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};