#include "pch.h"
#include "YellowSkeleton.h"

YellowSkeleton::YellowSkeleton(const string& name, int x, int y) : Enemy(name) {
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton2");
}

void YellowSkeleton::GetDmg(int dmg) {
	mHp -= dmg;
	if (mHp <= 0) {
		this->SetIsActive(false);
		this->SetIsDestroy(true);
	}
}