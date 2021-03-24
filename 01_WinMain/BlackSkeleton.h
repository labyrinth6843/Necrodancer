#pragma once
#include "Enemy.h"

class BlackSkeleton:public Enemy
{
public:

public:
	BlackSkeleton(const string& name, int x, int y);
	void GetDmg(int dmg)override;
};

