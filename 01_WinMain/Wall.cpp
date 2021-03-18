#include "pch.h"
#include "Wall.h"
#include "Camera.h"

Wall::Wall(const string& name) : GameObject(name) {}

void Wall::Init(){
	FileManager::LoadMap(L"Test01", mWallList, TileSize, 72);
	FileManager::LoadMap(L"Test02", mDecoList, TileSize);

	mMapSizeY = mWallList.size();
	mMapSizeX = mWallList[0].size();
}

void Wall::Update()
{

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
	mWallList.shrink_to_fit();

	mDecoList.clear();
	mDecoList.shrink_to_fit();
}

void Wall::Render(HDC hdc)
{
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			int posx = x * TileSize;
			int posy = y * TileSize;
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(posx, posy, TileSize))
			{
				if (mWallList[y][x]->GetImage() != NULL)
				{
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mWallList[y][x]->GetImage(),
						posx, posy, mWallList[y][x]->GetFrameIndexX(), mWallList[y][x]->GetFrameIndexY(),
						mWallList[y][x]->Getwidth(), mWallList[y][x]->GetHeight(), 1.0f);
					int a = 1;
				}
			}
		}
	}
}
