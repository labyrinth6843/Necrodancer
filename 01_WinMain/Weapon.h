#pragma once

//���� ����
enum class WeaponType {
	None,
	Dagger,
	Broadsword,
	Spear,
	Rapier,
	Bow,
	End
};

//���� ���
enum class WeaponMaterial {
	Basic,
	Blood,
	Glass,
	Gold,
	Obsidian,
	Titanium,
	End
};

//�������
enum class WeaponState {
	NotOwned,
	Owned
};

class Weapon
{
	vector<POINT> mRange;
	int mAtk;

	WeaponType mType;
	WeaponMaterial mMaterial;
	WeaponState mState;
public:
	void Init(WeaponType type, WeaponMaterial material, WeaponState state = WeaponState::NotOwned);
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void SetAtk(int atk) { mAtk = atk; }
	void SetWeaponType(WeaponType type) { mType = type; }
	void SetWeaponMaterial(WeaponMaterial mat) { mMaterial = mat; }
	void SetWeaponState(WeaponState state) { mState = state; }

	int GetAtk() { return mAtk; }
	WeaponType GetWeaponType() { return mType; }
	WeaponMaterial GetWeaponMaterial() { return mMaterial; }
	WeaponState GetWeaponState() { return mState; }
};

