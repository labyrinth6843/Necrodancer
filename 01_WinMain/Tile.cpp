#include "pch.h"
#include "Tile.h"
#include "Image.h"

Tile::Tile(Image * image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY, TileType tiletype){
	mImage = image;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFrameIndexX = frameIndexX;
	mFrameIndexY = frameIndexY;
	mLayer = TileLayer::End;
	mType = tiletype;

	mIndexX = mX / mSizeX; 
	mIndexY = mY / mSizeY;
}

void Tile::Render(HDC hdc){
	if (mImage != nullptr)
		mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);

	//Gizmo::GetInstance()->DrawRect(hdc, mRect, Gizmo::Color::Gray);
}
void Tile::MoveRender(HDC hdc, float moveX, float moveY)
{
	if (mImage != nullptr)
		mImage->ScaleFrameRender(hdc, mRect.left + moveX, mRect.top + moveY,
			mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);
}
void Tile::PositionRender(HDC hdc, float posX, float posY)
{
	if (mImage != nullptr)
		mImage->ScaleFrameRender(hdc, posX, posY, mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);
}

void Tile::ChangeAlphaTile(vector<vector<Tile*>>& tilelist, vector<vector<AlphaTile>>& alphalist)
{
	int sizeY = tilelist.size();
	int sizeX = tilelist[0].size();

	alphalist.clear();
	alphalist.shrink_to_fit();

	for (int y = 0; y < sizeY; ++y)
	{
		vector<AlphaTile> tempX;
		for (int x = 0; x < sizeX; ++x)
		{
			tempX.push_back(AlphaTile{ nullptr,0.f });
			tempX[x].Tile = tilelist[y][x];
			if (tilelist[y][x]->GetImage() != NULL)
			{
				//盲况柳 鸥老老锭
				if (tilelist[y][x]->GetFrameIndexX() != 0 || tilelist[y][x]->GetFrameIndexY() != 0)
				{
					tempX[x].Alpha = 1.f;
				}
				//后 鸥老老锭
				else
				{
					tempX[x].Alpha = 0.f;
				}
			}
		}
		alphalist.push_back(tempX);
	}
}
