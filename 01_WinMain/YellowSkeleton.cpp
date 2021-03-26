#include "pch.h"
#include "YellowSkeleton.h"

YellowSkeleton::YellowSkeleton(const string& name, int x, int y) : Enemy(name) {
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton2");
}

void YellowSkeleton::Attack() {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
}

void YellowSkeleton::IsAttacked(int dmg) {
	mHp -= dmg;
	if (mHp <= 0) {
		this->SetIsActive(false);
		this->SetIsDestroy(true);
	}
}

void YellowSkeleton::Init()
{
}

void YellowSkeleton::Update()
{
}

void YellowSkeleton::Release()
{
}

void YellowSkeleton::Render(HDC hdc)
{
}
