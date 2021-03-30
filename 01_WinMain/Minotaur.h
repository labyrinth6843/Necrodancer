#pragma once
#include "Enemy.h"
class Minotaur:public Enemy
{
public:
	bool mIsLeft;

	vector<vector<Tile*>> mWallList;

	vector<Tile*>mRouteList;

	Animation* mLeftWallImpactAnimation;
	Animation* mRightWallImpactAnimation;
public:
	Minotaur(const string& name, int x, int y);

	void Move(int dirX, int dirY);
	POINT DestinationValidationCheck();

	void Dig(int indexX, int indexY);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};