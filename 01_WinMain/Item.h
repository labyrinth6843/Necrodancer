#pragma once
#include "GameObject.h"
#include "Image.h"
#include "Animation.h"

//�������
enum class ItemState {
	NotOwned,
	Owned,
	End
};

class Item:public GameObject
{

	vector<vector<Tile*>> mItemList;

public:
	Item(const string& name);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};

