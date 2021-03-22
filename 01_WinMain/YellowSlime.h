#pragma once
#include "Enemy.h"

class YellowSlime:public Enemy
{
public:
	int direction;
	int destX;
	int destY;

public:
	YellowSlime(const string& name, int x, int y);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};

