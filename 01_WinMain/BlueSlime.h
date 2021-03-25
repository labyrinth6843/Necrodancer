#pragma once
#include "Enemy.h"

class BlueSlime:public Enemy
{
public:
	int mDestX;
	int mDestY;

	bool mIsLeft;
	bool mMoveBeat;

	Animation* mLeftIdleAnimation;
	Animation* mLeftMoveAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightMoveAnimation;
public:
	BlueSlime(const string& name, int x, int y);

	void Move(int destX, int destY);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};