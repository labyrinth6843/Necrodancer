#include "pch.h"
#include "GreyBat.h"

GreyBat::GreyBat(const string& name, int x, int y):Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 1;
	mCoin = 2;
	mAtk = 1;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"GreyBat");

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

	mMoveBeat = false;
}

void GreyBat::Init()
{

}

void GreyBat::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			mMoveBeat = !mMoveBeat;
			if (mMoveBeat == true) {
				POINT temp = DestinationValidationCheck();
				if (WallCheck(temp.x, temp.y) == false) {
					if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
						if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
							Attack();
						else
							Move(temp.x, temp.y);
					}
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

	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void GreyBat::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
}

void GreyBat::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void GreyBat::Move(int destX, int destY)
{
	mMoveTime = 0.f;
	mIsMove = true;

	mInitX = mX;
	mInitY = mY;

	if (mIsLeft == true)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

POINT GreyBat::DestinationValidationCheck()
{
	mDestX = mX;
	mDestY = mY;
	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	POINT destinationDirection = { 0,0 };

	mDirection = Random::GetInstance()->RandomInt(100) % 4;

	switch (mDirection) {
	case 0:
		mDestY = mY - TileSize;
		destinationDirection = { 0, -1 };
		break;
	case 1:
		mIsLeft = true;
		mDestX = mX - TileSize;
		destinationDirection = { -1, 0 };
		break;
	case 2:
		mIsLeft = false;
		mDestX = mX + TileSize;
		destinationDirection = { 1, 0 };
		break;
	case 3:
		mDestY = mY + TileSize;
		destinationDirection = { 0, 1 };
		break;
	}

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;
	return destinationDirection;
}

void GreyBat::Attack()
{
	float damage = (float)mAtk - mPlayerPtr->GetDef();
	if (damage <= 0.f)
		damage = 1.f;
	mPlayerPtr->HpDown(damage);
	SoundPlayer::GetInstance()->Play(L"bat_attack", 1.f);
}

void GreyBat::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"bat_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}