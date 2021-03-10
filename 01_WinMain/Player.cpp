#include "pch.h"
#include "Player.h"
Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	ImageManager::GetInstance()->LoadFromFile(L"Rouge", Resources(L"Rogue.bmp"), 96, 112, 6, 7, true);

	mImage = ImageManager::GetInstance()->FindImage(L"Rouge");

	mIdleAnimation = new Animation;
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(1.f);
	mIdleAnimation->Play();

	mWalkAnimation = new Animation;
	mWalkAnimation->InitFrameByStartEnd(0, 1, 5, 1, false);
	mWalkAnimation->SetIsLoop(true);
	mWalkAnimation->SetFrameUpdateTime(0.1f);
	mWalkAnimation->Play();

	mDeathAnimation = new Animation;
	mDeathAnimation->InitFrameByStartEnd(0, 2, 4, 2, false);
	mDeathAnimation->SetIsLoop(false);
	mDeathAnimation->SetFrameUpdateTime(0.1f);
	mDeathAnimation->Play();

	mAttackAnimation = new Animation;
	mAttackAnimation->InitFrameByStartEnd(0, 3, 2, 3, false);
	mAttackAnimation->SetIsLoop(false);
	mAttackAnimation->SetFrameUpdateTime(0.1f);
	mAttackAnimation->Play();

	mUseAnimation = new Animation;
	mUseAnimation->InitFrameByStartEnd(0, 4, 1, 4, false);
	mUseAnimation->SetIsLoop(false);
	mUseAnimation->SetFrameUpdateTime(0.1f);
	mUseAnimation->Play();

	mScrollAnimation = new Animation;
	mScrollAnimation->InitFrameByStartEnd(0, 6, 0, 6, false);
	mScrollAnimation->SetIsLoop(false);
	mScrollAnimation->SetFrameUpdateTime(0.1f);
	mScrollAnimation->Play();

	mFlyAnimation = new Animation;
	mFlyAnimation->InitFrameByStartEnd(0, 5, 1, 5, false);
	mFlyAnimation->SetIsLoop(false);
	mFlyAnimation->SetFrameUpdateTime(0.1f);
	mFlyAnimation->Play();

	mPlayerState = PlayerState::Idle;
	mCurrentAnimation = mIdleAnimation;
	mCurrentAnimation->Play();
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mX = 100 + TileSize * 5;
	mY = 200 + TileSize * 4;
	indexX = mX / TileSize;
	indexY = mY / TileSize;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
}

void Player::Release() { 
	SafeDelete(mIdleAnimation);
	SafeDelete(mWalkAnimation);
	SafeDelete(mDeathAnimation);
	SafeDelete(mAttackAnimation);
	SafeDelete(mUseAnimation);
	SafeDelete(mFlyAnimation);
	SafeDelete(mScrollAnimation);
}

void Player::Update() {
	indexX = (mX - 100) / TileSize;
	indexY = (mY - 200) / TileSize;

	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W')) {
			if (indexY > 0)
				Move(0, -1);
		}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if(indexX > 0)
				Move(-1, 0);
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if(indexY < 9)
				Move(0, 1);
	
		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if(indexX < 9)
				Move(1, 0);
	}
	else {
		mX += TileSize*2 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(mX, mY, destX, destY));
		mY += TileSize*2 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(mX, mY, destX, destY));

		if (fabs(destX - mX) <= 0.5 && fabs(destY - mY) <= 0.5) {
			mX = destX;
			mY = destY;
			mCurrentAnimation = mIdleAnimation;
			mIsMove = false;
		}
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}
	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc) {
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 32, 32);
}

void Player::Move(int x, int y) {
	destX = mX + TileSize * x;
	destY = mY + TileSize * y;

	mCurrentAnimation = mWalkAnimation;
	mIsMove = true;
}