#pragma once
#include"GameObject.h"
#include"Image.h"
#include"Animation.h"

class Enemy:public GameObject
{
	int mHp;
	int mAtk;
	int mCoin;
public:
	Enemy(const string& name);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

};

