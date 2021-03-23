#pragma once
#include "Enemy.h"
#include "Zombie.h"
#include "GreenSlime.h"
#include "BlueSlime.h"
#include "YellowSlime.h"
#include "WhiteSkeleton.h"
#include "YellowSkeleton.h"
#include "BlackSkeleton.h"

class EnemyManager
{
public:
	int EnemyImageKey;
	map<int, string> monsterMap;
public:
	void LoadEnemy();
};

