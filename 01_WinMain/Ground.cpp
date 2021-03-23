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
	
	mMapSizeY = mGroundList.size();
	mMapSizeX = mGroundList[0].size();

	SetMinMax();
	mOddFrame = { 0,0 };
	mEvenFrame = { 1,0 };
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
					mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));

					//������������
					if (mGroundList[y][x]->GetFrameIndexX() == 4 && mGroundList[y][x]->GetFrameIndexY() == 0)
					{
						mGroundList[y][x]->SetFrameIndexX(6);
						mGroundList[y][x]->SetFrameIndexY(0);
					}
					//shop
					else if (mGroundList[y][x]->GetFrameIndexX() == 3 && mGroundList[y][x]->GetFrameIndexY() == 0)
					{
						mGroundList[y][x]->SetFrameIndexX(7);
						mGroundList[y][x]->SetFrameIndexY(0);
					}
					else
					{
						//Ȧ���϶�
						if ((x + y) & 1)
						{
							mGroundList[y][x]->SetFrameIndexX(0);
							mGroundList[y][x]->SetFrameIndexY(0);
						}
						//¦���϶�
						else
						{
							mGroundList[y][x]->SetFrameIndexX(1);
							mGroundList[y][x]->SetFrameIndexY(0);
						}
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
		}
	}
	mGroundList.clear();
	mGroundList.shrink_to_fit();
}

void Ground::Update()
{
	SetMinMax();
	//�ϸ��� Ÿ�� �����ϱ�

	if(BEAT->NextTurn())
	{
		if (mOddFrame.x == 0)
			mOddFrame.x = 1;
		else if (mOddFrame.x == 1)
			mOddFrame.x = 0;
		if (mEvenFrame.x == 0)
			mEvenFrame.x = 1;
		else if (mEvenFrame.x == 1)
			mEvenFrame.x = 0;

		for (int y = mMinIndexY; y < mMaxIndexY; ++y)
		{
			for (int x = mMinIndexX; x < mMaxIndexX; ++x)
			{
				if (mGroundList[y][x]->GetImage() != NULL)
				{
					//����Ī�� �̹����� �ƴϸ� continue
					if (mGroundList[y][x]->GetFrameIndexX() > 5)
						continue;

					if (COMBO->GetCombo() >= 3)
					{
						mGroundList[y][x]->SetFrameIndexY(1);
						//Ȧ
						if ((x + y) & 1)
						{
								mGroundList[y][x]->SetFrameIndexX(mOddFrame.x);
						}
						//¦
						else
						{
							mGroundList[y][x]->SetFrameIndexX(mEvenFrame.x*2);
						}

					}
					else
					{
						mGroundList[y][x]->SetFrameIndexY(0);
						//Ȧ
						if ((x + y) & 1)
						{
							mGroundList[y][x]->SetFrameIndexX(mOddFrame.x);
						}
						//¦ : Ȧ�̶� �ٸ� �̹���
						else
						{
							mGroundList[y][x]->SetFrameIndexX(mEvenFrame.x);
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
	for (int y = mMinIndexY; y < mMaxIndexY; ++y)
	{
		for (int x = mMinIndexX; x < mMaxIndexX; ++x)
		{
			//�� ��ü�� �����ϸ� ��û �������� ó�� �����ϱ�
			int posx = x * TileSize;
			int posy = y * TileSize;

			if(mGroundList[y][x]->GetImage() != NULL)
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mGroundList[y][x]->GetImage(),
					posx, posy, mGroundList[y][x]->GetFrameIndexX(), mGroundList[y][x]->GetFrameIndexY(),
					mGroundList[y][x]->Getwidth(), mGroundList[y][x]->GetHeight(), 1.0f);
		}
	}
}

void Ground::SetMinMax()
{
	mMinIndexX = CameraManager::GetInstance()->GetMainCamera()->GetCameraLeft() / TileSize -1;
	if (mMinIndexX < 0)
		mMinIndexX = 0;
	mMinIndexY = CameraManager::GetInstance()->GetMainCamera()->GetCameraTop() / TileSize - 1;
	if (mMinIndexY < 0)
		mMinIndexY = 0;
	mMaxIndexX = CameraManager::GetInstance()->GetMainCamera()->GetCameraRight() / TileSize +1;
	if (mMaxIndexX > mMapSizeX)
		mMaxIndexX = mMapSizeX;
	mMaxIndexY = CameraManager::GetInstance()->GetMainCamera()->GetCameraBottom() / TileSize +1;
	if (mMaxIndexY > mMapSizeY)
		mMaxIndexY = mMapSizeY;
}

bool Ground::GetSight()
{
	return false;
}
