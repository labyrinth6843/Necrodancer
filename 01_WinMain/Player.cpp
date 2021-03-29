#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ground.h"
#include "Item.h"

Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	//이미지 로드
	mHeadImage = ImageManager::GetInstance()->FindImage(L"Head");
	mBodyImage = ImageManager::GetInstance()->FindImage(L"Body");
	mShovelImage = ImageManager::GetInstance()->FindImage(L"Shovel");

	//방향에 따른 머리, 몸통 애니메이션
	mHeadLeftAnimation = new Animation();
	mHeadLeftAnimation->InitFrameByStartEnd(4, mIsArmor, 7, mIsArmor, false);
	mHeadLeftAnimation->SetIsLoop(true);
	mHeadLeftAnimation->SetFrameUpdateTime(0.1f);
	mHeadLeftAnimation->Play();

	mHeadRightAnimation = new Animation();
	mHeadRightAnimation->InitFrameByStartEnd(0, mIsArmor, 3, mIsArmor, false);
	mHeadRightAnimation->SetIsLoop(true);
	mHeadRightAnimation->SetFrameUpdateTime(0.1f);
	mHeadRightAnimation->Play();

	mBodyLeftAnimation = new Animation();
	mBodyLeftAnimation->InitFrameByStartEnd(4, (int)mArmorType, 7, (int)mArmorType, false);
	mBodyLeftAnimation->SetIsLoop(true);
	mBodyLeftAnimation->SetFrameUpdateTime(0.1f);
	mBodyLeftAnimation->Play();

	mBodyRightAnimation = new Animation();
	mBodyRightAnimation->InitFrameByStartEnd(0, (int)mArmorType, 3, (int)mArmorType, false);
	mBodyRightAnimation->SetIsLoop(true);
	mBodyRightAnimation->SetFrameUpdateTime(0.1f);
	mBodyRightAnimation->Play();

	//초기 설정이 필요한 값 입력
	mHp = 6;
	mX = TileSize * 8;
	mY = TileSize * 4;
	mCorrectionY = 0.f;
	mStartIndexX = mX / TileSize;
	mStartIndexY = mY / TileSize;
	mCurrentHeadAnimation = mHeadRightAnimation;
	mCurrentBodyAnimation = mBodyRightAnimation;

	//초반 장착 아이템
	mWeapon = new Weapon(-10.f, -10.f, WeaponType::Rapier, WeaponMaterial::Glass, ItemState::Owned);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, (GameObject*)mWeapon);
	//
}

void Player::Release() {
	SafeDelete(mHeadLeftAnimation)
		SafeDelete(mHeadRightAnimation)
		SafeDelete(mBodyLeftAnimation)
		SafeDelete(mBodyRightAnimation)
}

void Player::Update() {
	//현재 인덱스값 계산
	mStartIndexX = mX / TileSize;
	mStartIndexY = mY / TileSize;

	//이동 중이지 않을 때 각 입력에 대한 처리
	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				//목적지 타일의 벽 유무 검사
				if (WallCheck(0, -1) == true)
					Dig(0, -1);//있으면 채광
				else
					Interaction(0, -1, VK_UP);//없으면 다른 상호작용
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (mIsLeft == false) {
					mIsLeft = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				if (WallCheck(1, 0) == true)
					Dig(1, 0);
				else
					Interaction(1, 0, VK_RIGHT);
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (mIsLeft == true) {
					mIsLeft = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				if (WallCheck(-1, 0) == true)
					Dig(-1, 0);
				else
					Interaction(-1, 0, VK_LEFT);
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (WallCheck(0, 1) == true)
					Dig(0, 1);
				else
					Interaction(0, 1, VK_DOWN);
			}
		}
	}
	else {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;
		mX = Math::Lerp(mStartX, mEndX, ratio);
		mY = Math::Lerp(mStartY, mEndY, ratio);

		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mX = mEndX;
			mY = mEndY;
			mCorrectionY = 0.f;
			mIsMove = false;
		}
	}

	if (mShowShovel == true) {
		mShowShovelFrame -= 0.1f;
		if (mShowShovelFrame <= 0.f)
			mShowShovel = false;
	}

	Ground* tempGround = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	tempGround->GetSight(mX / TileSize, mY / TileSize, (int)10);

	mCurrentHeadAnimation->Update();
	mCurrentBodyAnimation->Update();
}

void Player::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mBodyImage, mX + 5, mY + mCorrectionY + 6, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY(), 34, 30);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mHeadImage, mX + 5 + 2, mY + mCorrectionY + 6 - 14, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY(), 28, 22);
	if (mShowShovel == true)
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mShovelImage, mEndX, mEndY, (int)mShovelType - 1, 0, TileSize, TileSize);
}

float Player::DistanceShopkeeper() {
	GameObject* temp = ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, "ShopKeeper");

	if (temp == nullptr)
		return 0.f;

	//직선거리로 10칸을 넘어가는지 확인, 넘어갔다면 소리가 아예 들리지 않는다
	if (Math::GetDistance(mStartIndexX, mStartIndexY, temp->GetX() / TileSize, temp->GetY() / TileSize) < 10)
		return 0.f;
	//나온 직선거리를 역수를 취해 볼륨값으로 반환
	else
		return 1 / Math::GetDistance(mStartIndexX, mStartIndexY, temp->GetX() / TileSize, temp->GetY() / TileSize);
}

void Player::Move(int x, int y) {
	//이동용 Ground
	Ground* ground;
	if (ObjectManager::GetInstance()->FindObject("Ground"))
		ground = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	else
		return;

	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	mStartX = mX;
	mStartY = mY;
	mMoveTime = 0.f;
	mJumpPower = 150.f;
	mCorrectionY = 0.f;

	if (ground->IsMove(mEndIndexX, mEndIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

bool Player::WallCheck(int x, int y)
{
	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall") != nullptr) {
		Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

		POINT mapsize = temp->GetMapSize();
		if (mEndIndexX < 0 || mEndIndexX >= mapsize.x || mEndIndexY < 0 || mEndIndexY >= mapsize.y)
			return false;

		if (temp->GetFrameIndexX(mEndIndexX, mEndIndexY) == 0 && temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 0)
			return false;
		else
			return true;
	}
}

void Player::Dig(int x, int y) {
	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

	if (temp->GetFrameIndexX(mEndIndexX, mEndIndexY) == 0 && temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 0)
		return;

	mShowShovel = true;
	mShowShovelFrame = 01.0f;

	if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 6) {
		SoundPlayer::GetInstance()->Play(L"move_fail", 1.f);
		Combo::GetInstance()->ComboReset();
		return;
	}

	if (mShovelPower >= temp->GetDigLevel()) {
		if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 4)
			SoundPlayer::GetInstance()->Play(L"move_dirt", 1.f);
		else if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 5)
			SoundPlayer::GetInstance()->Play(L"move_stone", 1.f);
		else if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 6)
			SoundPlayer::GetInstance()->Play(L"move_brick", 1.f);

		temp->SetFrameIndexX(mEndIndexX, mEndIndexY, 0);
		temp->SetFrameIndexY(mEndIndexX, mEndIndexY, 0);
	}
}

void Player::Attack(GameObject* object) {
	if (object == nullptr || object->GetName() == "ShopKeeper")
		return;
	Enemy* temp = (Enemy*)object;

	temp->IsAttacked(mAtk);
	Combo::GetInstance()->ComboUp();
}

void Player::Equip(POINT index) {

	Item* newWeapon = (Item*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Item, index);

	if (newWeapon == nullptr)
		return;

	switch (newWeapon->GetType())
	{
	case ItemType::Weapon:
		mWeapon->SetState(ItemState::NotOwned);
		mWeapon->SetPosition(index.x * TileSize, index.y * TileSize);

		mWeapon = (Weapon*)newWeapon;
		mWeapon->SetState(ItemState::Owned);
		mWeapon->SetPosition(-10.f, -10.f);
		mAtk = mWeapon->GetAtk();
		break;

		//이후에 아이템 등급을 비교해서 교체하도록 기능 추가
	default:
		return;
		break;
	}

}

bool Player::AttackRangeCheck(const int& key)
{
	vector<POINT> range;
	mWeapon->GetRange(key, range);
	bool attackCheck = false;	//공격을 한번이라도 했는지

	Wall* tempWall = (Wall*)ObjectManager::GetInstance()->FindObject("Wall");

	for (int i = 0; i < range.size(); ++i)
	{
		//벽이 있는지 유무 체크
		if (tempWall->IsWall(range[i].x, range[i].y))
		{
			//벽이 있다면 공격 중단
			break;
		}

		//적이 공격범위에 있다면
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, range[i]) != nullptr)
		{
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, range[i]));
			attackCheck = true;
			if (mWeapon->GetWeaponType() == WeaponType::Rapier)
			{
				//한칸 공백 너머에 적이 있다면
				if (i > 0)
				{
					//한칸 움직인다
					Move(range[i - 1].x - mX / TileSize, range[i - 1].y - mY / TileSize);
				}
			}
			if (mWeapon->GetWeaponType() == WeaponType::Rapier || mWeapon->GetWeaponType() == WeaponType::Spear || mWeapon->GetWeaponType() == WeaponType::Bow)
			{
				//한칸을 공격하면 그 너머는 공격하지 않는다
				break;
			}
		}
	}
	if (attackCheck)
		CameraManager::GetInstance()->GetMainCamera()->CameraShake();
	return attackCheck;
}

void Player::Interaction(int x, int y, const int& key)
{
	if (AttackRangeCheck(key) == false)
	{
		mEndX = mX + TileSize * x;
		mEndY = mY + TileSize * y;

		mEndIndexX = mEndX / TileSize;
		mEndIndexY = mEndY / TileSize;

		Equip(POINT{ mEndIndexX, mEndIndexY });
		Move(x, y);
	}
}