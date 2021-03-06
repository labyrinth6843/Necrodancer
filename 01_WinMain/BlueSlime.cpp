#include "pch.h"
#include "BlueSlime.h"

BlueSlime::BlueSlime(const string& name, int x, int y) : Enemy(name) {
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 2;
	mCoin = 2;
	mAtk = 2;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime2");

	mDirection = Random::GetInstance()->RandomInt(100) % 4;

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mLeftIdleAnimation->SetFrameUpdateTime(0.1f);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->Play();

	mLeftMoveAnimation = new Animation();
	mLeftMoveAnimation->InitFrameByStartEnd(4, 0, 7, 0, false);
	mLeftMoveAnimation->SetFrameUpdateTime(0.1f);
	mLeftMoveAnimation->SetIsLoop(true);
	mLeftMoveAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightIdleAnimation->SetFrameUpdateTime(0.1f);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->Play();

	mRightMoveAnimation = new Animation();
	mRightMoveAnimation->InitFrameByStartEnd(4, 2, 7, 2, false);
	mRightMoveAnimation->SetFrameUpdateTime(0.1f);
	mRightMoveAnimation->SetIsLoop(true);
	mRightMoveAnimation->Play();

	mLeftAnimation = mLeftIdleAnimation;
	mRightAnimation = mRightIdleAnimation;

	if (Random::GetInstance()->RandomInt(2) == 0)
		mIsLeft = true;
	else
		mIsLeft = false;

	mMoveBeat = false;

	switch (mDirection) {
	case 0:
		mDestX = mX;
		mDestY = mY - TileSize;
		if (mIsLeft == true)
			mCurrentAnimation = mLeftAnimation;
		else
			mCurrentAnimation = mRightAnimation;
		break;
	case 1:
		mDestX = mX - TileSize;
		mDestY = mY;
		mCurrentAnimation = mLeftAnimation;
		break;
	case 2:
		mDestX = mX + TileSize;
		mDestY = mY;
		mCurrentAnimation = mRightAnimation;
		break;
	case 3:
		mDestX = mX;
		mDestY = mY + TileSize;
		if (mIsLeft == true)
			mCurrentAnimation = mLeftAnimation;
		else
			mCurrentAnimation = mRightAnimation;
		break;
	}
	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;
};

void BlueSlime::Init()
{

}

void BlueSlime::Update()
{
	if(mGroundPtr == nullptr)
		return;

	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			mMoveBeat = !mMoveBeat;
			if (mIsLeft == true)
				mCurrentAnimation = mLeftAnimation;
			else
				mCurrentAnimation = mRightAnimation;
			if (mMoveBeat == true) {
				if (WallCheck((mDestX - mX) / TileSize, (mDestY - mY) / TileSize) == false) {
					if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
						if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
							Attack();
						else
							Move((mDestX - mX) / TileSize, (mDestY - mY) / TileSize);
					}
					else
						Hop();
				}
				else
					Hop();
			}
			else {
				mLeftAnimation = mLeftIdleAnimation;
				mRightAnimation = mRightIdleAnimation;
			}
		}
	}
	if (mIsMove == true) {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;
		mX = Math::Lerp(mInitX, mDestX, ratio);
		mY = Math::Lerp(mInitY, mDestY, ratio);

		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mX = mDestX;
			mY = mDestY;
			mIsMove = false;
			mLeftAnimation = mLeftIdleAnimation;
			mRightAnimation = mRightIdleAnimation;
			mCorrectionY = 0.f;
			mDestX = mInitX;
			mDestY = mInitY;
			mInitX = mX;
			mInitY = mY;
		}
	}
	if (mIsHop == true) {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;

		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mIsHop = false;
			mCorrectionY = 0.f;
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

void BlueSlime::Release()
{
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mLeftMoveAnimation);
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mRightMoveAnimation);
}

void BlueSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY+mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void BlueSlime::Move(int dirX, int dirY) {
	mMoveTime = 0.f;
	mIsMove = true;

	mDestX = mX + TileSize * dirX;
	mDestY = mY + TileSize * dirY;

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	mInitX = mX;
	mInitY = mY;
	mCorrectionY = 0.f;
	mJumpPower = 150.f;
	mLeftAnimation = mLeftMoveAnimation;
	mRightAnimation = mRightMoveAnimation;

	if (mIsLeft == true)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;

	if (dirX > 0)
		mCurrentAnimation = mRightAnimation;
	else if (dirX < 0)
		mCurrentAnimation = mLeftAnimation;

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

void BlueSlime::Attack()
{
	float damage = (float)mAtk - mPlayerPtr->GetDef();
	if (damage <= 0.f)
		damage = 1.f;
	mPlayerPtr->HpDown(damage);
	SoundPlayer::GetInstance()->Play(L"slime_attack", 1.f);
}

void BlueSlime::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"slime_death_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"slime_death_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"slime_death_3", 1.f);
			break;
		}

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"slime_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"slime_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"slime_hit_3", 1.f);
			break;
		}
	}
}

void BlueSlime::Hop()
{
	mMoveTime = 0.f;
	mIsHop = true;

	mCorrectionY = 0.f;
	mJumpPower = 150.f;
}