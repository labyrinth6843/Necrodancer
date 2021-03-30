#pragma once
#include "Enemy.h"

class BlueSlime:public Enemy
{
public:
	bool mIsLeft;
	bool mMoveBeat;
	bool mIsHop;

	Animation* mLeftIdleAnimation;
	Animation* mLeftMoveAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightMoveAnimation;
public:
	BlueSlime(const string& name, int x, int y);

	void Move(int destX, int destY);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Hop();

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};