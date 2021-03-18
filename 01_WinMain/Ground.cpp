#include "pch.h"
#include "Ground.h"
#include "Camera.h"
Ground::Ground(const string &name, int startx, int starty) : GameObject(name)
{
	mX = startx;
	mY = starty;
}
void Ground::Init()
{
	mBack = IMAGEMANAGER->FindImage(L"Black");
	FileManager::LoadMap(L"Test00",mGroundList, TileSize);
	FileManager::LoadMap(L"Test01", mWallList, TileSize, 72);
	FileManager::LoadMap(L"Test02", mDecoList, TileSize);

	mMapSizeY = mGroundList.size();
	mMapSizeX = mGroundList[0].size();
}

void Ground::Release()
{
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			SafeDelete(mGroundList[y][x]);
			SafeDelete(mDecoList[y][x]);
		}
	}
	mGroundList.clear();
	mGroundList.shrink_to_fit();
	mDecoList.clear();
	mDecoList.shrink_to_fit();
}

void Ground::Update()
{
}

void Ground::Render(HDC hdc)
{
	//배경검정색
	mBack->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);

	//타일찍기
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			//맵 전체를 랜더하면 엄청 느려지니 처리 생각하기
			int posx = x * TileSize;
			int posy = y * TileSize;
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(posx, posy, TileSize))
			{
				if(mGroundList[y][x]->GetImage() != NULL)
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mGroundList[y][x]->GetImage(),
					posx, posy, mGroundList[y][x]->GetFrameIndexX(), mGroundList[y][x]->GetFrameIndexY(),
					mGroundList[y][x]->Getwidth(), mGroundList[y][x]->GetHeight(), 1.0f);
			}
		}
	}
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			//맵 전체를 랜더하면 엄청 느려지니 처리 생각하기
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

bool Ground::GetSight()
{
	return false;
}
