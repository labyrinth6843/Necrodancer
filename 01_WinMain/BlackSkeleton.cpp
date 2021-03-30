﻿#include "pch.h"
#include "BlackSkeleton.h"

BlackSkeleton::BlackSkeleton(const string& name, int x, int y) : Enemy(name){
	mX = x;
	mY = y;

	mHp = 3;
	mCoin = 4;
	mAtk = 2.f;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"Skeleton3");

	mUpLeftAnimation = new Animation();
	mUpLeftAnimation->InitFrameByStartEnd(0,0,7,0,false);
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

void BlackSkeleton::Attack() {
	mPlayerPtr->SetHp(GetHp() - mAtk);
	SoundPlayer::GetInstance()->Play(L"skeleton_attack", 1.f);
}

void BlackSkeleton::IsAttacked(int dmg)
{
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

void BlackSkeleton::Init()
{

}

void BlackSkeleton::Release()
{
	SafeDelete(mUpLeftAnimation);
	SafeDelete(mUpRightAnimation);
	SafeDelete(mDownLeftAnimation);
	SafeDelete(mDownRightAnimation);
}

void BlackSkeleton::Update()
{
	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void BlackSkeleton::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}