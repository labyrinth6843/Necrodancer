#include "pch.h"
#include "Wall.h"
#include "Camera.h"
#include "Ground.h"

Wall::Wall(const string& name) : GameObject(name) {}

void Wall::Init(){
	SetGroundPtr("Ground");
	FileManager::LoadMap(L"Test01", mWallList, TileSize, 72);
	FileManager::LoadMap(L"Test02", mDecoList, TileSize);

	mMapSizeY = mWallList.size();
	mMapSizeX = mWallList[0].size();

	mWallShadow = IMAGEMANAGER->FindImage(L"WallShadow");
	mFrameCount = 0;
}

void Wall::Update()
{
	mFrameCount += 100 * Time::GetInstance()->DeltaTime();
	mGroundPtr->GetShowArea(mMinIndexX, mMinIndexY, mMaxIndexX, mMaxIndexY);
	for (int y = mMinIndexY; y < mMaxIndexY; ++y)
	{
		for (int x = mMinIndexX; x < mMaxIndexX; ++x)
		{
			int posx = x * TileSize;
			int posy = y * TileSize;
			if (mWallList[y][x]->GetImage() != NULL && (mWallList[y][x]->GetFrameIndexX() != 0 || mWallList[y][x]->GetFrameIndexY() != 0))
			{
				if (mDecoList[y][x]->GetFrameIndexX() != 0 || mDecoList[y][x]->GetFrameIndexY() != 0)
				{
					mGroundPtr->GetSight(x, y, 5);
					if (mFrameCount>5)
					{
						int nextX = mDecoList[y][x]->GetFrameIndexX() + 1;
						if (nextX >= 5)
							nextX = 1;
						mDecoList[y][x]->SetFrameIndexX(nextX);
					}
				}
			}
		}
	}
	if(mFrameCount > 5)
		mFrameCount = 0;
}

void Wall::Release()
{
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			SafeDelete(mWallList[y][x]);
			SafeDelete(mDecoList[y][x]);
		}
	}
	mWallList.clear();
	mDecoList.clear();
}

void Wall::Render(HDC hdc)
{
	for (int y = mMinIndexY; y < mMaxIndexY; ++y)
	{
		for (int x = mMinIndexX; x < mMaxIndexX; ++x)
		{
			int posx = x * TileSize;
			int posy = y * TileSize;
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(posx, posy, TileSize))
			{
				if (mWallList[y][x]->GetImage() != NULL)
				{
					if (mWallList[y][x]->GetFrameIndexX() != 0 || mWallList[y][x]->GetFrameIndexY() != 0)
					{
						float alpha = 1.f;
						if (mGroundPtr->GetAlpha(x, y, alpha))
						{
							CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mWallShadow, posx, posy, TileSize , TileSize);
							CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mWallList[y][x]->GetImage(),
								posx, posy, mWallList[y][x]->GetFrameIndexX(), mWallList[y][x]->GetFrameIndexY(),
								mWallList[y][x]->Getwidth(), mWallList[y][x]->GetHeight(), alpha);

						}
						if (mDecoList[y][x]->GetFrameIndexX() != 0 || mDecoList[y][x]->GetFrameIndexY() != 0)
						{
							float alpha = 1.f;
							if (mGroundPtr->GetAlpha(x, y, alpha))
							{
								CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mDecoList[y][x]->GetImage(),
									posx, posy, mDecoList[y][x]->GetFrameIndexX(), mDecoList[y][x]->GetFrameIndexY(),
									mDecoList[y][x]->Getwidth(), mDecoList[y][x]->GetHeight(), alpha);

							}
						}
					}
				}
			}
		}
	}
}

bool Wall::IsWall(int indexX, int indexY)
{
	//장외처리
	if (indexX < 0 || indexX >= mMapSizeX || indexY < 0 || indexY >= mMapSizeY)
		return false;

	if (mWallList[indexY][indexX]->GetFrameIndexX() != 0 || mWallList[indexY][indexX]->GetFrameIndexY() != 0)
		return true;
	return false;
}