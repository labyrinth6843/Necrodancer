#pragma once
#include "Enemy.h"

class BlueSlime:public Enemy
{
public:
	int destX;
	int destY;

public:
	BlueSlime(const string& name, int x, int y);

	void Move(int destX, int destY);
	void Attack();

	void GetDmg(int dmg)override;

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};