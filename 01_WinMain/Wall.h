#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Animation.h"

enum class WallType {
	Dirt,
	Stone,
	Brick,
	Fail,
	End
};

class Wall:public GameObject
{
	vector<vector<Tile*>> mWallList;
	vector<vector<Tile*>> mDecoList;

	int mMapSizeX;
	int mMapSizeY;

	int mDigLevel;
public:
	Wall(const string& name);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	int GetDigLevel() { return mDigLevel; }

	int GetFrameIndexX(int indexX, int indexY) { return mWallList[indexY][indexX]->GetFrameIndexX(); }
	int GetFrameIndexY(int indexX, int indexY) { return mWallList[indexY][indexX]->GetFrameIndexY(); }

	void SetFrameIndexX(int indexX, int indexY, int input) { mWallList[indexY][indexX]->SetFrameIndexX(input); }
	void SetFrameIndexY(int indexX, int indexY, int input) { mWallList[indexY][indexX]->SetFrameIndexY(input); }
};

