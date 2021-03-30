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
}

void Wall::Update()
{
	mGroundPtr->GetShowArea(mMinIndexX, mMinIndexY, mMaxIndexX, mMaxIndexY);
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