#pragma once
#include"GameObject.h"
#include"Image.h"
#include"Animation.h"
#include"Camera.h"

class Enemy:public GameObject
{
public:
	Image* mImage;

	Animation* mCurrentAnimation;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;

	int direction;
	int mHp;
	int mAtk;
	int mCoin;
public:
	Enemy(const string& name);

	virtual void Init()override;
	virtual void Update()override;
	virtual void Release()override;
	virtual void Render(HDC hdc)override;
	
	virtual void GetDmg(int dmg) = 0;

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }
};

