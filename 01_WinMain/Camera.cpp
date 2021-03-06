#include "pch.h"
#include "Camera.h"

#include "Image.h"

Camera::Camera()
{
	mName = "Camera";
}

void Camera::Init()
{
	mMode = Mode::Follow;
	//mTarget = nullptr;
	//mX = WINSIZEX / 2;
	//mY = WINSIZEY / 2;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMoveSpeed = 5.f;
}

void Camera::Release()
{
	//얘도 쓸일이 없다 . . . 
}

void Camera::Update()
{
	switch (mMode)
	{
	case Camera::Mode::Follow:
		if (mTarget)
		{
			mX = mTarget->GetX();
			mY = mTarget->GetY();
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		break;
	case Camera::Mode::Smooth:
		if(mTarget)
		{
			mX = Math::Lerp(mX, mTarget->GetX(), 2.f * Time::GetInstance()->DeltaTime());
			mY = Math::Lerp(mY, mTarget->GetY(), 2.f * Time::GetInstance()->DeltaTime());
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		break;
	case Camera::Mode::Free:
		if (Input::GetInstance()->GetKey('A'))mX -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('D'))mX += mMoveSpeed;
		if (Input::GetInstance()->GetKey('W'))mY -= mMoveSpeed;
		if (Input::GetInstance()->GetKey('S'))mY += mMoveSpeed;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		break;
	}

	if (mShakeCount > 0)
	{
		mRect = RectMakeCenter(mX + (1.35f) * (Random::GetInstance()->RandomInt(3) - 1), 
							   mY + (1.35f) * (Random::GetInstance()->RandomInt(3) - 1), mSizeX, mSizeY);
		mShakeCount--;
	}
}
void Camera::CameraShake(int strength)
{
	mShakeCount = strength * 20;
}
void Camera::Render(HDC hdc)
{
	//쓸일이 없다 . . . . 
}

void Camera::Render(HDC hdc, Image * image, int x, int y)
{
	image->Render(hdc, x - mRect.left, y - mRect.top);
}

void Camera::Render(HDC hdc, Image * image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
{
	image->Render(hdc, x - mRect.left, y - mRect.top, tempX, tempY, tempWidth, tempHeight);
}

void Camera::FrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY)
{
	image->FrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY);
}

void Camera::AlphaRender(HDC hdc, Image * image, int x, int y, float alpha)
{
	image->AlphaRender(hdc, x - mRect.left, y - mRect.top, alpha);
}

void Camera::AlphaFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, float alpha)
{
	image->AlphaFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, alpha);
}

void Camera::ScaleRender(HDC hdc, Image * image, int x, int y, int width, int height)
{
	image->ScaleRender(hdc, x - mRect.left, y - mRect.top, width, height);
}

void Camera::ScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height)
{
	image->ScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height);
}

void Camera::AlphaScaleRender(HDC hdc, Image * image, int x, int y, int width, int height, float alpha)
{
	image->AlphaScaleRender(hdc, x - mRect.left, y - mRect.top, width, height, alpha);
}

void Camera::AlphaScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	image->AlphaScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height, alpha);
}

void Camera::RenderRect(HDC hdc, RECT rc)
{
	rc.left -= mRect.left;
	rc.right -= mRect.left;
	rc.top -= mRect.top;
	rc.bottom -= mRect.top;
	RenderRect(hdc, rc);
}

void Camera::RenderEllipse(HDC hdc, float x, float y, float radius)
{
	RenderEllipse(hdc, x - mRect.left, y - mRect.top, radius);
}

void Camera::RenderTextBox(HDC hdc, RECT rc, wstring st)
{
	TextOut(hdc, rc.right - mRect.left, rc.bottom - mRect.top, st.c_str(), st.length());
}

bool Camera::IsInCameraArea(float x, float y, float width, float height)
{
	RECT rc = RectMakeCenter(x, y, width, height);
	return IsInCameraArea(rc);
}

bool Camera::IsInCameraArea(RECT rc)
{
	if (rc.right < mRect.left)return false;
	if (rc.left > mRect.right)return false;
	if (rc.bottom < mRect.top)return false;
	if (rc.top > mRect.bottom)return false;

	return true;
}

bool Camera::IsInCameraArea(int x, int y, int range)
{
	if (x + range < mRect.left)return false;
	if (x - range > mRect.right)return false;
	if (y + range < mRect.top)return false;
	if (y - range > mRect.bottom)return false;

	return true;
}

bool Camera::IsInCameraArea(int x, int y)
{
	if (x < mRect.left)return false;
	if (x > mRect.right)return false;
	if (y < mRect.top)return false;
	if (y > mRect.bottom)return false;

	return true;
}
