#include "pch.h"
#include "BlackSkeleton.h"

BlackSkeleton::BlackSkeleton(const string& name, int x, int y) : Enemy(name){
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton3");


}

void BlackSkeleton::Attack(int destX, int destY) {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, POINT{ mDestIndexX, mDestIndexY });

	temp->SetHp(GetHp() - mAtk);
}

void BlackSkeleton::IsAttacked(int dmg) {

}