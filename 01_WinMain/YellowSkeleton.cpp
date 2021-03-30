#include "pch.h"
#include "YellowSkeleton.h"

YellowSkeleton::YellowSkeleton(const string& name, int x, int y) : Enemy(name) {
	mX = x;
	mY = y;

	mHp = 2;
	mCoin = 3;
	mAtk = 1.5f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton2");

	mUpLeftAnimation = new Animation();
	mUpLeftAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mUpLeftAnimation->SetFrameUpdateTime(0.1f);
	mUpLeftAnimation->SetIsLoop(true);
	mUpLeftAnimation->Play();

	mUpRightAnimation = new Animation();
	mUpRightAnimation->InitFrameByStartEnd(0, 2, 7, 2, false);
	mUpRightAnimation->SetFrameUpdateTime(0.1f);
	mUpRightAnimation->SetIsLoop(true);
	mUpRightAnimation->Play();

	mDownLeftAnimation = new Animation();
	mDownLeftAnimation->InitFrameByStartEnd(0, 4, 7, 4, false);
	mDownLeftAnimation->SetFrameUpdateTime(0.1f);
	mDownLeftAnimation->SetIsLoop(true);
	mDownLeftAnimation->Play();

	mDownRightAnimation = new Animation();
	mDownRightAnimation->InitFrameByStartEnd(0, 6, 7, 6, false);
	mDownRightAnimation->SetFrameUpdateTime(0.1f);
	mDownRightAnimation->SetIsLoop(true);
	mDownRightAnimation->Play();
}

void YellowSkeleton::Attack() {
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	temp->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"skeleton_attack", 1.f);
}

void YellowSkeleton::IsAttacked(int dmg) {
	mHp -= dmg;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"skeleton_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"skeleton_hit_3", 1.f);
			break;
		}
	}
}

void YellowSkeleton::Init()
{
}

void YellowSkeleton::Release()
{
	SafeDelete(mUpLeftAnimation);
	SafeDelete(mUpRightAnimation);
	SafeDelete(mDownLeftAnimation);
	SafeDelete(mDownRightAnimation);
}

void YellowSkeleton::Update()
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

void YellowSkeleton::Render(HDC hdc)
{

}