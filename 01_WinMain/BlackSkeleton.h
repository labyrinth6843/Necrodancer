#pragma once
#include "Enemy.h"

class BlackSkeleton:public Enemy
{
public:
	Animation* mUpLeftAnimation;
	Animation* mUpRightAnimation;
	Animation* mDownLeftAnimation;
	Animation* mDownRightAnimation;
public:
	BlackSkeleton(const string& name, int x, int y);

	void Move(int dirX, int dirY);
	POINT DestinationValidationCheck();

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};