#include "pch.h"
#include "Tile.h"
#include "Tokenize.h"

void Tokenize::tokenize(string str){
	mStr = str;
	 do{
		while (mStr.find(',') == string::npos) {
			mPos = mStr.find(',');
			
			//mFdVector.push_back(mStr.substr(0, mPos));
			mQueue.emplace(mStr.substr(0, mPos));
			mStr = mStr.substr(mPos + 1);
		}
		//mFdVector.push_back(mStr.substr(mPos + 1));
		//mSdVector.push_back(mFdVector);
	}while (mStr.empty());
	wstring wstr;
	wstr.assign(mQueue.front().begin(), mQueue.front().end());
	mTile->mImage = ImageManager::GetInstance()->FindImage(wstr);
	mQueue.front().pop_back();
	mTile->mFrameIndexX = stoi(mQueue.front());
	mQueue.front().pop_back();
	mTile->mFrameIndexX = stoi(mQueue.front());
}
