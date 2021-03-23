#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(const string& name, int x, int y):Enemy(name)
{
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Zombie");

	direction = Random::GetInstance()->RandomInt(100) % 2;

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mLeftAnimation->SetFrameUpdateTime(0.1f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0, 2, 3, 2, false);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	if (direction == 0)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;
}

void Zombie::GetDmg(int dmg)
{
	mHp -= dmg;

	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"zombie_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
}
