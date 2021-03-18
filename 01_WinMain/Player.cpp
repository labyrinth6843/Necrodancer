#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"

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
	mBodyLeftAnimation->InitFrameByStartEnd(4, (int)mArmorType, 7, (int)mArmorType, false);
	mBodyLeftAnimation->SetIsLoop(true);
	mBodyLeftAnimation->SetFrameUpdateTime(0.1f);
	mBodyLeftAnimation->Play();

	mBodyRightAnimation = new Animation();
	mBodyRightAnimation->InitFrameByStartEnd(0, (int)mArmorType,3, (int)mArmorType,false);
	mBodyRightAnimation->SetIsLoop(true);
	mBodyRightAnimation->SetFrameUpdateTime(0.1f);
	mBodyRightAnimation->Play();

	//초기 설정이 필요한 값 입력
	mHp = 6;
	StartX = TileSize * 5;
	StartY = TileSize * 4;
	StartIndexX = StartX / TileSize;
	StartIndexY = StartY / TileSize;
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
	StartIndexX = StartX / TileSize;
	StartIndexY = StartY / TileSize;

	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
			if (StartIndexY > 0)
				Move(0, -1);

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if (StartIndexX < 9) {
				if (direction == false) {
					direction = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				Move(1, 0);
			}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (StartIndexX > 0) {
				if (direction == true) {
					direction = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				Move(-1, 0);
			}
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if (StartIndexY < 9)
				Move(0, 1);
	}
	else {
		StartX += TileSize * 3 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(StartX, StartY, EndX, EndY));
		StartY += TileSize * 3 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(StartX, StartY, EndX, EndY));

		if (Math::GetDistance(StartX, StartY, EndX, EndY) < TileSize / 2)
			StartY += 1;
		else
			StartY -= 1;

		if (fabs(EndX - StartX) <= 0.5 && fabs(EndY - StartY) <= 0.5) {
			StartX = EndX;
			StartY = EndY;
			mIsMove = false;
		}
	}
	mCurrentHeadAnimation->Update();
	mCurrentBodyAnimation->Update();
}

void Player::Render(HDC hdc) {
	//수정이 많이 필요한 부분
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mBodyImage, StartX, StartY, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY(), 34, 30);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mHeadImage, StartX + 2, StartY - 14, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY(), 28, 22);
}

void Player::Move(int x, int y) {
	EndX = StartX + TileSize * x;
	EndY = StartY + TileSize * y;

	EndIndexX = EndX / TileSize;
	EndIndexY = EndY / TileSize;

	Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Monster, POINT{ (int)EndIndexX, (int)EndIndexY }));
	Dig(ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, POINT{ (int)EndIndexX, (int)EndIndexY }));
	Equip(ObjectManager::GetInstance()->FindObject(ObjectLayer::Item, POINT{ (int)EndIndexX, (int)EndIndexY }));

	mIsMove = true;
}

void Player::Dig(GameObject* object) {
	Wall* temp = (Wall*)object;
}

void Player::Attack(GameObject* object) {

}

void Player::Equip(GameObject* object) {

}