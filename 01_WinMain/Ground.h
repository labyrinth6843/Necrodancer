#pragma once
#include "GameObject.h"
#include "Wall.h"

class Ground : public GameObject
{
	Image* mBack;
	vector<vector<AlphaTile>> mGroundList;	//Test00.txt

	int mMapSizeX;
	int mMapSizeY;

	int mMinIndexX;
	int mMinIndexY;
	int mMaxIndexX;
	int mMaxIndexY;

	POINT mOddFrame; //홀수 프레임
	POINT mEvenFrame;//짝수 프레임

	int mSightCall;
public:
	Ground(const string &name, int startx = 0, int starty = 0);
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

public:
	bool GetSight(int targetX, int targetY, int level);
	bool GetAlpha(int indexX, int indexY, float& alpha);	//Wall 클래스에서 호출할 함수
	bool GetAlpha(float posX, float posY, float & alpha);
	bool IsMove(int indexX, int indexY);	//이동하고자 하는 바닥타일의 인덱스를 인자로 받는다

	void GetShowArea(int &minx, int &miny, int &maxx, int &maxy);

	void SightCall();

	POINT GetMapSize()
	{
		POINT pt = { mMapSizeX, mMapSizeY };
		return pt;
	}

private:
	void SetMinMax();
};