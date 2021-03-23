#include "pch.h"
#include "BlueSlime.h"

BlueSlime::BlueSlime(const string& name, int x, int y) : Enemy(name){
	mX = x;
	mY = y;

	mHp = 2;
	mCoin = 2;
	mAtk = 1.f;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime2");

	direction = Random::GetInstance()->RandomInt(100) % 4;

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mLeftAnimation->SetFrameUpdateTime(0.5f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightAnimation->SetFrameUpdateTime(0.5f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	if (direction == 0)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;

	switch (direction) {
	case 0:
		destX = mX;
		destY = mY - TileSize;
		break;
	case 1:
		destX = mX - TileSize;
		destY = mY;
		mCurrentAnimation = mLeftAnimation;
		break;
	case 2:
		destX = mX + TileSize;
		destY = mY;
		mCurrentAnimation = mRightAnimation;
		break;
	case 3:
		destX = mX;
		destY = mY + TileSize;
		break;
	}
};

void BlueSlime::Init()
{

}

void BlueSlime::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		Move(destX, destY);
	}



	mCurrentAnimation->Update();
}

void BlueSlime::Release()
{
}

void BlueSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX * TileSize, mY * TileSize, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void BlueSlime::Move(int destX, int destY) {
	if (ObjectManager::GetInstance()->FindObject(POINT{ destX, destY }) == NULL) {
		mX += 3*cosf(Math::GetAngle(mX, mY, destX, destY));
		mY += 3*-sinf(Math::GetAngle(mX, mY, destX, destY));

		if (Math::GetDistance(mX, mY, destX, destY) <= 0.5) {
			mX = destX;
			mY = destY;
		}
	}
	else if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, POINT{destX, destY}) != NULL)
		Attack();
}

void BlueSlime::Attack() {

}

void BlueSlime::GetDmg(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"slime_death_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"slime_death_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"slime_death_3", 1.f);
			break;
		}

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}
