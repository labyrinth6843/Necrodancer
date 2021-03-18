#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Animation.h"
class Item:public GameObject
{

public:
	Item(const string& name);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};

