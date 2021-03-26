#include "pch.h"
#include "Minotaur.h"

Minotaur::Minotaur(const string & name, int x, int y):Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 3;
	mCoin = 10;
	mAtk = 2.f;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime2");
}

void Minotaur::Init()
{

}

void Minotaur::Update()
{

}

void Minotaur::Release()
{

}

void Minotaur::Render(HDC hdc)
{

}

void Minotaur::Attack()
{
}

void Minotaur::IsAttacked(int dmg)
{
}