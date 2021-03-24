#include "pch.h"
#include "BlackSkeleton.h"

BlackSkeleton::BlackSkeleton(const string& name, int x, int y) : Enemy(name){
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton3");


}

void BlackSkeleton::GetDmg(int dmg) {

}