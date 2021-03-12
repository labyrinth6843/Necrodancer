#pragma once
#include "Image.h"
#include "GameObject.h"

class Player:public GameObject{
	Image* mHeadImage;
	Image* mBodyImage;

	int mHp;
	int indexX;
	int indexY;
	float destX;
	float destY;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Move(int x, int y);
};