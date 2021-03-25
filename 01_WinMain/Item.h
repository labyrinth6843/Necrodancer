#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Image.h"

//아이템 재료
enum class ItemMaterial {
	Basic,
	Blood,
	Glass,
	Gold,
	Obsidian,
	Titanium,
	End
};

//착용상태
enum class ItemState {
	NotOwned,
	Owned,
	End
};

class Item:public GameObject
{
protected:
	FrameImage mImage;
	float mX;
	float mY;

	ItemMaterial mMaterial;
	ItemState mState;

public:
	Item();

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	FrameImage GetFrameImage() { return mImage; }
	POINT GetPosition() { return POINT{ (long)mX,(long)mY }; }
	float GetPositionX() { return mX; }
	float GetPositionY() { return mY; }
	ItemMaterial GetMaterial() { return mMaterial; }
	ItemState GetState() { return mState; }

	void SetFrameImage(FrameImage fimage) { mImage = fimage; }
	void SetPosition(float x, float y) { mX = x; mY = y; }
	void SetPositionX(float x) { mX = x; }
	void SetPositionY(float y) { mY = y; }
	void SetMaterial(ItemMaterial mt) { mMaterial = mt; }
	void SetState(ItemState st) { mState = st; }
};

