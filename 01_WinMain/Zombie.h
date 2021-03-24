#pragma once
#include "Enemy.h"

class Zombie:public Enemy
{
public:
	Zombie(const string& name, int x, int y);

	void Attack(int destX, int destY)override;
	void IsAttacked(int dmg)override;
};