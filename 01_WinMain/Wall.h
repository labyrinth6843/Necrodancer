#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Animation.h"

class Ground;

enum class WallType {
	Dirt,
	Stone,
	Brick,
	Fail,
	End
};

class Wall:public GameObject
{
	Image* mWallShadow;
	Ground* mGroundPtr;

	vector<vector<Tile*>> mWallList;
	vector<vector<Tile*>> mDecoList;

	int mMapSizeX;
	int mMapSizeY;

	int mDigLevel;

	int mMinIndexX;
	int mMinIndexY;
	int mMaxIndexX;
	int mMaxIndexY;

public:
	Wall(const string& name);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

public:
	void SetGroundPtr(string name)
	{ 
		if(ObjectManager::GetInstance()->FindObject(name))
			mGroundPtr = (Ground*)ObjectManager::GetInstance()->FindObject(name); 
	}
	bool IsWall(int indexX, int indexY);

	int GetDigLevel() { return mDigLevel; }

	int GetFrameIndexX(int indexX, int indexY) { return mWallList[indexY][indexX]->GetFrameIndexX(); }
	int GetFrameIndexY(int indexX, int indexY) { return mWallList[indexY][indexX]->GetFrameIndexY(); }

	void SetFrameIndexX(int indexX, int indexY, int input) { mWallList[indexY][indexX]->SetFrameIndexX(input); }
	void SetFrameIndexY(int indexX, int indexY, int input) { mWallList[indexY][indexX]->SetFrameIndexY(input); }

	POINT GetMapSize() 
	{ 
		POINT pt = { mMapSizeX,mMapSizeY };
		return pt;
	}
};

