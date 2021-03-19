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
	mX = TileSize * 8;
	mY = TileSize * 4;
	StartIndexX = mX / TileSize;
	StartIndexY = mY / TileSize;
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
	StartIndexX = mX / TileSize;
	StartIndexY = mY / TileSize;

	//이동 중이지 않을 때 각 입력에 대한 처리
	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W'))
			if (StartIndexY > 0) {
				//이동하려는 타일에 오브젝트가 존재하는가 확인
				if (TileCheck(0, -1) == false)
					Move(0, -1);
				//무엇인가가 존재하므로 상호작용 처리
				else
					Interaction(0, -1);
			}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if (StartIndexX < 9) {
				if (direction == false) {
					direction = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				if (TileCheck(1, 0) == false)
					Move(1, 0);
				else
					Interaction(1, 0);
			}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (StartIndexX > 0) {
				if (direction == true) {
					direction = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				if (TileCheck(-1, 0) == false)
					Move(-1, 0);
				else
					Interaction(-1, 0);
			}
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if (StartIndexY < 9) {
				if (TileCheck(0, 1) == false)
					Move(0, 1);
				else
					Interaction(0, 1);
			}
				
	}
	else {
		//목표 좌표로 서서히 움직이는 처리
		mX += TileSize * 3 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(mX, mY, EndX, EndY));
		mY += TileSize * 3 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(mX, mY, EndX, EndY));

		//목표지점까지 거리를 확인하여 포물선으로 움직이게끔 구현
		if (Math::GetDistance(mX, mY, EndX, EndY) < TileSize / 2)
			mY += 1;
		else
			mY -= 1;

		//완벽하게 도착할 수 없으니 시각적으로 문제가 없을 거리가 되면 이동이 완료되게끔 보정
		if (fabs(EndX - mX) <= 0.5 && fabs(EndY - mY) <= 0.5) {
			mX = EndX;
			mY = EndY;
			mIsMove = false;
		}
	}
	mCurrentHeadAnimation->Update();
	mCurrentBodyAnimation->Update();
}

void Player::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mBodyImage, mX, mY, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY(), 34, 30);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mHeadImage, mX + 2, mY - 14, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY(), 28, 22);
}

float Player::DistanceShopkeeper(GameObject* object) {
	//직선거리로 10칸을 넘어가는지 확인, 넘어갔다면 소리가 아예 들리지 않는다
	if (Math::GetDistance(StartIndexX, StartIndexY, object->GetX() / TileSize, object->GetY() / TileSize) < 10)
		return 0.f;
	//나온 직선거리를 역수를 취해 볼륨값으로 반환
	else
		return 1 / Math::GetDistance(StartIndexX, StartIndexY, object->GetX() / TileSize, object->GetY() / TileSize);
}

bool Player::TileCheck(int x, int y) {
	EndX = mX + TileSize * x;
	EndY = mY + TileSize * y;

	EndIndexX = EndX / TileSize;
	EndIndexY = EndY / TileSize;

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall") != nullptr) {
		Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

		if (temp->GetFrameIndexX(EndIndexX, EndIndexY) == 0 && temp->GetFrameIndexY(EndIndexX, EndIndexY) == 0)
			return false;
		else
			return true;
	}

	if (ObjectManager::GetInstance()->FindObject(POINT{ (int)EndIndexX, (int)EndIndexY }) == nullptr)
		return false;
	else
		return true;
}

void Player::Move(int x, int y) {
	EndX = mX + TileSize * x;
	EndY = mY + TileSize * y;

	EndIndexX = EndX / TileSize;
	EndIndexY = EndY / TileSize;

	mIsMove = true;
}

void Player::Dig(int x, int y) {
	Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

	if (temp->GetFrameIndexX(x, y) == 0 && temp->GetFrameIndexY(x, y) == 0)
		return;

	//파일 저장할 때 벽 경도 저장하면 좋을 거 같긴 한데 어려울려나
	if (mShovelPower >= temp->GetDigLevel()) {
		temp->SetFrameIndexX(x, y, 0);
		temp->SetFrameIndexY(x, y, 0);
	}

	//if (mShovelPower >= temp->GetDigLevel()) {
	//	object->SetIsActive(false);
	//	object->SetIsDestroy(true);
	//}
}

void Player::Attack(GameObject* object) {
	if (object == nullptr)
		return;
	Enemy* temp = (Enemy*)object;

	temp->SetHp(temp->GetHp() - mWeaponPower);

	if (temp->GetHp() <= 0) {
		object->SetIsActive(false);
		object->SetIsDestroy(true);
	}
}

void Player::Equip(GameObject* object) {
	if (object == nullptr)
		return;

	Item* temp = (Item*)object;

	
}

void Player::Interaction(int x, int y)
{
	EndX = mX + TileSize * x;
	EndY = mY + TileSize * y;

	EndIndexX = EndX / TileSize;
	EndIndexY = EndY / TileSize;

	Dig(EndIndexX, EndIndexY);
	Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Monster, POINT{ (int)EndIndexX, (int)EndIndexY }));
	Equip(ObjectManager::GetInstance()->FindObject(ObjectLayer::Item, POINT{ (int)EndIndexX, (int)EndIndexY }));
}