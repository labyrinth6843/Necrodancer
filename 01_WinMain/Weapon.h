#pragma once

//무기 종류
enum class WeaponType {
	None,
	Dagger,
	Broadsword,
	Longsword,
	Spear,
	Rapier,
	Bow,
	End
};

//무기 재료
enum class WeaponMaterial {
	Basic,
	Blood,
	Glass,
	Gold,
	Obsidian,
	Titanium,
	End
};
//무기 특성
enum class WeaponAttribute {
	Normal,
	Pierce,
	Throw,
	End
};

//착용상태
enum class WeaponState {
	NotOwned,
	Owned,
	End
};

class Weapon
{
	vector<POINT> mLeftRange;
	vector<POINT> mRightRange;
	vector<POINT> mTopRange;
	vector<POINT> mBottomRange;
	int mAtk;

	WeaponType mType;
	WeaponMaterial mMaterial;
	WeaponAttribute mAttribute;
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

