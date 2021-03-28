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
	vector<vector<Tile*>> groundList;
	mBack = IMAGEMANAGER->FindImage(L"Black");
	FileManager::LoadMap(L"Test00", groundList, TileSize);
	mMapSizeY = groundList.size();
	mMapSizeX = groundList[0].size();

	SetMinMax();
	mOddFrame = { 0,0 };
	mEvenFrame = { 1,0 };
	//원활한 작업을 위해타일의 이미지 포인터 변경
	for (int y = 0; y < mMapSizeY; ++y)
	{
		vector<AlphaTile> tempX;
		for (int x = 0; x < mMapSizeX; ++x)
		{
			tempX.push_back(AlphaTile{ nullptr,0.f });
			tempX[x].Tile = groundList[y][x];
			if (groundList[y][x]->GetImage() != NULL)
			{
				//채워진 타일일때
				if (groundList[y][x]->GetFrameIndexX() != 0 || groundList[y][x]->GetFrameIndexY() != 0)
				{
					tempX[x].Tile->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));

					//다음스테이지
					if (groundList[y][x]->GetFrameIndexX() == 4 && groundList[y][x]->GetFrameIndexY() == 0)
					{
						tempX[x].Tile->SetFrameIndexX(6);
						tempX[x].Tile->SetFrameIndexY(0);
					}
					//shop
					else if (groundList[y][x]->GetFrameIndexX() == 3 && groundList[y][x]->GetFrameIndexY() == 0)
					{
						tempX[x].Tile->SetFrameIndexX(7);
						tempX[x].Tile->SetFrameIndexY(0);
					}
					else
					{
						//홀수일때
						if ((x + y) & 1)
						{
							tempX[x].Tile->SetFrameIndexX(0);
							tempX[x].Tile->SetFrameIndexY(0);
						}
						//짝수일때
						else
						{
							tempX[x].Tile->SetFrameIndexX(1);
							tempX[x].Tile->SetFrameIndexY(0);
						}
					}
					tempX[x].Alpha = 1.f;
				}
				//빈 타일일때
				else
				{
					tempX[x].Tile->SetImage(IMAGEMANAGER->GetInstance()->FindImage(L"GroundTile"));
					tempX[x].Tile->SetFrameIndexX(7);
					tempX[x].Tile->SetFrameIndexY(1);
					tempX[x].Alpha = 0.f;
				}
			}
		}
		mGroundList.push_back(tempX);
	}
}

void Ground::Release()
{
	for (int y = 0; y < mMapSizeY; ++y)
	{
		for (int x = 0; x < mMapSizeX; ++x)
		{
			SafeDelete(mGroundList[y][x].Tile);
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
				if (mGroundList[y][x].Tile->GetImage() != NULL)
				{
					//스위칭될 이미지가 아니면 continue
					if (mGroundList[y][x].Tile->GetFrameIndexX() > 5)
						continue;

					if (COMBO->GetCombo() >= 3)
					{
						mGroundList[y][x].Tile->SetFrameIndexY(1);
						//홀
						if ((x + y) & 1)
						{
								mGroundList[y][x].Tile->SetFrameIndexX(mOddFrame.x);
						}
						//짝
						else
						{
							mGroundList[y][x].Tile->SetFrameIndexX(mEvenFrame.x*2);
						}

					}
					else
					{
						mGroundList[y][x].Tile->SetFrameIndexY(0);
						//홀
						if ((x + y) & 1)
						{
							mGroundList[y][x].Tile->SetFrameIndexX(mOddFrame.x);
						}
						//짝 : 홀이랑 다른 이미지
						else
						{
							mGroundList[y][x].Tile->SetFrameIndexX(mEvenFrame.x);
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

			if (mGroundList[y][x].Tile->GetImage() != NULL)
			{
				if (mGroundList[y][x].Alpha > 0.f)
				{
					CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mGroundList[y][x].Tile->GetImage(),
						posx, posy, mGroundList[y][x].Tile->GetFrameIndexX(), mGroundList[y][x].Tile->GetFrameIndexY(),
						mGroundList[y][x].Tile->Getwidth(), mGroundList[y][x].Tile->GetHeight(), mGroundList[y][x].Alpha);
				}
			}
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

	if (mGroundList[indexY][indexX].Tile->GetFrameIndexX() != 7 || mGroundList[indexY][indexX].Tile->GetFrameIndexY() != 1)
		return true;
	return false;
}
