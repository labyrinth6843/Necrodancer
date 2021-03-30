#include "pch.h"
#include "YellowSkeleton.h"

YellowSkeleton::YellowSkeleton(const string& name, int x, int y) : Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 2;
	mCoin = 3;
	mAtk = 1.5f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton2");

	mUpLeftReadyAnimation = new Animation();
	mUpLeftReadyAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mUpLeftReadyAnimation->SetFrameUpdateTime(0.1f);
	mUpLeftReadyAnimation->SetIsLoop(true);
	mUpLeftReadyAnimation->Play();

	mUpLeftMoveAnimation = new Animation();
	mUpLeftMoveAnimation->InitFrameByStartEnd(4, 0, 7, 0, false);
	mUpLeftMoveAnimation->SetFrameUpdateTime(0.1f);
	mUpLeftMoveAnimation->SetIsLoop(true);
	mUpLeftMoveAnimation->Play();

	mUpRightReadyAnimation = new Animation();
	mUpRightReadyAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mUpRightReadyAnimation->SetFrameUpdateTime(0.1f);
	mUpRightReadyAnimation->SetIsLoop(true);
	mUpRightReadyAnimation->Play();

	mUpRightMoveAnimation = new Animation();
	mUpRightMoveAnimation->InitFrameByStartEnd(4, 2, 7, 2, false);
	mUpRightMoveAnimation->SetFrameUpdateTime(0.1f);
	mUpRightMoveAnimation->SetIsLoop(true);
	mUpRightMoveAnimation->Play();

	mDownLeftReadyAnimation = new Animation();
	mDownLeftReadyAnimation->InitFrameByStartEnd(0, 4, 3, 4, false);
	mDownLeftReadyAnimation->SetFrameUpdateTime(0.1f);
	mDownLeftReadyAnimation->SetIsLoop(true);
	mDownLeftReadyAnimation->Play();

	mDownLeftMoveAnimation = new Animation();
	mDownLeftMoveAnimation->InitFrameByStartEnd(4, 4, 7, 4, false);
	mDownLeftMoveAnimation->SetFrameUpdateTime(0.1f);
	mDownLeftMoveAnimation->SetIsLoop(true);
	mDownLeftMoveAnimation->Play();

	mDownRightReadyAnimation = new Animation();
	mDownRightReadyAnimation->InitFrameByStartEnd(0, 6, 7, 6, false);
	mDownRightReadyAnimation->SetFrameUpdateTime(0.1f);
	mDownRightReadyAnimation->SetIsLoop(true);
	mDownRightReadyAnimation->Play();

	mDownRightMoveAnimation = new Animation();
	mDownRightMoveAnimation->InitFrameByStartEnd(0, 6, 7, 6, false);
	mDownRightMoveAnimation->SetFrameUpdateTime(0.1f);
	mDownRightMoveAnimation->SetIsLoop(true);
	mDownRightMoveAnimation->Play();

	if (Random::GetInstance()->RandomInt(2) == 0)
		mIsLeft = true;
	else
		mIsLeft = false;

	mMoveBeat = false;

	mDirection = Random::GetInstance()->RandomInt(100) % 4;

	switch (mDirection) {
	case 0:
		if (mIsLeft == true)
			mCurrentAnimation = mUpLeftReadyAnimation;
		else
			mCurrentAnimation = mUpRightReadyAnimation;
		break;
	case 1:
		mCurrentAnimation = mDownLeftReadyAnimation;
		break;
	case 2:
		mCurrentAnimation = mDownRightReadyAnimation;
		break;
	case 3:
		if (mIsLeft == true)
			mCurrentAnimation = mDownLeftReadyAnimation;
		else
			mCurrentAnimation = mDownRightReadyAnimation;
		break;
	}
}

void YellowSkeleton::Attack() {
	mPlayerPtr->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"skeleton_attack", 1.f);
}

void YellowSkeleton::IsAttacked(int dmg) {
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"skeleton_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_3", 1.f);
			break;
		}
	}
}

void YellowSkeleton::Init()
{

}

void YellowSkeleton::Release()
{
	SafeDelete(mUpLeftReadyAnimation);
	SafeDelete(mUpLeftMoveAnimation);
	SafeDelete(mUpRightReadyAnimation);
	SafeDelete(mUpRightMoveAnimation);
	SafeDelete(mDownLeftReadyAnimation);
	SafeDelete(mDownLeftMoveAnimation);
	SafeDelete(mDownRightReadyAnimation);
	SafeDelete(mDownRightMoveAnimation);
}

void YellowSkeleton::Update()
{
	if (mHp != 1) {
		if (Beat::GetInstance()->NextTurn() == true) {
			if (mIsMove == false) {
				mMoveBeat = !mMoveBeat;
				if (mMoveBeat == true) {
					POINT temp = DirectionDecision();
					switch (mDirection) {
					case 0:
						if (mIsLeft == true)
							mCurrentAnimation = mUpLeftMoveAnimation;
						else
							mCurrentAnimation = mUpRightMoveAnimation;
						break;
					case 1:
						mCurrentAnimation = mDownLeftMoveAnimation;
						break;
					case 2:
						mCurrentAnimation = mDownRightMoveAnimation;
						break;
					case 3:
						if (mIsLeft == true)
							mCurrentAnimation = mDownLeftMoveAnimation;
						else
							mCurrentAnimation = mDownRightMoveAnimation;
						break;
					}
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
				else {
					switch (mDirection) {
					case 0:
						if (mIsLeft == true)
							mCurrentAnimation = mUpLeftReadyAnimation;
						else
							mCurrentAnimation = mUpRightReadyAnimation;
						break;
					case 1:
						mCurrentAnimation = mDownLeftReadyAnimation;
						break;
					case 2:
						mCurrentAnimation = mDownRightReadyAnimation;
						break;
					case 3:
						if (mIsLeft == true)
							mCurrentAnimation = mDownLeftReadyAnimation;
						else
							mCurrentAnimation = mDownRightReadyAnimation;
						break;
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
	}
	else {
		if (Beat::GetInstance()->NextTurn() == true) {
			if (mIsMove == false) {

				POINT temp = { 0,0 };
				switch (mDirection) {
				case 0:
					if (mIsLeft == true)
						mCurrentAnimation = mDownLeftMoveAnimation;
					else
						mCurrentAnimation = mDownRightMoveAnimation;
					temp = { 0,1 };
					break;
				case 1:
					mCurrentAnimation = mDownRightMoveAnimation;
					temp = { 1,0 };
					break;
				case 2:
					mCurrentAnimation = mDownLeftMoveAnimation;
					temp = { -1,0 };
					break;
				case 3:
					if (mIsLeft == true)
						mCurrentAnimation = mUpLeftMoveAnimation;
					else
						mCurrentAnimation = mUpRightMoveAnimation;
					temp = { 0,-1 };
					break;
				}

				if (WallCheck(temp.x, temp.y) == false) {
					if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
						if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
						{
							Hop();
						}
						else
							Move(temp.x, temp.y);
					}
					else {
						Hop();
					}
				}
				else
					Hop();

			}
		}
		if (mIsMove == true) {
			mMoveTime += Time::GetInstance()->DeltaTime();
			float ratio = mMoveTime / 0.15f;
			if (mIsHop == true) {
				mX = Math::Lerp(mInitX, mDestX, ratio);
				mY = Math::Lerp(mInitY, mDestY, ratio);
			}

			mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
			mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

			if (ratio >= 1.f)
			{
				mX = mDestX;
				mY = mDestY;
				mIsMove = false;
				mIsHop = false;
				mCorrectionY = 0.f;
			}
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

void YellowSkeleton::Render(HDC hdc)
{
	if (mHp != 1)
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
	else
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, 8, mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void YellowSkeleton::Hop(){
	mMoveTime = 0.f;
	mIsMove = true;
	mIsHop = true;

	mCorrectionY = 0.f;
	mJumpPower = 150.f;
}

void YellowSkeleton::Move(int dirX, int dirY)
{
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

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

POINT YellowSkeleton::DirectionDecision()
{
	int disX = abs(mX / TileSize - mPlayerPtr->GetX() / TileSize);
	int disY = abs(mY / TileSize - mPlayerPtr->GetY() / TileSize);

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