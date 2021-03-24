#pragma once
#include "Enemy.h"

class WhiteSkeleton:public Enemy
{
public:

public:
	WhiteSkeleton(const string& name, int x, int y);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;
};

