#include "pch.h"
#include "WhiteSkeleton.h"

WhiteSkeleton::WhiteSkeleton(const string& name, int x, int y):Enemy(name)
{
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton1");
}

void WhiteSkeleton::Attack() {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
}

void WhiteSkeleton::IsAttacked(int dmg)
{
}

void WhiteSkeleton::Init()
{
}

void WhiteSkeleton::Update()
{
}

void WhiteSkeleton::Release()
{
}

void WhiteSkeleton::Render(HDC hdc)
{
}
