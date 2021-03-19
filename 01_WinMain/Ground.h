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

	POINT mOddFrame; //È¦¼ö ÇÁ·¹ÀÓ
	POINT mEvenFrame;//Â¦¼ö ÇÁ·¹ÀÓ
public:
	Ground(const string &name, int startx = 0, int starty = 0);
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetMinMax();
	bool GetSight();
};

