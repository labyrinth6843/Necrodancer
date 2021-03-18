#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Animation.h"

class Wall:public GameObject
{
	int mDigLevel;
public:
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	int GetDigLevel() { return mDigLevel; }
};

