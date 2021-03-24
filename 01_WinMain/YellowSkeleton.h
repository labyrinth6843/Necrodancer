#pragma once
#include "Enemy.h"

class YellowSkeleton:public Enemy
{
public:
	
public:
	YellowSkeleton(const string& name, int x, int y);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;
};