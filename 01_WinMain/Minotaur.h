#pragma once
#include "Enemy.h"

class Minotaur:public Enemy
{
public:
	bool mIsLeft;
	bool mIsAttack;
	bool mIsStun;

	int mStunBeat;

	POINT mRushDirection;
	
	vector<vector<Tile*>> mWallList;

	Animation* mLeftWallImpactAnimation;
	Animation* mRightWallImpactAnimation;
public:
	Minotaur(const string& name, int x, int y);

	void Move(int dirX, int dirY);
	POINT DestinationValidationCheck();

	void Dig(int indexX, int indexY);

	void Attack()override;
	void IsAttacked(int dmg)override;
	void Stun();

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};