#include "pch.h"
#include "KingConga.h"

KingConga::KingConga(const string& name, int x, int y): Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	InitX = mX;
	InitY = mY;

	mHp = 2;
	mCoin = 50;
	mAtk = 1.f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"KingConga");
	mThroneImage = ImageManager::GetInstance()->FindImage(L"KingCongaThrone");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.1f);
	mIdleAnimation->Play();

	mMoveAnimation = new Animation();
	mMoveAnimation->InitFrameByStartEnd(5, 0, 6, 0, false);
	mMoveAnimation->SetIsLoop(true);
	mMoveAnimation->SetFrameUpdateTime(0.5f);
	mMoveAnimation->Play();

	mCurrentAnimation = mIdleAnimation;
}

void KingConga::Init()
{

}

void KingConga::Update()
{
	Ground* ground = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground");
	ground->GetAlpha(mX / TileSize, mY / TileSize, mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void KingConga::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mMoveAnimation);
}

void KingConga::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mThroneImage, InitX, InitY, 39, 39);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}

void KingConga::Attack()
{
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	int random = Random::GetInstance()->RandomInt(100) % 3;
	switch (random) {
	case 0:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_1", 1.f);
		break;
	case 1:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_2", 1.f);
		break;
	case 2:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_3", 1.f);
		break;
	}
}

void KingConga::IsAttacked(int dmg)
{
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"kingconga_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_3", 1.f);
			break;
		}
	}
}

void KingConga::Move(int dirX, int dirY)
{
}
