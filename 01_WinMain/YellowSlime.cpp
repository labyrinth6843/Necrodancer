#include "pch.h"
#include "YellowSlime.h"

YellowSlime::YellowSlime(const string& name, int x, int y) :Enemy(name) {
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 1;
	mCoin = 2;
	mAtk = 0.5f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime3");

	mDirection = Random::GetInstance()->RandomInt(100) % 2;

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

	if (mDirection == 0) {
		mCurrentAnimation = mLeftAnimation;
		mClockWise = true;
	}
	else {
		mCurrentAnimation = mRightAnimation;
		mClockWise = false;
	}
	mMoveState = 0;
}

void YellowSlime::Init()
{

}

void YellowSlime::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			if (mIsLeft == true)
				mCurrentAnimation = mLeftAnimation;
			else
				mCurrentAnimation = mRightAnimation;
			POINT temp = DestinationValidationCheck(mMoveState);
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

	Ground* ground = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground");
	ground->GetAlpha(mX / TileSize, mY / TileSize, mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void YellowSlime::Release()
{
	SafeDelete(mLeftAnimation)
	SafeDelete(mRightAnimation)
}

void YellowSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void YellowSlime::Attack() {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"slime_attack", 1.f);
}

void YellowSlime::IsAttacked(int dmg)
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
}

POINT YellowSlime::DestinationValidationCheck(int moveState) {
	mDestX = mX;
	mDestIndexX = mDestX / TileSize;
	mDestY = mY;
	mDestIndexY = mDestY / TileSize;
	if (mClockWise == true) {
		switch (moveState) {
		case 0:
			mIsLeft = false;
			mDestX += TileSize;
			mDestIndexX++;
			return { 1,0 };
		case 1:
			mDestY += TileSize;
			mDestIndexY++;
			return { 0,1 };
		case 2:
			mIsLeft = true;
			mDestX-= TileSize;
			mDestIndexX--;
			return { -1,0 };
		case 3:
			mDestY -= TileSize;
			mDestIndexY--;
			return { 0,-1 };
		}
	}
	else {
		switch (moveState) {
		case 0:
			mIsLeft = true;
			mDestX -= TileSize;
			mDestIndexX--;
			return { -1,0 };
		case 1:
			mDestY += TileSize;
			mDestIndexY++;
			return { 0,1 };
		case 2:
			mIsLeft = false;
			mDestX += TileSize;
			mDestIndexX++;
			return { 1,0 };
		case 3:
			mDestY -= TileSize;
			mDestIndexY--;
			return { 0,-1 };
		}
	}
}

void YellowSlime::Move(int dirX, int dirY) {
	mMoveTime = 0.f;
	mIsMove = true;
	mMoveState++;
	if (mMoveState > 3)
		mMoveState = 0;
	Ground* ground;
	if (ObjectManager::GetInstance()->FindObject("Ground"))
		ground = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	else
		return;

	mInitX = mX;
	mInitY = mY;
	mCorrectionY = 0.f;
	mJumpPower = 150.f;

	if (mIsLeft == true)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;

	if (dirX > 0)
		mCurrentAnimation = mRightAnimation;
	else if (dirX < 0)
		mCurrentAnimation = mLeftAnimation;

	if (ground->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}