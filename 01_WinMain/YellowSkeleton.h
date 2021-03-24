#pragma once
#include "Enemy.h"

class YellowSkeleton:public Enemy
{
public:
	
public:
	YellowSkeleton(const string& name, int x, int y);

	void GetDmg(int dmg)override;
};

