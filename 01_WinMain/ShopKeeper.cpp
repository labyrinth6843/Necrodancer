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
	mIdleAnimation->SetFrameUpdateTime(0.1f);
	mIdleAnimation->Play();

	mSingAnimation = new Animation();
	mSingAnimation->InitFrameByStartEnd(4, 0, 7, 0, false);
	mSingAnimation->SetIsLoop(true);
	mSingAnimation->SetFrameUpdateTime(0.1f);
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
	Player* temp = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (temp->DistanceShopkeeper() != 0)
		mCurrentAnimation = mSingAnimation;
	else
		mCurrentAnimation = mIdleAnimation;

	Ground* ground = (Ground*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground");
	ground->GetAlpha(mX / TileSize, mY / TileSize, mOpacity);
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
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
}
