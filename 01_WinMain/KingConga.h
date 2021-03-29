#pragma once
#include "Enemy.h"

class KingConga:public Enemy
{
public:
	Image* mThroneImage;

	Animation* mIdleAnimation;
	Animation* mMoveAnimation;

	float InitX;
	float InitY;
public:
	KingConga(const string& name, int x, int y);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Move(int dirX, int dirY);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};