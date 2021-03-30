#pragma once
#include "GameObject.h"
class Hud
{
	Singleton(Hud);
private:
	vector<GameObject*> mItemSlot;
public:

};
#define HUD Hud::GetInstance()