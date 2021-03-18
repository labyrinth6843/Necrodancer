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

	//��Ȱ�� �۾��� ����Ÿ���� �̹��� ������ ����
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			if (mGroundList[y][x]->GetImage() != NULL)
			{
				//ä���� Ÿ���϶�
				if (mGroundList[y][x]->GetFrameIndexX() != 0 || mGroundList[y][x]->GetFrameIndexY() != 0)
				{
					//Ȧ���϶�
					if ((x + y) & 1)
					{
						mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));
						mGroundList[y][x]->SetFrameIndexX(0);
						mGroundList[y][x]->SetFrameIndexY(0);
					}
					//¦���϶�
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
	//�ϸ��� Ÿ�� �����ϱ�
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
							//Ȧ
							if ((x + y) & 1)
							{
								if (mGroundList[y][x]->GetFrameIndexX() == 0)
									mGroundList[y][x]->SetFrameIndexX(1);
								else
									mGroundList[y][x]->SetFrameIndexX(0);
							}
							//¦
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
	//��������
	mBack->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);

	//�ٴ� Ÿ�����
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			//�� ��ü�� �����ϸ� ��û �������� ó�� �����ϱ�
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
	//Wall�� Wall Ŭ���� �۾��� ����Ǹ� ����
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
