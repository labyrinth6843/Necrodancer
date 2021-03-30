#pragma once
#include "Enemy.h"

class WhiteSkeleton:public Enemy
{
public:
	bool mIsLeft;
	bool mMoveBeat;
	
	Animation* mUpLeftReadyAnimation;
	Animation* mUpLeftMoveAnimation;

	Animation* mUpRightReadyAnimation;
	Animation* mUpRightMoveAnimation;

	Animation* mDownLeftReadyAnimation;
	Animation* mDownLeftMoveAnimation;

	Animation* mDownRightReadyAnimation;
	Animation* mDownRightMoveAnimation;
public:
	WhiteSkeleton(const string& name, int x, int y);

	void Move(int dirX, int dirY);
	POINT DirectionDecision();

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};