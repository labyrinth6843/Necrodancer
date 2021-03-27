#pragma once
#include "Enemy.h"
class Minotaur:public Enemy
{
public:
	Animation* mLeftWallImpactAnimation;
	Animation* mRightWallImpactAnimation;
public:
	Minotaur(const string& name, int x, int y);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};