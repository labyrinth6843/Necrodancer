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
					mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));

					//다음스테이지
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
						//홀수일때
						if ((x + y) & 1)
						{
							mGroundList[y][x]->SetFrameIndexX(0);
							mGroundList[y][x]->SetFrameIndexY(0);
						}
						//짝수일때
						else
						{
							mGroundList[y][x]->SetFrameIndexX(1);
							mGroundList[y][x]->SetFrameIndexY(0);
						}
					}
				}
				//빈 타일일때
				else
				{
					mGroundList[y][x]->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));
					mGroundList[y][x]->SetFrameIndexX(7);
					mGroundList[y][x]->SetFrameIndexY(1);
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
	//턴마다 타일 변경하기

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
					//스위칭될 이미지가 아니면 continue
					if (mGroundList[y][x]->GetFrameIndexX() > 5)
						continue;

					if (COMBO->GetCombo() >= 3)
					{
						mGroundList[y][x]->SetFrameIndexY(1);
						//홀
						if ((x + y) & 1)
						{
								mGroundList[y][x]->SetFrameIndexX(mOddFrame.x);
						}
						//짝
						else
						{
							mGroundList[y][x]->SetFrameIndexX(mEvenFrame.x*2);
						}

					}
					else
					{
						mGroundList[y][x]->SetFrameIndexY(0);
						//홀
						if ((x + y) & 1)
						{
							mGroundList[y][x]->SetFrameIndexX(mOddFrame.x);
						}
						//짝 : 홀이랑 다른 이미지
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
	//배경검정색
	mBack->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);

	//바닥 타일찍기
	for (int y = mMinIndexY; y < mMaxIndexY; ++y)
	{
		for (int x = mMinIndexX; x < mMaxIndexX; ++x)
		{
			//맵 전체를 랜더하면 엄청 느려지니 처리 생각하기
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
	mMinIndexX = CameraManager::GetInstance()->GetMainCamera()->GetCameraLeft() / TileSize -2;
	if (mMinIndexX < 0)
		mMinIndexX = 0;
	mMinIndexY = CameraManager::GetInstance()->GetMainCamera()->GetCameraTop() / TileSize - 2;
	if (mMinIndexY < 0)
		mMinIndexY = 0;
	mMaxIndexX = CameraManager::GetInstance()->GetMainCamera()->GetCameraRight() / TileSize + 2;
	if (mMaxIndexX > mMapSizeX)
		mMaxIndexX = mMapSizeX;
	mMaxIndexY = CameraManager::GetInstance()->GetMainCamera()->GetCameraBottom() / TileSize +2;
	if (mMaxIndexY > mMapSizeY)
		mMaxIndexY = mMapSizeY;
}

bool Ground::GetSight()
{
	return false;
}

bool Ground::IsMove(int indexX, int indexY)
{
	//장외처리
	if(indexX < 0 || indexX >= mMapSizeX || indexY < 0 || indexY >= mMapSizeY)
		return false;

	if (mGroundList[indexY][indexX]->GetFrameIndexX() != 7 || mGroundList[indexY][indexX]->GetFrameIndexY() != 1)
		return true;
	return false;
}
