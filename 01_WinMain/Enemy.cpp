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
