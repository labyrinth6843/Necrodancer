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
