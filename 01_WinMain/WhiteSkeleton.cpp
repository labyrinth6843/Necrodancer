#include "pch.h"
#include "WhiteSkeleton.h"

WhiteSkeleton::WhiteSkeleton(const string& name, int x, int y):Enemy(name)
{
	mX = x;
	mY = y;

	mHp = 1;
	mCoin = 2;
	mAtk = 0.5f;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton1");

	mUpLeftAnimation = new Animation();
	mUpLeftAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mUpLeftAnimation->SetFrameUpdateTime(0.1f);
	mUpLeftAnimation->SetIsLoop(true);
	mUpLeftAnimation->Play();

	mUpRightAnimation = new Animation();
	mUpRightAnimation->InitFrameByStartEnd(0, 2, 7, 2, false);
	mUpRightAnimation->SetFrameUpdateTime(0.1f);
	mUpRightAnimation->SetIsLoop(true);
	mUpRightAnimation->Play();

	mDownLeftAnimation = new Animation();
	mDownLeftAnimation->InitFrameByStartEnd(0, 4, 7, 4, false);
	mDownLeftAnimation->SetFrameUpdateTime(0.1f);
	mDownLeftAnimation->SetIsLoop(true);
	mDownLeftAnimation->Play();

	mDownRightAnimation = new Animation();
	mDownRightAnimation->InitFrameByStartEnd(0, 6, 7, 6, false);
	mDownRightAnimation->SetFrameUpdateTime(0.1f);
	mDownRightAnimation->SetIsLoop(true);
	mDownRightAnimation->Play();
}

void WhiteSkeleton::Init()
{
}

void WhiteSkeleton::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			if (mIsLeft == true)
				mCurrentAnimation = mLeftAnimation;
			else
				mCurrentAnimation = mRightAnimation;
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
	mCurrentAnimation->Update();
}

void WhiteSkeleton::Release()
{
	SafeDelete(mUpLeftAnimation);
	SafeDelete(mUpRightAnimation);
	SafeDelete(mDownLeftAnimation);
	SafeDelete(mDownRightAnimation);
}

void WhiteSkeleton::Render(HDC hdc)
{

}

void WhiteSkeleton::Attack() {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"skeleton_attack", 1.f);
}

void WhiteSkeleton::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"skeleton_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}

void WhiteSkeleton::Move(int dirX, int dirY)
{

}

POINT WhiteSkeleton::DestinationValidationCheck()
{

}