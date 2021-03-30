#pragma once
#include "Enemy.h"

class BlackSkeleton:public Enemy
{
public:
	bool mIsLeft;
	bool mMoveBeat;
	bool mIsHop;

	Animation* mUpLeftReadyAnimation;
	Animation* mUpLeftMoveAnimation;

	Animation* mUpRightReadyAnimation;
	Animation* mUpRightMoveAnimation;

	Animation* mDownLeftReadyAnimation;
	Animation* mDownLeftMoveAnimation;

	Animation* mDownRightReadyAnimation;
	Animation* mDownRightMoveAnimation;
public:
	BlackSkeleton(const string& name, int x, int y);

	void Move(int dirX, int dirY);
	POINT DirectionDecision();

	void Hop();

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};