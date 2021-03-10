#pragma once
#include "Image.h"
#include "Animation.h"
#include "GameObject.h"
enum class PlayerState {
	Idle,
	Walk,
	Death,
	Attack,
	Use,
	Scroll,
	Fly,
	End
};

class Player:public GameObject{
	Image* mImage;

	Animation* mIdleAnimation;
	Animation* mWalkAnimation;
	Animation* mDeathAnimation;
	Animation* mAttackAnimation;
	Animation* mUseAnimation;
	Animation* mScrollAnimation;
	Animation* mFlyAnimation;
	
	PlayerState mPlayerState;

	Animation* mCurrentAnimation;

	int indexX;
	int indexY;
	float destX;
	float destY;
	float mAngle;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Move(int x, int y);
};