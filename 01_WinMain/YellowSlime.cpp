#include "pch.h"
#include "YellowSlime.h"

YellowSlime::YellowSlime(const string& name, int x, int y) :Enemy(name) {
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 1;
	mCoin = 2;
	mAtk = 0.5f;

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
		mDestX = mX + TileSize;
		mDestY = mY;
		mClockWise = true;
	}
	else {
		mCurrentAnimation = mRightAnimation;
		mDestX = mX - TileSize;
		mDestY = mY;
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

			if (WallCheck((mDestX - mX) / TileSize, (mDestY - mY) / TileSize) == false) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetX() / TileSize == mDestIndexX + MoveDirection(mMoveState).x &&
					ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetY() / TileSize == mDestIndexY + MoveDirection(mMoveState).y)
					Attack(MoveDirection(mMoveState).x, MoveDirection(mMoveState).y);
				else
					Move(MoveDirection(mMoveState).x, MoveDirection(mMoveState).y);
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

void YellowSlime::Release()
{
	SafeDelete(mLeftAnimation)
	SafeDelete(mRightAnimation)
}

void YellowSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void YellowSlime::Attack(int destX, int destY) {
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

POINT YellowSlime::MoveDirection(int moveState) {
	if (mClockWise == true) {
		switch (moveState) {
		case 0:
			mIsLeft = false;
			return { 1,0 };
		case 1:
			return { 0,1 };
		case 2:
			mIsLeft = true;
			return { -1,0 };
		case 3:
			return { 0,-1 };
		}
	}
	else {
		switch (moveState) {
		case 0:
			mIsLeft = true;
			return { -1,0 };
		case 1:
			return { 0,1 };
		case 2:
			mIsLeft = false;
			return { 1,0 };
		case 3:
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

	mDestX = mX + TileSize * dirX;
	mDestY = mY + TileSize * dirY;

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

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