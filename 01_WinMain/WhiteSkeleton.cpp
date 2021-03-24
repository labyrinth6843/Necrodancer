#include "pch.h"
#include "WhiteSkeleton.h"

WhiteSkeleton::WhiteSkeleton(const string& name, int x, int y):Enemy(name)
{
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton1");
}

void WhiteSkeleton::Attack(int destX, int destY) {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, POINT{ mDestIndexX, mDestIndexY });

	temp->SetHp(GetHp() - mAtk);
}

void WhiteSkeleton::IsAttacked(int dmg)
{
}
