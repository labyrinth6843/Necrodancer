#pragma once
#include "Item.h"

class Player;
//무기 종류
enum class WeaponType {
	None,
	Dagger,		//공격 방향으로 1x1칸 공격, 투척
	Broadsword,	//공격 방향으로 3x1칸 공격, 관통
	Longsword,	//공격 방향으로 1x2칸 공격, 관통
	Spear,		//공격 방향으로 1x2칸 중 하나만 공격, 투척
	Rapier,		//공격 방향으로 1x2칸 중 하나만 공격, 최대 사거리에서 공격력 2배
	Bow,		//공격 방향으로 1x3칸 중 하나만 공격, 일반
	End
};

//무기 재료
enum class WeaponMaterial {
	Basic,	//공격력1
	Blood,	//공격력1, 체력이 반칸 이하일 경우 공격력 999
	Glass,	//공격력4, 피격시 무기 파괴, 파괴된 자리에 유리조각이 남는다
	Gold,	//공격력1, 금화를 주우면 직후 턴 공격력 999
	Obsidian,//콤보에 따라 공격력 1~3
	Titanium,//공격력2
	End
};
//무기 특성
enum class WeaponAttribute {
	Normal,	//일반 : 범위중 하나의 대상만 공격
	Splash,	//범위 : 범위 전체 공격
	Throw,	//투척 : 일반 + 특수조작으로 투척 가능
	End
};

//착용상태
enum class WeaponState {
	NotOwned,
	Owned,
	End
};

class Weapon final : public Item
{
	Player* mPlayer;
	int mAtk;

	//출력용
	FrameImage mImage;
	float mX;
	float mY;

	WeaponType mType;
	WeaponMaterial mMaterial;
	WeaponAttribute mAttribute;

	WeaponState mState;	//Render와 Update?에서 사용

public:
	void Init(float posx, float posy, WeaponType type, WeaponMaterial material, WeaponState state = WeaponState::NotOwned);
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	void SetAtk(int atk) { mAtk = atk; }
	void SetWeaponType(WeaponType type) { mType = type; }
	void SetWeaponMaterial(WeaponMaterial mat) { mMaterial = mat; }
	void SetWeaponState(WeaponState state) { mState = state; }
	void SetWeaponAttribute(WeaponAttribute att) { mAttribute = att; }

	int GetAtk() { return mAtk; }
	WeaponType GetWeaponType() { return mType; }
	WeaponMaterial GetWeaponMaterial() { return mMaterial; }
	WeaponState GetWeaponState() { return mState; }
	WeaponAttribute GetAttribute() { return mAttribute; }

	bool GetRange(const int key, vector<POINT> &range);	//Player에서 호출할 함수

private:
	bool SetRange(const int &key, vector<POINT> &range);	//GetRange에서 반환할 Range를 Player에 보내기 전에 세팅하는 함수

};

