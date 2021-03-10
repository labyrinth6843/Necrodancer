#include "pch.h"
#include "Button.h"
#include "Image.h"

Button::Button(wstring imagekey, wstring text,float x, float y, float sizeX, float sizeY, function<void(void)> func)
{
	ImageManager::GetInstance()->LoadFromFile(L"Save", Resources(L"Save.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Load", Resources(L"Load.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Undo", Resources(L"Undo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Redo", Resources(L"Redo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Clear", Resources(L"Clear.bmp"), 88, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Play", Resources(L"Play.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Tool", Resources(L"Tool.bmp"), 72, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Ground", Resources(L"Ground.bmp"), 104, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Wall", Resources(L"Wall.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Deco", Resources(L"Deco.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Item", Resources(L"Item.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Object", Resources(L"Object.bmp"), 104, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Prev", Resources(L"Prev.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Next", Resources(L"Next.bmp"), 72, 48, 1, 2, false);

	mImage = ImageManager::GetInstance()->FindImage(imagekey);
	mText = text;
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mFrameX = 0;
	mFrameY = 0;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
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
	mImage->ScaleFrameRender(hdc, mX, mY, mFrameX, mFrameY, mSizeX, mSizeY);
}
