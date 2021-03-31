#include "pch.h"
#include "ShopKeeper.h"

ShopKeeper::ShopKeeper(const string& name, int x, int y):Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"ShopKeeper");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.5f);
	mIdleAnimation->Play();

	mSingAnimation = new Animation();
	mSingAnimation->InitFrameByStartEnd(4, 0, 7, 0, false);
	mSingAnimation->SetIsLoop(true);
	mSingAnimation->SetFrameUpdateTime(0.5f);
	mSingAnimation->Play();

	mCurrentAnimation = mIdleAnimation;
}

void ShopKeeper::Attack()
{

}

void ShopKeeper::IsAttacked(int dmg)
{

}

void ShopKeeper::Init()
{

}

void ShopKeeper::Update()
{
	SoundPlayer::GetInstance()->SetVolume(L"zone1_1_shopkeeper", mPlayerPtr->DistanceShopkeeper()*0.2f);

	if (mPlayerPtr->DistanceShopkeeper() != 0)
		mCurrentAnimation = mSingAnimation;
	else
		mCurrentAnimation = mIdleAnimation;

	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void ShopKeeper::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mSingAnimation);
}

void ShopKeeper::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX-15, mY-18, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 70, 57);
}