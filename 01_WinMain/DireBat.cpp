#include "pch.h"
#include "DireBat.h"

DireBat::DireBat(const string& name, int x, int y) :Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 2;
	mCoin = 10;
	mAtk = 1.5f;

	mImage = ImageManager::GetInstance()->FindImage(L"DireBat");

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

void DireBat::Init()
{

}

void DireBat::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			mMoveBeat = !mMoveBeat;
			if (mMoveBeat == true) {
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

void DireBat::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
}

void DireBat::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void DireBat::Move(int destX, int destY)
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

POINT DireBat::DestinationValidationCheck()
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

void DireBat::Attack()
{
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"bat_attack", 1.f);
}

void DireBat::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"bat_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else
		SoundPlayer::GetInstance()->Play(L"bat_miniboss_hit", 1.f);
}