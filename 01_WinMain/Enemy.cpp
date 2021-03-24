#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const string& name) : GameObject(name){}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
}

void Enemy::Render(HDC hdc)
{
}

bool Enemy::WallCheck(int x, int y)
{
	mDestX = mX + TileSize * x;
	mDestY = mY + TileSize * y;

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall") != nullptr) {
		Wall* temp = (Wall*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Wall, "Wall");

		POINT mapsize = temp->GetMapSize();
		if (mDestIndexX < 0 || mDestIndexX >= mapsize.x || mDestIndexY < 0 || mDestIndexY >= mapsize.y)
			return false;

		if (temp->GetFrameIndexX(mDestIndexX, mDestIndexY) == 0 && temp->GetFrameIndexY(mDestIndexX, mDestIndexY) == 0)
			return false;
		else
			return true;
	}
}
