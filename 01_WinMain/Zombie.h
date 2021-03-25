#pragma once
#include "Enemy.h"

class Zombie:public Enemy
{
public:
	Animation* mUpLeftAnimation;
	Animation* mUpRightAnimation;
	Animation* mDownLeftAnimation;
	Animation* mDownRightAnimation;

	bool mIsLeft;
	bool mMoveBeat;
public:
	Zombie(const string& name, int x, int y);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;
	
	POINT MoveDirection(int direction);
	void Move(int dirX, int dirY);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};