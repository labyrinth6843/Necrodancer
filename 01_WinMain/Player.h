#pragma once
#include "Image.h"
#include "GameObject.h"
#include "Animation.h"

//무기 종류
enum class WeaponType {
	None,
	Dagger,
	Broadsword,
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

//갑옷 종류
enum class ArmorType {
	None,
	Leather,
	Chainmail,
	Plate,
	HeavyPlate,
	Obsidian,
	Glass,
	Karate,
	End
};

//삽 종류
enum class ShovelType {
	None,
	Basic,
	Blood,
	Titanium,
	Glass,
	Crystal,
	Obsidian,
	End
};

class Player:public GameObject{
	Image* mHeadImage;
	Image* mBodyImage;

	bool direction = true;

	Animation* mHeadLeftAnimation;
	Animation* mHeadRightAnimation;
	Animation* mBodyLeftAnimation;
	Animation* mBodyRightAnimation;

	Animation* mCurrentHeadAnimation;
	Animation* mCurrentBodyAnimation;
	
	float mHp = 6;
	float mDef = 0;
	int mShovelPower = 3;
	int mWeaponPower = 1;
	bool mIsArmor = false;

	ArmorType mArmorType = ArmorType::None;
	WeaponType mWeaponType = WeaponType::Dagger;
	WeaponMaterial mWeaponMaterial = WeaponMaterial::Basic;

	int mCoin = 0;
	float StartX;
	float StartY;
	int StartIndexX;
	int StartIndexY;
	float EndX;
	float EndY;
	int EndIndexX;
	int EndIndexY;
	bool mIsMove;

	int mSpeed;
public:
	Player(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	//상점 주인과 거리를 판별해 float값 반환
	//반환된 값을 바로 GameScene에서 사용하면 된다.
	float DistanceShopkeeper(GameObject* object);

	//이동하려는 타일에 오브젝트 유무 확인
	bool TileCheck(int x, int y);
	//Tilecheck가 false면 실행
	void Move(int x, int y);
	//아래 세 함수를 하나로 묶기 위함
	void Interaction(int x, int y);

	void Dig(int x, int y);
	void ShowShovel(int x, int y);
	void Attack(GameObject* object);
	void Equip(GameObject* object);

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	float GetDmg() { return mWeaponPower; }
	float GetDef() { return mDef; }

	POINT GetIndex() { return { StartIndexX, StartIndexY }; }
	float GetndexX() { return StartIndexX; }
	float GetndexY() { return StartIndexY; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};