#pragma once
#include "Enemy.h"

class RedBat :public Enemy
{
public:
	int mDestX;
	int mDestY;

	bool mIsLeft;
	bool mMoveBeat;
public:
	RedBat(const string& name, int x, int y);

	void Move(int destX, int destY);

	POINT DestinationValidationCheck();

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};