#include "pch.h"
#include "Minotaur.h"
//
Minotaur::Minotaur(const string & name, int x, int y):Enemy(name)
{
	FileManager::LoadMap(L"Test01", mWallList, TileSize, 72);

	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 3;
	mCoin = 10;
	mAtk = 2.f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Minotaur");

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0,0,3,0,false);
	mLeftAnimation->SetFrameUpdateTime(0.1f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0,2,3,2,false);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	mLeftWallImpactAnimation = new Animation();
	mLeftWallImpactAnimation->InitFrameByStartEnd(5, 0, 8, 0, false);
	mLeftWallImpactAnimation->SetFrameUpdateTime(0.1f);
	mLeftWallImpactAnimation->SetIsLoop(true);
	mLeftWallImpactAnimation->Play();

	mRightWallImpactAnimation = new Animation;
	mRightWallImpactAnimation->InitFrameByStartEnd(5,2,8,2,false);
	mRightWallImpactAnimation->SetFrameUpdateTime(0.1f);
	mRightWallImpactAnimation->SetIsLoop(true);
	mRightWallImpactAnimation->Play();

	mDirection = Random::GetInstance()->RandomInt(100) % 2;

	if (mDirection == 0) {
		mCurrentAnimation = mLeftAnimation;
		mIsLeft = true;
	}
	else {
		mCurrentAnimation = mRightAnimation;
		mIsLeft = false;
	}
}

void Minotaur::Move(int dirX, int dirY)
{
	mMoveTime = 0.f;
	mIsMove = true;

	mDestX = mX + TileSize * dirX;
	mDestY = mY + TileSize * dirY;

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	if (dirX > 0)
		mIsLeft = false;
	else if(dirX < 0)
		mIsLeft = true;

	mInitX = mX;
	mInitY = mY;
	mCorrectionY = 0.f;
	mJumpPower = 150.f;

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

POINT Minotaur::DestinationValidationCheck()
{
	mDestX = mPlayerPtr->GetX();
	mDestY = mPlayerPtr->GetY();
	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;
	
	int disX = abs(mX / TileSize - mPlayerPtr->GetX() / TileSize);
	int disY = abs(mY / TileSize - mPlayerPtr->GetY() / TileSize);

	if (mX / TileSize == mDestIndexX) {
		mIsAttack = true;
		SoundPlayer::GetInstance()->Play(L"minotaur_charge", 1.f);
		if (mY / TileSize > mDestIndexY) {
			mRushDirection = { 0, -1 };
			return { 0, -1 };
		}
		else
			mRushDirection = { 0, 1 };
			return { 0, 1 };
	}

	if (mY / TileSize == mDestIndexY) {
		mIsAttack = true;
		SoundPlayer::GetInstance()->Play(L"minotaur_charge", 1.f);
		if (mX / TileSize > mDestIndexX) {
			mRushDirection = { -1,0 };
			return { -1,0 };
		}
		else {
			mRushDirection = { 1,0 };
			return { 1,0 };
		}
	}

	if (disX > disY) {
		if (mX > mPlayerPtr->GetX()) {
			mDirection = 1;
			return { -1,0 };
		}
		else {
			mDirection = 2;
			return { 1, 0 };
		}
	}
	else if (disX < disY) {
		if (mY > mPlayerPtr->GetY()) {
			mDirection = 0;
			return { 0, -1 };
		}
		else {
			mDirection = 3;
			return { 0, 1 };
		}
	}
	else {
		switch (mDirection) {
		case 0:
			return { 0, -1 };
		case 1:
			return { -1,0 };
		case 2:
			return { 1, 0 };
		case 3:
			return { 0, 1 };
		}
	}
}

void Minotaur::Dig(int indexX, int indexY)
{
	
}

void Minotaur::Init()
{

}

void Minotaur::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			if (mIsStun == true) {
				mStunBeat++;
				if (mStunBeat > 2)
					mIsStun = false;
			}
			else {
				if (mIsLeft == true)
					mCurrentAnimation = mLeftAnimation;
				else
					mCurrentAnimation = mRightAnimation;

				if (mIsAttack == false) {
					POINT temp = DestinationValidationCheck();
					if (WallCheck(temp.x, temp.y) == false) {
						if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr)
							Move(temp.x, temp.y);
					}
				}

				else {
					if (WallCheck(mRushDirection.x, mRushDirection.y) == false) {
						if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) != nullptr)
							Stun();
						else if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY) {
							Attack();
							Stun();
						}
						else
							Move(mRushDirection.x, mRushDirection.y);
					}
					else
						Stun();
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

void Minotaur::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mLeftWallImpactAnimation);
	SafeDelete(mRightWallImpactAnimation);
}

void Minotaur::Render(HDC hdc)
{
	if(mIsAttack == false)
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
	else
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, 4, mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void Minotaur::Attack()
{
	mPlayerPtr->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"minotaur_attack", 1.f);
}

void Minotaur::Stun()
{
	SoundPlayer::GetInstance()->Play(L"minotaur_wallimpact", 1.f);
	mStunBeat = 0;

	mIsAttack = false;
	mIsStun = true;
	
	if (mIsLeft == true)
		mCurrentAnimation = mLeftWallImpactAnimation;
	else
		mCurrentAnimation = mRightWallImpactAnimation;
}

void Minotaur::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"minotaur_death",1.f);
		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_3", 1.f);
			break;
		}
	}
}