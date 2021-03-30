#pragma once
#include "Enemy.h"

class YellowSlime:public Enemy
{
public:
	//매 움직임마다 1씩 증가하며 4이하로 고정되는 값
	//이 값에 따라 시계 방향, 반시계 방향으로 돌아가는 동작 중 다음 박자때 움직일 방향을 산출
	int mMoveState;

	bool mClockWise;
	bool mIsLeft;
public:
	YellowSlime(const string& name, int x, int y);

	POINT DestinationValidationCheck(int moveState);
	void Move(int dirX, int dirY);

	void Attack()override;
	void IsAttacked(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};