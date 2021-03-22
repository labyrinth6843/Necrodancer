#include "pch.h"
#include "BlueSlime.h"

BlueSlime::BlueSlime(const string& name, int x, int y) : Enemy(name){
	mX = x;
	mY = y;

	mImage = ImageManager::GetInstance()->FindImage(L"Slime2");

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
};

void BlueSlime::Init()
{

}

void BlueSlime::Update()
{
	mCurrentAnimation->Update();
}

void BlueSlime::Release()
{
}

void BlueSlime::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX * TileSize, mY * TileSize, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), 39, 39);
}
