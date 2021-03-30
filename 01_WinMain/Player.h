#pragma once
#include "Image.h"
#include "GameObject.h"
#include "Animation.h"

class Weapon;
class Armor;

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
	float mDef = 0.f;
	float mAtk = 1.f;
	int mShovelPower = 3;
	bool mIsArmor = false;
	
	ShovelType mShovelType = ShovelType::Basic;
	bool mShowShovel = false;
	float mShowShovelFrame;

	//장착중인 아이템
	Weapon* mWeapon;
	Armor* mArmor;

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

	float mCorrectionY;
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
	float DistanceShopkeeper();

	//목적지 타일의 벽 유무 검사
	bool WallCheck(int x, int y);
	void Dig(int x, int y);
	void Attack(GameObject* object);
	//아이템 습득 -> 목적지 타일만 확인
	void Equip(POINT index);
	//몬스터 오브젝트가 없다면 이동
	void Move(int x, int y);
	
	//상호작용 함수를 하나로 묶기 위함
	void Interaction(int x, int y, const int &key = NULL);

	bool AttackRangeCheck(const int& key);

	void SetHp(float hp) { mHp = hp; }
	float GetHp() { return mHp; }

	void SetAtk(float atk) { mAtk = atk; }
	void SetDef(float def) { mAtk = def; }

	float GetAtk() { return mAtk; }
	float GetDef() { return mDef; }

	POINT GetIndex() { return { (long)(mX / TileSize), (long)(mY/TileSize) }; }
	float GetIndexX() { return mX / TileSize; }
	float GetIndexY() { return mY / TileSize; }

	void SetCoin(int coin) { mCoin = coin; }
	int GetCoin() { return mCoin; }
};