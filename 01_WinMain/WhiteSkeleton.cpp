#include "pch.h"
#include "WhiteSkeleton.h"

WhiteSkeleton::WhiteSkeleton(const string& name, int x, int y):Enemy(name)
{
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton1");
}

void WhiteSkeleton::GetDmg(int dmg)
{
}
