#pragma once
#include "Enemy.h"

class BlueSlime:public Enemy
{
public:
	int destX;
	int destY;

public:
	BlueSlime(const string& name, int x, int y);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};