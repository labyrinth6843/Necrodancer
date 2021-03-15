#include "pch.h"
#include "Player.h"
Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	mHeadImage = ImageManager::GetInstance()->FindImage(L"Head");
	mBodyImage = ImageManager::GetInstance()->FindImage(L"Body");

	mHeadLeftAnimation = new Animation();
	mHeadLeftAnimation->InitFrameByStartEnd(4, mArmor,7, mArmor,false);
	mHeadLeftAnimation->SetIsLoop(true);
	mHeadLeftAnimation->Play();

	mHeadRightAnimation = new Animation();
	mHeadRightAnimation->InitFrameByStartEnd(0, mArmor,3, mArmor,false);
	mHeadRightAnimation->SetIsLoop(true);
	mHeadRightAnimation->Play();

	mBodyLeftAnimation = new Animation();
	mBodyLeftAnimation->InitFrameByStartEnd(4, mArmorType, 7, mArmorType, false);
	mBodyLeftAnimation->SetIsLoop(true);
	mBodyLeftAnimation->Play();

	mBodyRightAnimation = new Animation();
	mBodyRightAnimation->InitFrameByStartEnd(0, mArmorType,3, mArmorType,false);
	mBodyRightAnimation->SetIsLoop(true);
	mBodyRightAnimation->Play();

	mHp = 6;
	mX = 100 + TileSize * 5;
	mY = 200 + TileSize * 4;
	initindexX = mX / TileSize;
	initindexY = mY / TileSize;

	mCurrentHeadAnimation = mHeadRightAnimation;
	mCurrentBodyAnimation = mBodyRightAnimation;
}

void Player::Release() { 
	SafeDelete(mHeadLeftAnimation)
	SafeDelete(mHeadRightAnimation)
	SafeDelete(mBodyLeftAnimation)
	SafeDelete(mBodyRightAnimation)
}

void Player::Update() {
	initindexX = (mX - 100) / TileSize;
	initindexY = (mY - 200) / TileSize;

	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
			if (initindexY > 0)
				Move(0, -1);

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if (initindexX < 9) {
				if (direction == false) {
					direction = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				Move(1, 0);
			}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (initindexX > 0) {
				if (direction == true) {
					direction = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				Move(-1, 0);
			}
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if (initindexY < 9)
				Move(0, 1);
	}
	else {
		mX += TileSize*2 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(mX, mY, destindexX, destindexY));
		mY += TileSize*2 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(mX, mY, destindexX, destindexY));

		if (fabs(destindexX - mX) <= 0.5 && fabs(destindexY - mY) <= 0.5) {
			mX = destindexX;
			mY = destindexY;
			mIsMove = false;
		}
	}
}

void Player::Render(HDC hdc) {
	mBodyImage->TileFrameRender(hdc, initindexX, initindexY, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY());
	mHeadImage->TileFrameRender(hdc, initindexX, initindexY, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY());
}

void Player::Move(int x, int y) {
	destindexX = mX + TileSize * x;
	destindexY = mY + TileSize * y;
	mIsMove = true;
}