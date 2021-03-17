#pragma once
#include "Tile.h"
#include "GameObject.h"

class Ground : public GameObject
{
	Image* mBack;
	vector<vector<Tile*>> mGroundList;	//Test00.txt
	vector<vector<Tile*>> mWallList;	//Test01.txt
	vector<vector<Tile*>> mDecoList;	//Test02.txt

	int mMapSizeX;
	int mMapSizeY;
public:
	Ground(const string &name, int startx = 0, int starty = 0);
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool GetSight();
};

