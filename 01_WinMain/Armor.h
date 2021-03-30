#pragma once
#include "Item.h"

class Player;

enum class ArmorMaterial {
	None,
	Leather,//가죽 : 방어력 0.5
	Chain,	//사슬 : 방어력 1.0
	Plate,	//판금 : 방어력 1.5
	HeavyPlate,	//판금 중갑 : 방어력 2.0, 화살표 함정 면역
	Karate,	//가라데 : 무기 공격력2배, 피격데미지 2배
	Obsidian,//흑요석 : 콤보에 따라 방어력 0.5~1.5
	Glass,	//유리 : 1회 피해 무효화
	End
};

class Armor final : public Item
{
	Player* mPlayer;
	float mDef;

	ArmorMaterial mArmorMaterial;
public:
	Armor(float posx, float posy, ArmorMaterial material, ItemState state = ItemState::NotOwned);

	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

public:
	void SetDef(int def) { mDef = def; }
	void SetArmorMaterial(ArmorMaterial mt) { mArmorMaterial = mt; }

	int GetDef() { return mDef; }
	ArmorMaterial GetArmorMaterial() { return mArmorMaterial; }
};

