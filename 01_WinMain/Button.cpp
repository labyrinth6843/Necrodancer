#include "pch.h"
#include "Button.h"
#include "Image.h"

Button::Button(wstring imagekey, wstring text,float x, float y, float sizeX, float sizeY, function<void(void)> func)
{
	//Image LoadFromFile은 필터 -> LoadImage.cpp로 옮김

	mText = text;
	mX = x;
	mY = y;
	mFrameX = 0;
	mFrameY = 0;
	mFunc = func;
	mState = State::Normal;
	if (imagekey != L"")
	{
		mImage = ImageManager::GetInstance()->FindImage(imagekey);
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
		mRect = RectMake(mX, mY, mSizeX, mSizeY);
	}
	else
	{
		mImage = nullptr;
		mSizeX = sizeX;
		mSizeY = sizeY;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

}

void Button::Update(){
	if (mState == State::Normal){
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON)){
			if (PtInRect(&mRect, _mousePosition)){
				mFrameY = 1;
				mState = State::Push;
			}
		}
	}
	else
	{
		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))	{
			mFrameY = 0;
			mState = State::Normal;
			if (mFunc != nullptr){
				mFunc();
			}
		}
	}
}

void Button::Render(HDC hdc){
	if(mImage != nullptr)
		mImage->ScaleFrameRender(hdc, mX, mY, mFrameX, mFrameY, mSizeX, mSizeY);
	else
	{
		if (mState == State::Normal)
			RenderRect(hdc, mRect);
		else
		{
			float sizeX = mSizeX * 0.75f;
			float sizeY = mSizeY * 0.75f;
			RECT rc = RectMakeCenter(mX, mY, sizeX, sizeY);
			RenderRect(hdc, rc);
		}

		TextOut(hdc, mX - mSizeX / 4, mY - mSizeY / 4, mText.c_str(), mText.length());
	}
}
