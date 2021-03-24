#pragma once
#include "Image.h"
#include "GameObject.h"
#include "Animation.h"

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
	None = 0,
	Basic = 1,
	Blood = 2,
	Titanium = 3,
	Glass = 4,
	Crystal = 5,
	Obsidian = 6,
	End
};

class Player:public GameObject{
	Image* mHeadImage;
	Image* mBodyImage;

	Image* mShovelImage;

	bool mIsLeft = true;

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
	
	ShovelType mShovelType = ShovelType::Basic;
	bool mShowShovel = false;
	float mShowShovelFrame;

	ArmorType mArmorType = ArmorType::None;
	WeaponType mWeaponType = WeaponType::Longsword;
	WeaponMaterial mWeaponMaterial = WeaponMaterial::Basic;

	int mCoin = 0;
	float mStartX;
	float mStartY;
	int mStartIndexX;
	int mStartIndexY;
	float mEndX;
	float mEndY;
	int mEndIndexX;
	int mEndIndexY;
	bool mIsMove;

	float mImageY;
	float mMoveTime;
	float mJumpPower;

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

	//목적지 타일의 벽 유무 검사
	bool WallCheck(int x, int y);
	void Dig(int x, int y);
	//있으면 채광
	//dig();
	//없으면 다른 상호작용
	//본인 상태에 따라 다른 무기 상호작용 -> 목적지 타일 외 다른 타일 확인 필요
	
	void Attack(GameObject* object);
	

	//아이템 습득 -> 목적지 타일만 확인
	void Equip(GameObject* object);
	//몬스터 오브젝트가 없다면 이동


	//이동하려는 타일에 오브젝트 유무 확인
	bool TileCheck(int x, int y);
	//Tilecheck가 false면 실행
	void Move(int x, int y);
	//아래 세 함수를 하나로 묶기 위함
	void Interaction(int x, int y);

	bool AttackRangeCheck(WeaponType weapontype, int destX, int destY, int dirX, int dirY);


	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	float GetDmg() { return mWeaponPower; }
	float GetDef() { return mDef; }

	POINT GetIndex() { return { mStartIndexX, mStartIndexY }; }
	float GetndexX() { return mStartIndexX; }
	float GetndexY() { return mStartIndexY; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};