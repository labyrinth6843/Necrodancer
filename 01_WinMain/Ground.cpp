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

	//원활한 작업을 위해타일의 이미지 포인터 변경
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			if (mGroundList[y][x]->GetImage() != NULL)
			{
				//채워진 타일일때
				if (mGroundList[y][x]->GetFrameIndexX() != 0 || mGroundList[y][x]->GetFrameIndexY() != 0)
				{
					//홀수일때
					if ((x + y) & 1)
					{
						mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));
						mGroundList[y][x]->SetFrameIndexX(0);
						mGroundList[y][x]->SetFrameIndexY(0);
					}
					//짝수일때
					else
					{
						mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));
						mGroundList[y][x]->SetFrameIndexX(1);
						mGroundList[y][x]->SetFrameIndexY(0);
					}
				}
			}
		}
	}
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
	//턴마다 타일 변경하기
	if(BEAT->NextTurn())
	{
		for (int y = 0; y < mMapSizeY; ++y)
		{
			for (int x = 0; x < mMapSizeX; ++x)
			{

				int posx = x * TileSize;
				int posy = y * TileSize;
				if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(posx, posy, TileSize))
				{
					if (mGroundList[y][x]->GetImage() != NULL)
					{
						if (COMBO->GetCombo() >= 3)
						{
							mGroundList[y][x]->SetFrameIndexY(1);
							//홀
							if ((x + y) & 1)
							{
								if (mGroundList[y][x]->GetFrameIndexX() == 0)
									mGroundList[y][x]->SetFrameIndexX(1);
								else
									mGroundList[y][x]->SetFrameIndexX(0);
							}
							//짝
							else
							{
								if (mGroundList[y][x]->GetFrameIndexX() == 0)
									mGroundList[y][x]->SetFrameIndexX(2);
								else
									mGroundList[y][x]->SetFrameIndexX(0);
							}

						}
						else
						{
							mGroundList[y][x]->SetFrameIndexY(0);
							if (mGroundList[y][x]->GetFrameIndexX() == 0)
								mGroundList[y][x]->SetFrameIndexX(1);
							else
								mGroundList[y][x]->SetFrameIndexX(0);
						}

					}
				}
			}
		}
	}
}

void Ground::Render(HDC hdc)
{
	//배경검정색
	mBack->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);

	//바닥 타일찍기
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
	//Wall은 Wall 클래스 작업이 진행되면 제거
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

bool Ground::GetSight()
{
	return false;
}
