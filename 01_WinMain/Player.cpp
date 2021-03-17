#include "pch.h"
#include "Player.h"
#include "Camera.h"

Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	//이미지 로드
	mHeadImage = ImageManager::GetInstance()->FindImage(L"Head");
	mBodyImage = ImageManager::GetInstance()->FindImage(L"Body");

	//방향에 따른 머리, 몸통 애니메이션
	mHeadLeftAnimation = new Animation();
	mHeadLeftAnimation->InitFrameByStartEnd(4, mIsArmor,7, mIsArmor,false);
	mHeadLeftAnimation->SetIsLoop(true);
	mHeadLeftAnimation->SetFrameUpdateTime(0.1f);
	mHeadLeftAnimation->Play();

	mHeadRightAnimation = new Animation();
	mHeadRightAnimation->InitFrameByStartEnd(0, mIsArmor,3, mIsArmor,false);
	mHeadRightAnimation->SetIsLoop(true);
	mHeadRightAnimation->SetFrameUpdateTime(0.1f);
	mHeadRightAnimation->Play();

	mBodyLeftAnimation = new Animation();
	mBodyLeftAnimation->InitFrameByStartEnd(4, mArmorType, 7, mArmorType, false);
	mBodyLeftAnimation->SetIsLoop(true);
	mBodyLeftAnimation->SetFrameUpdateTime(0.1f);
	mBodyLeftAnimation->Play();

	mBodyRightAnimation = new Animation();
	mBodyRightAnimation->InitFrameByStartEnd(0, mArmorType,3, mArmorType,false);
	mBodyRightAnimation->SetIsLoop(true);
	mBodyRightAnimation->SetFrameUpdateTime(0.1f);
	mBodyRightAnimation->Play();

	//초기 설정이 필요한 값 입력
	mHp = 6;
	mX = TileSize * 5;
	mY = TileSize * 4;
	initIndexX = mX / TileSize;
	initIndexY = mY / TileSize;
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
	//현재 인덱스값 계산
	initIndexX = mX / TileSize;
	initIndexY = mY / TileSize;

	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
			if (initIndexY > 0)
				Move(0, -1);

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if (initIndexX < 9) {
				if (direction == false) {
					direction = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				Move(1, 0);
			}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (initIndexX > 0) {
				if (direction == true) {
					direction = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				Move(-1, 0);
			}
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if (initIndexY < 9)
				Move(0, 1);
	}
	else {
		mX += TileSize * 3 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(mX, mY, destIndexX, destIndexY));
		mY += TileSize * 3 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(mX, mY, destIndexX, destIndexY));

		if (Math::GetDistance(mX, mY, destIndexX, destIndexY) < TileSize / 2)
			mY += 1;
		else
			mY -= 1;

		if (fabs(destIndexX - mX) <= 0.5 && fabs(destIndexY - mY) <= 0.5) {
			mX = destIndexX;
			mY = destIndexY;
			mIsMove = false;
		}
	}
	mCurrentHeadAnimation->Update();
	mCurrentBodyAnimation->Update();
}

void Player::Render(HDC hdc) {
	//수정이 많이 필요한 부분
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mBodyImage, mX, mY, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY(), 34, 30);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mHeadImage, mX + 2, mY - 18, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY(), 28, 22);
}

void Player::Move(int x, int y) {
	//무조건 이동하는 방식이 아닌 목적지 타일의 여러 상태를 확인한 후 넘어가야 할 듯함
	destIndexX = mX + TileSize * x;
	destIndexY = mY + TileSize * y;
	mIsMove = true;
}