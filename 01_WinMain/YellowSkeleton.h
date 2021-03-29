#pragma once
#include "Enemy.h"

class YellowSkeleton:public Enemy
{
public:
	Animation* mUpLeftAnimation;
	Animation* mUpRightAnimation;
	Animation* mDownLeftAnimation;
	Animation* mDownRightAnimation;
public:
	YellowSkeleton(const string& name, int x, int y);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};