#pragma once
#include "Scene.h"
class Tile;
class Button;
class Player;

class BossScene : public Scene
{
	vector<wstring>mPallete;

	Button* mToolButton;
	Player* mPlayer;
	bool mIsEnd;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Tool();
	void NextStage();
};

