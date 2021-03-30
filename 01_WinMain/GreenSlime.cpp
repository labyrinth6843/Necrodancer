#include "pch.h"
#include "GreenSlime.h"

GreenSlime::GreenSlime(const string & name, int x, int y):Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;
	
	mHp = 1;
	mCoin = 1;
	mAtk = 50.f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime1");

	mDirection = Random::GetInstance()->RandomInt(100) % 2;

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

	if (mDirection == 0)
		mCurrentAnimation = mLeftAnimation;
	else
		mCurrentAnimation = mRightAnimation;
}

void GreenSlime::Attack() {
	mPlayerPtr->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"slime_attack", 1.f);
}

void GreenSlime::IsAttacked(int dmg)
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

void GreenSlime::Init() {

}

void GreenSlime::Update()
{
	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void GreenSlime::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
}

void GreenSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() +(int)mIsVisible, 39, 39);
}