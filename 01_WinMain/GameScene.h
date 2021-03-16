#pragma once
#include "Scene.h"
class Tile;
class Button;

class GameScene : public Scene
{
	vector<wstring>mPallete;

	vector<vector<Tile*>> mGroundList;
	vector<vector<Tile*>> mDecoList;
	vector<vector<Tile*>> mItemList;
	vector<vector<Tile*>> mObjectList;

	Button* mToolButton;

	bool mIsEnd;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Tool();
};

