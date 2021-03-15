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
	FileManager::GetInstance()->LoadMap(L"Test00",mGroundList, TileSize);
	FileManager::GetInstance()->LoadMap(L"Test01", mDecoList, TileSize);

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
				//if(mGroundList[y][x]->GetImage() != NULL)
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mGroundList[y][x]->GetImage(),
					mGroundList[y][x]->GetX(), mGroundList[y][x]->GetY(), mGroundList[y][x]->GetFrameIndexX(), mGroundList[y][x]->GetFrameIndexY(),
					mGroundList[y][x]->Getwidth(), mGroundList[y][x]->GetHeight(), 1.0f
					);
				if (mDecoList[y][x]->GetImage() != NULL)
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mDecoList[y][x]->GetImage(),
						mDecoList[y][x]->GetX(), mDecoList[y][x]->GetY(), mDecoList[y][x]->GetFrameIndexX(), mDecoList[y][x]->GetFrameIndexY(),
						mDecoList[y][x]->Getwidth(), mDecoList[y][x]->GetHeight(), 1.0f
					);
			}
		}
		int a = 1;
	}
}

bool Ground::GetSight()
{
	return false;
}
