#pragma once
#include"GameObject.h"
#include"Image.h"
#include"Animation.h"
#include"Camera.h"
#include "Ground.h"
#include "Wall.h"
#include "Player.h"

class Enemy:public GameObject
{
protected:
	Image* mImage;
	Ground* mGroundPtr;
	Wall* mWallPtr;
	Player* mPlayerPtr;

	Animation* mCurrentAnimation;
	Animation* mLeftAnimation;
	Animation* mRightAnimation;

	float mInitX;
	float mInitY;
	float mDestX;
	float mDestY;
	int mDestIndexX;
	int mDestIndexY;

	float mMoveTime;
	float mCorrectionY;
	float mJumpPower;
	bool mIsMove;
	bool mIsVisible;
	float mOpacity;

	int mDirection;
	int mHp;
	int mAtk;
	int mCoin;
public:
	Enemy(const string& name);

	virtual void Init()override;
	virtual void Update()override;
	virtual void Release()override;
	virtual void Render(HDC hdc)override;

	bool WallCheck(int x, int y);
	virtual void Attack() = 0;
	virtual void IsAttacked(int dmg) = 0;

	void SetGroundPtr(Ground* groundPtr) { mGroundPtr = groundPtr; }
	void SetWallPtr(Wall* wallPtr) { mWallPtr = wallPtr; }
	void SetPlayerPtr(Player* playerPtr) { mPlayerPtr = playerPtr; }

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }
};