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
	Tile* mGroundList[TileCountY][TileCountX];
	Tile* mDecoList[TileCountY][TileCountX];
	Tile* mItemList[TileCountY][TileCountX];
	Tile* mObjectList[TileCountY][TileCountX];
	//
	TilePallete mPallete[10][5];

	vector<wstring>mPalleteList;
	int mCurrentPage = 0;

	TilePallete mCurrentPallete;
	Button* mSaveButton;
	Button* mLoadButton;
	Button* mClearButton;
	Button* mUndoButton;
	Button* mRedoButton;
	Button* mPlayButton;

	Button* mGroundButton;
	Button* mWallButton;
	Button* mDecoButton;
	Button* mItemButton;
	Button* mObjectButton;

	Button* mPrevButton;
	Button* mNextButton;
	map<wstring, class Button*> mButtonList;
	typedef map<wstring, class Button*> ::iterator ButtonIt;

	stack<ICommand*> mCommandList;
	stack<ICommand*> mReCommandList;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

private:
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
};