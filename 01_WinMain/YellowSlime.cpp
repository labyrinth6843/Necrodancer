#include "pch.h"
#include "YellowSlime.h"

YellowSlime::YellowSlime(const string& name, int x, int y) :Enemy(name) {
	mX = x;
	mY = y;

	mHp = 1;
	mCoin = 2;
	mAtk = 0.5f;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime3");

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

void YellowSlime::Attack(int destX, int destY) {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, POINT{ mDestIndexX, mDestIndexY });

	temp->SetHp(GetHp() - mAtk);
}

void YellowSlime::IsAttacked(int dmg)
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

void YellowSlime::Init()
{
	
}

void YellowSlime::Update()
{
	mCurrentAnimation->Update();
}

void YellowSlime::Release()
{
}

void YellowSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX * TileSize, mY * TileSize, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}
