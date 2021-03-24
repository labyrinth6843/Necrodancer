#pragma once
#include "Enemy.h"

class BlackSkeleton:public Enemy
{
public:

public:
	BlackSkeleton(const string& name, int x, int y);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;
};

