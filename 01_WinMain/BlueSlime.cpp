#include "pch.h"
#include "BlueSlime.h"

BlueSlime::BlueSlime(const string& name, int x, int y) : Enemy(name) {
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 2;
	mCoin = 2;
	mAtk = 1.f;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime2");

	direction = Random::GetInstance()->RandomInt(100) % 4;

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

	switch (direction) {
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
	if (Beat::GetInstance()->NextTurn() == true) {
		mMoveBeat = !mMoveBeat;
		mLeftAnimation = mLeftIdleAnimation;
		mRightAnimation = mRightIdleAnimation;
		if (mIsLeft == true)
			mCurrentAnimation = mLeftAnimation;
		else
			mCurrentAnimation = mRightAnimation;
		if (mMoveBeat == true) {
			if (WallCheck((mDestX - mX) / TileSize, (mDestY - mY) / TileSize) == false) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetX() / TileSize == mDestIndexX ||
					ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")->GetY() / TileSize == mDestIndexY)
					Attack(mDestIndexX, mDestIndexY);
				else
					Move((mDestX - mX) / TileSize, (mDestY - mY) / TileSize);
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
	mCurrentAnimation->Update();
}

void BlueSlime::Release()
{
}

void BlueSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void BlueSlime::Move(int dirX, int dirY) {
	mMoveTime = 0.f;
	mIsMove = true;

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
	mMoveTime = 0.f;
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


	if (ground->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

void BlueSlime::Attack(int destX, int destY) {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
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
