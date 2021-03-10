#pragma once
#include <queue>
class Tokenize
{
	string mStr;
	string mTempStr;
	int mPos;
	class Tile* mTile;
	//vector<vector<string>> mSdVector;
	//vector<string> mFdVector;

	queue<string>mQueue;
public:
	void tokenize(string str);
	
	void SetTileList(Tile* tile) { mTile = tile; }
};

