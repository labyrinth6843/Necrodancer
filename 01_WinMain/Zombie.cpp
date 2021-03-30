#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(const string& name, int x, int y) :Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 1;
	mCoin = 1;
	mAtk = 2;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Zombie");

	mDirection = Random::GetInstance()->RandomInt(100) % 4;

	mUpLeftAnimation = new Animation();
	mUpLeftAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mUpLeftAnimation->SetFrameUpdateTime(0.1f);
	mUpLeftAnimation->SetIsLoop(true);
	mUpLeftAnimation->Play();

	mUpRightAnimation = new Animation();
	mUpRightAnimation->InitFrameByStartEnd(8, 0, 15, 0, false);
	mUpRightAnimation->SetFrameUpdateTime(0.1f);
	mUpRightAnimation->SetIsLoop(true);
	mUpRightAnimation->Play();

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 2, 7, 2, false);
	mLeftAnimation->SetFrameUpdateTime(0.1f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(8, 2, 15, 2, false);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	mDownLeftAnimation = new Animation();
	mDownLeftAnimation->InitFrameByStartEnd(0, 4, 7, 4, false);
	mDownLeftAnimation->SetFrameUpdateTime(0.1f);
	mDownLeftAnimation->SetIsLoop(true);
	mDownLeftAnimation->Play();

	mDownRightAnimation = new Animation();
	mDownRightAnimation->InitFrameByStartEnd(8, 4, 15, 4, false);
	mDownRightAnimation->SetFrameUpdateTime(0.1f);
	mDownRightAnimation->SetIsLoop(true);
	mDownRightAnimation->Play();

	if (Random::GetInstance()->RandomInt(2) == 0)
		mIsLeft = true;
	else
		mIsLeft = false;

	switch (mDirection) {
	case 0:
		if (mIsLeft == true)
			mCurrentAnimation = mUpLeftAnimation;
		else
			mCurrentAnimation = mUpRightAnimation;
		break;
	case 1:
		mIsLeft = true;
		mCurrentAnimation = mLeftAnimation;
		break;
	case 2:
		mIsLeft = false;
		mCurrentAnimation = mRightAnimation;
		break;
	case 3:
		if (mIsLeft == true)
			mCurrentAnimation = mDownLeftAnimation;
		else
			mCurrentAnimation = mDownRightAnimation;
		break;
	}
	mMoveBeat = false;
}

void Zombie::Init()
{

}

void Zombie::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			mMoveBeat = !mMoveBeat;
			if (mMoveBeat == true) 
			{
				POINT temp = DestinationValidationCheck(mDirection);
				if (WallCheck(temp.x, temp.y) == false && ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
					if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
						Attack();
					else
						Move(temp.x, temp.y);
				}
				else {
					switch (mDirection) {
					case 0:
						mDirection = 3;
						if (mIsLeft == true)
							mCurrentAnimation = mDownLeftAnimation;
						else
							mCurrentAnimation = mDownRightAnimation;
						break;
					case 1:
						mIsLeft = false;
						mDirection = 2;
						mCurrentAnimation = mRightAnimation;
						break;
					case 2:
						mIsLeft = true;
						mDirection = 1;
						mCurrentAnimation = mLeftAnimation;
						break;
					case 3:
						mDirection = 0;
						if (mIsLeft == true)
							mCurrentAnimation = mUpLeftAnimation;
						else
							mCurrentAnimation = mUpRightAnimation;
						break;
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

		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mX = mDestX;
			mY = mDestY;
			mIsMove = false;
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

void Zombie::Release()
{
	SafeDelete(mUpLeftAnimation);
	SafeDelete(mUpRightAnimation);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mDownLeftAnimation);
	SafeDelete(mDownRightAnimation);
}

void Zombie::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void Zombie::Attack() {
	float damage = (float)mAtk - mPlayerPtr->GetDef();
	if (damage <= 0.f)
		damage = 1.f;
	mPlayerPtr->HpDown(damage);
	SoundPlayer::GetInstance()->Play(L"zombie_attack", 1.f);
}

void Zombie::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"zombie_death", 1.f);
		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}

POINT Zombie::DestinationValidationCheck(int direction)
{
	mDestX = mX;
	mDestIndexX = mDestX / TileSize;
	mDestY = mY;
	mDestIndexY = mDestY / TileSize;
	switch (direction) {
	case 0 :
		mDestY -= TileSize;
		mDestIndexY = mDestY / TileSize;
		return { 0, -1 };
	case 1:
		mDestX -= TileSize;
		mDestIndexX = mDestX / TileSize;
		return { -1, 0 };
	case 2:
		mDestX += TileSize;
		mDestIndexX = mDestX / TileSize;
		return { 1, 0 };
	case 3: 
		mDestY -= TileSize;
		mDestIndexY = mDestY / TileSize;
		return { 0, 1 };
	}
}

void Zombie::Move(int dirX, int dirY) {
	mMoveTime = 0.f;
	mIsMove = true;

	mInitX = mX;
	mInitY = mY;
	mCorrectionY = 0.f;
	mJumpPower = 150.f;

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}