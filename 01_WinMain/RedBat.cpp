#include "pch.h"
#include "RedBat.h"

RedBat::RedBat(const string& name, int x, int y) :Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 1;
	mCoin = 3;
	mAtk = 1.f;

	mImage = ImageManager::GetInstance()->FindImage(L"RedBat");

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mLeftAnimation->SetFrameUpdateTime(0.1f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	if (Random::GetInstance()->RandomInt(2) == 0) {
		mIsLeft = true;
		mCurrentAnimation = mLeftAnimation;
	}

	else {
		mIsLeft = false;
		mCurrentAnimation = mRightAnimation;
	}
}

void RedBat::Init()
{

}

void RedBat::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			POINT temp = DestinationValidationCheck();

			if (WallCheck(temp.x, temp.y) == false) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
					if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetX() / TileSize == mDestIndexX &&
						ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetY() / TileSize == mDestIndexY)
						Attack();
					else
						Move(temp.x, temp.y);
				}
			}

		}
	}
	if (mIsMove == true) {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;
		mX = Math::Lerp(mInitX, mDestX, ratio);
		mY = Math::Lerp(mInitY, mDestY, ratio);

		if (ratio >= 1.f)
		{
			mX = mDestX;
			mY = mDestY;
			mIsMove = false;
			mDestX = mInitX;
			mDestY = mInitY;
			mInitX = mX;
			mInitY = mY;
		}
	}
	mCurrentAnimation->Update();
}

void RedBat::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
}

void RedBat::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void RedBat::Move(int destX, int destY)
{
	mMoveTime = 0.f;
	mIsMove = true;
	Ground* ground;
	if (ObjectManager::GetInstance()->FindObject("Ground"))
		ground = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	else
		return;

	mInitX = mX;
	mInitY = mY;

	if (mIsLeft == true)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;

	if (ground->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

POINT RedBat::DestinationValidationCheck()
{
	mDestX = mX;
	mDestY = mY;
	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	bool isBreak = false;
	int count = 0;
	POINT destinationDirection = { 0,0 };

	while (isBreak == false) {
		mDirection = Random::GetInstance()->RandomInt(100) % 4;

		switch (mDirection) {
		case 0:
			mDestY = mY - TileSize;
			count++;
			destinationDirection = { 0, -1 };
			break;
		case 1:
			mIsLeft = true;
			mDestX = mX - TileSize;
			count++;
			destinationDirection = { -1, 0 };
			break;
		case 2:
			mIsLeft = false;
			mDestX = mX + TileSize;
			count++;
			destinationDirection = { 1, 0 };
			break;
		case 3:
			mDestY = mY + TileSize;
			count++;
			destinationDirection = { 0, 1 };
			break;
		}

		if (count > 3) {
			mDestX = mX;
			mDestY = mY;
			isBreak = true;
			return { 0,0 };
		}

		mDestIndexX = mDestX / TileSize;
		mDestIndexY = mDestY / TileSize;

		if (WallCheck(destinationDirection.x, destinationDirection.y) == false && ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr)
			isBreak = true;
	}
	return destinationDirection;
}

void RedBat::Attack()
{
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"bat_attack", 1.f);
}

void RedBat::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"bat_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}