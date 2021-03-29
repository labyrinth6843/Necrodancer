#include "pch.h"
#include "KingConga.h"

KingConga::KingConga(const string& name, int x, int y): Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

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
	mCurrentAnimation->Update();
}

void KingConga::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mMoveAnimation);
}

void KingConga::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}