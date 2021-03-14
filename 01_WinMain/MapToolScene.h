#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"
#include <stack>
#include <queue>

//구조체 변수는 대문자로 시작하게 짬, 나같은경우에는
struct TilePallete{
	class Image* Image;
	int PositionX;
	int PositionY;
	int Width;
	int Height;
	RECT Rc;
	int FrameX;
	int FrameY;
	TileType Type;
	TileLayer Layer;
};

struct TileSave {
	wstring SaveImageKey;
	int SaveFrameX;
	int SaveFrameY;

	int IndexX;
	int IndexY;

	void Set(wstring imagekey, int frameX, int frameY, int indexX, int indexY)
	{
		SaveImageKey = imagekey;
		SaveFrameX = frameX;
		SaveFrameY = frameY;
		IndexX = indexX;
		IndexY = indexY;
	}
};

class ICommand{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

//{{ 개조 테스트, 단일 Re/Undo 확인 완료 ~
class IBrushTile : public ICommand {
	vector<vector<Tile*>> mTileList;//원본 레이어
	vector<TileSave> mTargetTile; //바꿀 타일들의 정보(ImageKey,FrameX,FrameY,IndexX,IndexY)

	TilePallete mExecutePalleteData;//바꿀 타일 정보
public:

	//생성자를 호출하기 이전에 TileSave에 저장한 값을 넣어서 보내기때문에 따로 저장할 필요가 없다
	IBrushTile(vector<vector<Tile*>>& LayerList, TileSave &tilesave, TilePallete executeData) {
		mTileList = LayerList;
		mTargetTile.push_back(tilesave);
		mExecutePalleteData = executeData;
	}
	IBrushTile(vector<vector<Tile*>> &LayerList,vector<TileSave> &tilesave, TilePallete executeData) {
		mTileList = LayerList;
		mTargetTile = tilesave;
		mExecutePalleteData = executeData;
	}

	void Execute() {//실행
		for (int i = 0; i < mTargetTile.size(); ++i)
		{
			int indexX = mTargetTile[i].IndexX;
			int indexY = mTargetTile[i].IndexY;

			mTileList[indexY][indexX]->SetImage(ImageManager::GetInstance()->FindImage(mExecutePalleteData.Image->GetKeyName()));
			mTileList[indexY][indexX]->SetFrameIndexX(mExecutePalleteData.FrameX);
			mTileList[indexY][indexX]->SetFrameIndexY(mExecutePalleteData.FrameY);
		}
	}
	void Undo()override {//실행취소
		for (int i = 0; i < mTargetTile.size(); ++i)
		{
			int indexX = mTargetTile[i].IndexX;
			int indexY = mTargetTile[i].IndexY;

			mTileList[indexY][indexX]->SetImage(ImageManager::GetInstance()->FindImage(mTargetTile[i].SaveImageKey));
			mTileList[indexY][indexX]->SetFrameIndexX(mTargetTile[i].SaveFrameX);
			mTileList[indexY][indexX]->SetFrameIndexY(mTargetTile[i].SaveFrameY);
		}
	}
	void Redo()override {//실행취소 번복
		for (int i = 0; i < mTargetTile.size(); ++i)
		{
			int indexX = mTargetTile[i].IndexX;
			int indexY = mTargetTile[i].IndexY;

			mTileList[indexY][indexX]->SetImage(ImageManager::GetInstance()->FindImage(mExecutePalleteData.Image->GetKeyName()));
			mTileList[indexY][indexX]->SetFrameIndexX(mExecutePalleteData.FrameX);
			mTileList[indexY][indexX]->SetFrameIndexY(mExecutePalleteData.FrameY);
		}
	}
};
// ~}}

class Button;
class Tile;
class MapToolScene : public Scene{
	Image* tileImage;

	vector<vector<Tile*>> mGroundList;
	vector<vector<Tile*>> mDecoList;
	vector<vector<Tile*>> mItemList;
	vector<vector<Tile*>> mObjectList;

	int mCurrentPage = 0;

	TilePallete mPallete[10][5];
	vector<wstring>mPalleteList;
	TilePallete mCurrentPallete;

	map<wstring, class Button*> mButtonList;
	typedef map<wstring, class Button*> ::iterator ButtonIt;

	stack<ICommand*> mCommandList;
	stack<ICommand*> mReCommandList;

	bool mShowGrid;

	int mMinIndexX;
	int mMinIndexY;
	int mMaxSizeX;
	int mMaxSizeY;

	int mMoveX;
	int mMoveY;

	int mIsInput;	//0 : false, 1 : x, 2 : y
	string mInputX;
	string mInputY;

	bool mSelectMod;
	bool mDragMod;
	bool mSelectRectShow;
	RECT mSelectRect;
	vector<POINT> mSelectIndex;
	bool mFillMod;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	LRESULT Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	void SetSize();

	void Save();
	void Load();
	void Clear();
	void Undo();
	void Redo();
	void Fill();
	void Paint();

	void FloodFill(vector<vector<Tile*>>& tileList, int indexX, int indexY);


	void Play();
	void PushCommand(ICommand* command);
	
	void GroundPallete();
	void WallPallete();
	void DecoPallete();
	void ItemPallete();
	void ObjectPallete();

	void PrevPallete();
	void NextPallete();

	void CanvasMove();
	void ButtonMove(int key, int move);
};