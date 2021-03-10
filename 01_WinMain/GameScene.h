#pragma once
#include "Scene.h"
class Player;
class Tile;
class Button;

class GameScene : public Scene
{
	Player* mPlayer;
	vector<wstring>mPallete;

	Tile* mGroundList[TileCountY][TileCountX];
	Tile* mDecoList[TileCountY][TileCountX];
	Tile* mItemList[TileCountY][TileCountX];
	Tile* mObjectList[TileCountY][TileCountX];

	Button* mToolButton;

	bool mIsEnd;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Tool();
};

