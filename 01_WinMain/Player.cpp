#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ground.h"
#include "Item.h"

Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	//이미지 로드
	mHeadImage = ImageManager::GetInstance()->FindImage(L"Head");
	mBodyImage = ImageManager::GetInstance()->FindImage(L"Body");
	mShovelImage = ImageManager::GetInstance()->FindImage(L"Shovel");

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
	mImageY = 0.f;
	mStartIndexX = mX / TileSize;
	mStartIndexY = mY / TileSize;
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
	mStartIndexX = mX / TileSize;
	mStartIndexY = mY / TileSize;

	//이동 중이지 않을 때 각 입력에 대한 처리
	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W')){
			if (Beat::GetInstance()->IsDecision() == true) {
				//목적지 타일의 벽 유무 검사
				if (WallCheck(0, -1) == true)
					Dig(0, -1);//있으면 채광
				else
					Interaction(0, -1);//없으면 다른 상호작용
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (mIsLeft == false) {
					mIsLeft = true;
					mCurrentHeadAnimation = mHeadRightAnimation;
					mCurrentBodyAnimation = mBodyRightAnimation;
				}
				if (WallCheck(1, 0) == true)
					Dig(1, 0);
				else
					Interaction(1, 0);					
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (mIsLeft == true) {
					mIsLeft = false;
					mCurrentHeadAnimation = mHeadLeftAnimation;
					mCurrentBodyAnimation = mBodyLeftAnimation;
				}
				if (WallCheck(-1, 0) == true)
					Dig(-1, 0);
				else
					Interaction(-1, 0);
			}
		}

		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S')) {
			if (Beat::GetInstance()->IsDecision() == true) {
				if (WallCheck(0, 1) == true)
					Dig(0, 1);
				else
					Interaction(0, 1);
			}
		}
	}
	else {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;
		mX = Math::Lerp(mStartX, mEndX, ratio);
		mY = Math::Lerp(mStartY, mEndY, ratio);

		mImageY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mX = mEndX;
			mY = mEndY;
			mImageY = 0.f;
			mIsMove = false;
		}
	}

	if (mShowShovel == true) {
		mShowShovelFrame-=0.1f;
		if (mShowShovelFrame <= 0.f)
			mShowShovel = false;
	}

	mCurrentHeadAnimation->Update();
	mCurrentBodyAnimation->Update();
}

void Player::Render(HDC hdc) {
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mBodyImage, mX +5, mY + mImageY +6, mCurrentBodyAnimation->GetNowFrameX(), mCurrentBodyAnimation->GetNowFrameY(), 34, 30);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mHeadImage, mX +5 + 2, mY + mImageY +6 - 14, mCurrentHeadAnimation->GetNowFrameX(), mCurrentHeadAnimation->GetNowFrameY(), 28, 22);
	if (mShowShovel == true)
		CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mShovelImage, mEndX, mEndY, (int)mShovelType - 1, 0, TileSize, TileSize);
}

float Player::DistanceShopkeeper(GameObject* object) {
	//직선거리로 10칸을 넘어가는지 확인, 넘어갔다면 소리가 아예 들리지 않는다
	if (Math::GetDistance(mStartIndexX, mStartIndexY, object->GetX() / TileSize, object->GetY() / TileSize) < 10)
		return 0.f;
	//나온 직선거리를 역수를 취해 볼륨값으로 반환
	else
		return 1 / Math::GetDistance(mStartIndexX, mStartIndexY, object->GetX() / TileSize, object->GetY() / TileSize);
}

void Player::Move(int x, int y) {
	//이동용 Ground
	Ground* ground;
	if (ObjectManager::GetInstance()->FindObject("Ground"))
		ground = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	else
		return;

	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	mStartX = mX;
	mStartY = mY;
	mMoveTime = 0.f;
	mJumpPower = 150.f;
	mImageY = 0.f;

	if(ground->IsMove(mEndIndexX, mEndIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

bool Player::WallCheck(int x, int y)
{
	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall") != nullptr) {
		Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

		POINT mapsize = temp->GetMapSize();
		if (mEndIndexX < 0 || mEndIndexX >= mapsize.x || mEndIndexY < 0 || mEndIndexY >= mapsize.y)
			return false;

		if (temp->GetFrameIndexX(mEndIndexX, mEndIndexY) == 0 && temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 0)
			return false;
		else
			return true;
	}
}

void Player::Dig(int x, int y) {
	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

	if (temp->GetFrameIndexX(mEndIndexX, mEndIndexY) == 0 && temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 0)
		return;

	mShowShovel = true;
	mShowShovelFrame = 01.0f;

	if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) == 6) {
		SoundPlayer::GetInstance()->Play(L"move_fail", 1.f);
		Combo::GetInstance()->ComboReset();
		return;
	}

	if (mShovelPower >= temp->GetDigLevel()) {
		if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 4)
			SoundPlayer::GetInstance()->Play(L"move_dirt", 1.f);
		else if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 5)
			SoundPlayer::GetInstance()->Play(L"move_stone", 1.f);
		else if (temp->GetFrameIndexY(mEndIndexX, mEndIndexY) < 6)
			SoundPlayer::GetInstance()->Play(L"move_brick", 1.f);			

		temp->SetFrameIndexX(mEndIndexX, mEndIndexY, 0);
		temp->SetFrameIndexY(mEndIndexX, mEndIndexY, 0);
	}
}

void Player::Attack(GameObject* object) {
	if (object == nullptr)
		return;
	Enemy* temp = (Enemy*)object;
	
	temp->IsAttacked(mWeaponPower);
	Combo::GetInstance()->ComboUp();
}

void Player::Equip(GameObject* object) {
	if (object == nullptr)
		return;

	Item* temp = (Item*)object;

	
}

bool Player::AttackRangeCheck(WeaponType weapontype, int destX, int destY, int dirX, int dirY) {
	switch (weapontype) {
	case WeaponType::None:
		return false;
		break;

	case WeaponType::Dagger:
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
			return true;
		}
		else
			return false;
		break;

	case WeaponType::Broadsword:
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
		}
		else{
			if (dirY == 0) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }) != nullptr ||
					ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }));
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }));
				}
			}
			else {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }) != nullptr ||
					ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }));
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }));
				}
			}
			return true;
		}
		return false;
		break;

	case WeaponType::Longsword:
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
			if (dirX == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }));
			}

			else if (dirX == -1) {
				if(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }));
			}
				
			else if (dirY == 1) {
				if(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }));
			}
				
			else if (dirY == -1) {
				if(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }));
			}
			return true;
		}
		else
			return false;
		break;

	case WeaponType::Spear:
		//입력 방향에 오브젝트 유무 확인 후 있다면 공격
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
			return true;
		}
		//없으면 그 너머 범위까지 체크
		else {
			if (dirX == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }));
					return true;
				}
			}

			else if (dirX == -1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }));
					return true;
				}
			}

			else if (dirY == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }));
					return true;;
				}
			}

			else if (dirY == -1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }));
					return true;
				}
			}
			return false;
		}
		break;

	case WeaponType::Bow:
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
			return true;
		}
		else {
			if (dirX == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }));
					return true;
				}
				else if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 2, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 2, destY }));
					return true;
				}
			}
			else if (dirX == -1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }));
					return true;
				}
				else if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 2, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 2, destY }));
					return true;
				}
			}

			else if (dirY == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }));
					return true;
				}
				else if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 2 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 2 }));
					return true;
				}
			}

			else if (dirY == -1) {
				if(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }));
				else if(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 2 }) != nullptr)
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 2 }));
			}
			return false;
		}
		break;
		
	case WeaponType::Rapier:
		//입력 방향에 오브젝트 유무 확인 후 있다면 공격
		if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }) != nullptr) {
			Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY }));
			return true;
		}
		//없으면 그 너머 범위까지 체크
		else {
			if (dirX == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX + 1, destY }));
					Move(destX, destY);
					return true;
				}
			}
			else if (dirX == -1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX - 1, destY }));
					Move(destX, destY);
					return true;
				}
			}
			else if (dirY == 1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY + 1 }));
					Move(destX, destY);
					return true;
				}
			}
			else if (dirY == -1) {
				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }) != nullptr) {
					Attack(ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ destX, destY - 1 }));
					Move(destX, destY);
					return true;
				}
			}
			return false;
		}
		break;
	}
	return false;
}

void Player::Interaction(int x, int y)
{
	mEndX = mX + TileSize * x;
	mEndY = mY + TileSize * y;

	mEndIndexX = mEndX / TileSize;
	mEndIndexY = mEndY / TileSize;

	if (AttackRangeCheck(mWeaponType, mEndIndexX, mEndIndexY, x, y) == false) {
		Equip(ObjectManager::GetInstance()->FindObject(ObjectLayer::Item, POINT{ mEndIndexX, mEndIndexY }));
		Move(x, y);
	}
}