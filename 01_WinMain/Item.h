#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Image.h"
#include "Ground.h"

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

//아이템 종류
enum class ItemType {
	Weapon,
	Armor,
	Shovel,
	Torch,
	End
};

class Item:public GameObject
{
protected:
	FrameImage mImage;

	ItemMaterial mMaterial;
	ItemState mState;
	ItemType mType;

	Ground* mGroundPtr;

	int mMinIndexX;
	int mMinIndexY;
	int mMaxIndexX;
	int mMaxIndexY;

	bool mIsShadow = false;
public:
	Item();

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

public:
	FrameImage GetFrameImage() { return mImage; }
	POINT GetPosition() { return POINT{ (long)mX,(long)mY }; }
	float GetPositionX() { return mX; }
	float GetPositionY() { return mY; }
	ItemMaterial GetMaterial() { return mMaterial; }
	ItemState GetState() { return mState; }
	ItemType GetType() { return mType; }

	void SetFrameImage(FrameImage fimage) { mImage = fimage; }
	void SetPosition(float x, float y) { mX = x; mY = y; }
	void SetPositionX(float x) { mX = x; }
	void SetPositionY(float y) { mY = y; }
	void SetMaterial(ItemMaterial mt) { mMaterial = mt; }
	void SetState(ItemState st) { mState = st; }
	void SetType(ItemType t) { mType = t; }

	void SetGroundPtr(Ground* gptr) { mGroundPtr = gptr; }
	void SetGroundPtr(GameObject* gptr)
	{ 
		if(gptr)
		 mGroundPtr = (Ground*)gptr; 
	}
	Ground* GetGroundPtr() { return mGroundPtr; }
};

