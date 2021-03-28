#pragma once

enum class TileLayer {
	Ground = 0,
	Wall = 1,
	Deco = 2,
	Item = 3,
	GameObject = 4,
	End
};

enum class TileType {
	Normal = 0,
	Wall = 1,
	Slow = 2,
	BreakAble = 3,
	End
};

class Tile {
private:
	TileLayer mLayer;
	TileType mType;
	class Image* mImage;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;
	int mFrameIndexX;
	int mFrameIndexY;
	int mIndexX;
	int mIndexY;
public:
	Tile(class Image* image, float x, float y, float sizeX, float sizeY,int frameIndexX, int frameIndexY, TileType tiletype = TileType::Normal);
	
	void Render(HDC hdc);
	void MoveRender(HDC hdc, float moveX, float moveY);
	void PositionRender(HDC hdc, float posX, float posY);


	Image* GetImage()const { return mImage; }
	void SetImage(Image * image) { mImage = image; }

	float GetX()const { return mX; }
	void SetX(float x) { mX = x; }

	float GetY()const { return mY; }
	void SetY(float y) { mY = y; }

	float Getwidth()const { return mSizeX; }
	void SetWidth(float w) { mSizeX = w; }

	float GetHeight()const { return mSizeY; }
	void SetHeight(float h) { mSizeY = h; }

	RECT GetRect()const { return mRect; }
	void SetRect() { mRect = RectMake(mX, mY, mSizeX, mSizeY); }

	void SetRect(float x, float y, float width, float height) { mRect = RectMake(x, y, width, height); }

	int GetFrameIndexX()const { return mFrameIndexX; }
	void SetFrameIndexX(int x) { mFrameIndexX = x; }

	int GetFrameIndexY()const { return mFrameIndexY; }
	void SetFrameIndexY(int y) { mFrameIndexY = y; }

	void SetFrame(int x, int y) { mFrameIndexX = x; mFrameIndexY = y; }

	int GetIndexX() { return mIndexX; }
	int GetIndexY() { return mIndexY; }

	TileLayer GetTileLayer()const { return mLayer; }
	void SetTileLayer(TileLayer layer) { mLayer = layer; }
	TileType GetTileType()const { return mType; }
	void SetTileType(TileType type) { mType = type; }
};

struct AlphaTile {
	Tile* Tile;
	float Alpha;
};