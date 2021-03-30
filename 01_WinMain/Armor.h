#pragma once
#include "Item.h"

class Player;

enum class ArmorMaterial {
	None,
	Leather,//���� : ���� 0.5
	Chain,	//�罽 : ���� 1.0
	Plate,	//�Ǳ� : ���� 1.5
	HeavyPlate,	//�Ǳ� �߰� : ���� 2.0, ȭ��ǥ ���� �鿪
	Karate,	//���� : ���� ���ݷ�2��, �ǰݵ����� 2��
	Obsidian,//��伮 : �޺��� ���� ���� 0.5~1.5
	Glass,	//���� : 1ȸ ���� ��ȿȭ
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

