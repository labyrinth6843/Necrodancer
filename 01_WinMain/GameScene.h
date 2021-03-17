#pragma once
#include "Scene.h"
class Tile;
class Button;

class GameScene : public Scene
{
	vector<wstring>mPallete;

	Button* mToolButton;

	bool mIsEnd;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Tool();
};

