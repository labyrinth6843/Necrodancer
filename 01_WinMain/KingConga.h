#pragma once
#include "Enemy.h"

class KingConga:public Enemy
{
public:
	Image* mThroneImage;

	Animation* mIdleAnimation;
	Animation* mMoveAnimation;
public:
	KingConga(const string& name, int x, int y);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};