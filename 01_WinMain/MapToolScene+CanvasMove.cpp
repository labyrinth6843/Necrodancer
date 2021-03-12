#include "pch.h"
#include "MapToolScene.h"

void MapToolScene::CanvasMove()
{
	if (Input::GetInstance()->GetKeyDown(VK_UP))
	{
		mMinIndexY--;
		if (mMinIndexY < 0)
			mMinIndexY = 0;
	}
	if (Input::GetInstance()->GetKeyDown(VK_DOWN))
	{
		mMinIndexY++;
		if (mMinIndexY >= mMaxSizeY)
			mMinIndexY = mMaxSizeY;
	}
	if (Input::GetInstance()->GetKeyDown(VK_LEFT))
	{
		mMinIndexX--;
		if (mMinIndexX < 0)
			mMinIndexX = 0;
	}
	if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
	{
		mMinIndexX++;
		if (mMinIndexX >= mMaxSizeX)
			mMinIndexX = mMaxSizeX;
	}
}

void MapToolScene::ButtonMove(int key, int move)//¹öÆ°¿ë
{
	if (key == VK_UP)
	{
		mMinIndexY = mMinIndexY - move;
		if (mMinIndexY < 0)
			mMinIndexY = 0;
	}
	if (key == VK_DOWN )
	{
		mMinIndexY = mMinIndexY + move;
		if (mMinIndexY >= mMaxSizeY)
			mMinIndexY = mMaxSizeY;
	}
	if (key == VK_LEFT )
	{
		mMinIndexX = mMinIndexX - move;
		if (mMinIndexX < 0)
			mMinIndexX = 0;
	}
	if (key == VK_RIGHT)
	{
		mMinIndexX = mMinIndexX + move;
		if (mMinIndexX >= mMaxSizeX)
			mMinIndexX = mMaxSizeX;
	}
}