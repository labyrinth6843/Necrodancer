#include "pch.h"
#include "Minotaur.h"

Minotaur::Minotaur(const string & name, int x, int y):Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mHp = 3;
	mCoin = 10;
	mAtk = 2.f;

	mImage = ImageManager::GetInstance()->FindImage(L"Minotaur");

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0,0,4,0,false);
	mLeftAnimation->SetFrameUpdateTime(0.1f);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->Play();

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0,2,4,2,false);
	mRightAnimation->SetFrameUpdateTime(0.1f);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->Play();

	mLeftWallImpactAnimation = new Animation();
	mLeftWallImpactAnimation->InitFrameByStartEnd(5, 0, 8, 0, false);
	mLeftWallImpactAnimation->SetFrameUpdateTime(0.1f);
	mLeftWallImpactAnimation->SetIsLoop(true);
	mLeftWallImpactAnimation->Play();

	mRightWallImpactAnimation = new Animation;
	mRightWallImpactAnimation->InitFrameByStartEnd(5,2,8,2,false);
	mRightWallImpactAnimation->SetFrameUpdateTime(0.1f);
	mRightWallImpactAnimation->SetIsLoop(true);
	mRightWallImpactAnimation->Play();

}

void Minotaur::Init()
{

}

void Minotaur::Update()
{
	mCurrentAnimation->Update();
}

void Minotaur::Release()
{
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mLeftWallImpactAnimation);
	SafeDelete(mRightWallImpactAnimation);
}

void Minotaur::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}

void Minotaur::Attack()
{
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"minotaur_attack", 1.f);
}

void Minotaur::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"minotaur_death",1.f);
		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"minotaur_hit_3", 1.f);
			break;
		}
	}
}