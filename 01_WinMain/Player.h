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
	int initindexX;
	int initindexY;
	float destindexX;
	float destindexY;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Move(int x, int y);

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	float GetDmg() { return mDmg; }

	float GetDef() { return mDef; }

	POINT GetCord() { return { initindexX, initindexY }; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};