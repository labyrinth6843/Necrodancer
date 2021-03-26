#pragma once
#include "Tile.h"
#include "GameObject.h"

class Ground : public GameObject
{
	Image* mBack;
	vector<vector<Tile*>> mGroundList;	//Test00.txt

	int mMapSizeX;
	int mMapSizeY;

	int mMinIndexX;
	int mMinIndexY;
	int mMaxIndexX;
	int mMaxIndexY;

	POINT mOddFrame; //홀수 프레임
	POINT mEvenFrame;//짝수 프레임
public:
	Ground(const string &name, int startx = 0, int starty = 0);
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

public:
	void SetMinMax();
	bool GetSight();
	bool IsMove(int indexX, int indexY);	//이동하고자 하는 바닥타일의 인덱스를 인자로 받는다

	POINT GetMapSize()
	{
		POINT pt = { mMapSizeX,mMapSizeY };
		return pt;
	}
};

