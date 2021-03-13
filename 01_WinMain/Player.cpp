#include "pch.h"
#include "Player.h"
Player::Player(const string& name) : GameObject(name) {

}

void Player::Init() {
	mHeadImage = ImageManager::GetInstance()->FindImage(L"Head");
	mBodyImage = ImageManager::GetInstance()->FindImage(L"Body");

	mHp = 6;
	mX = 100 + TileSize * 5;
	mY = 200 + TileSize * 4;
	indexX = mX / TileSize;
	indexY = mY / TileSize;
}

void Player::Release() { 

}

void Player::Update() {
	indexX = (mX - 100) / TileSize;
	indexY = (mY - 200) / TileSize;

	if (mIsMove == false) {
		if (Input::GetInstance()->GetKeyDown(VK_UP) || Input::GetInstance()->GetKeyDown('W')) {
			if (indexY > 0)
				Move(0, -1);
		}
	
		if (Input::GetInstance()->GetKeyDown(VK_LEFT) || Input::GetInstance()->GetKeyDown('A')) {
			if(indexX > 0)
				Move(-1, 0);
		}
			
		if (Input::GetInstance()->GetKeyDown(VK_DOWN) || Input::GetInstance()->GetKeyDown('S'))
			if(indexY < 9)
				Move(0, 1);
	
		if (Input::GetInstance()->GetKeyDown(VK_RIGHT) || Input::GetInstance()->GetKeyDown('D'))
			if(indexX < 9)
				Move(1, 0);
	}
	else {
		mX += TileSize*2 * Time::GetInstance()->DeltaTime() *  cosf(Math::GetAngle(mX, mY, destX, destY));
		mY += TileSize*2 * Time::GetInstance()->DeltaTime() * -sinf(Math::GetAngle(mX, mY, destX, destY));

		if (fabs(destX - mX) <= 0.5 && fabs(destY - mY) <= 0.5) {
			mX = destX;
			mY = destY;
			mIsMove = false;
		}
	}
}

void Player::Render(HDC hdc) {

}

void Player::Move(int x, int y) {
	destX = mX + TileSize * x;
	destY = mY + TileSize * y;
	mIsMove = true;
}