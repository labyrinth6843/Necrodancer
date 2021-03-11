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

class ICommand{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

class IBrushTile : public ICommand{
	Tile* mTargetTile;

	wstring mSaveImageKey;
	int mSaveFrameX;
	int mSaveFrameY;

	TilePallete mExecutePalleteData;
public:
	IBrushTile(Tile* tile ,TilePallete executeData)	{
		mTargetTile = tile;
		mExecutePalleteData = executeData;

		if(tile->GetImage() != nullptr)
			mSaveImageKey = tile->GetImage()->GetKeyName();
		mSaveFrameX = tile->GetFrameIndexX();
		mSaveFrameY = tile->GetFrameIndexY();
	}

	void Execute(){
		mTargetTile->SetImage(ImageManager::GetInstance()->FindImage(mExecutePalleteData.Image->GetKeyName()));
		mTargetTile->SetFrameIndexX(mExecutePalleteData.FrameX);
		mTargetTile->SetFrameIndexY(mExecutePalleteData.FrameY);
	}
	void Undo()override	{
		mTargetTile->SetImage(ImageManager::GetInstance()->FindImage(mSaveImageKey));
		mTargetTile->SetFrameIndexX(mSaveFrameX);
		mTargetTile->SetFrameIndexY(mSaveFrameY);
	}
	void Redo()override {
		mTargetTile->SetImage(ImageManager::GetInstance()->FindImage(mSaveImageKey));
		mTargetTile->SetFrameIndexX(mExecutePalleteData.FrameX);
		mTargetTile->SetFrameIndexY(mExecutePalleteData.FrameY);
	}
};

class IRectTile :public ICommand {
	void Execute(){}
	void Undo()override {

	}
	void Redo()override {

	}
};

class IPaintTile :public ICommand {
	void Execute() {}
	void Undo()override {

	}
	void Redo()override {

	}
};

class ISelectTile :public ICommand {
	void Execute() {}
	void Undo()override {

	}
	void Redo()override {

	}
};

class Button;
class Tile;
class MapToolScene : public Scene{
	Image* tileImage;
	//
	/*	
	Tile* mGroundList[TileCountY][TileCountX];
	Tile* mDecoList[TileCountY][TileCountX];
	Tile* mItemList[TileCountY][TileCountX];
	Tile* mObjectList[TileCountY][TileCountX];
	*/
	//
	//타일 벡터화 -> 이부분 주석 해제하기전에 Init개조 필요
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
};