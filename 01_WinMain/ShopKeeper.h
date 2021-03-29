#pragma once
#include "Enemy.h"

class ShopKeeper:public Enemy
{
public:
	Animation* mIdleAnimation;
	Animation* mSingAnimation;
public:
	ShopKeeper(const string& name, int x, int y);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};