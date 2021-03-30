#include "pch.h"

void Hud::SetHp()
{
	//GameScene Init 혹은 최대체력 상태에서 체력칸을 늘릴때 호출,
	mMaxHp = mPlayerPtr->GetHp();
	for (int i = 0.f; i < mMaxHp / 2.f; i ++)
	{
		FrameImage temp = { IMAGEMANAGER->FindImage(L"HUDHealth"), WINSIZEX - 200.f - mHudSize * i, 50.f,  0, 0, mHudSize, mHudSize };
		mHp.push_back(temp);
	}
}

void Hud::UpdateHp()
{
	float a = mPlayerPtr->GetHp();
	int count = (int)(mMaxHp - mPlayerPtr->GetHp());
	int index = 0;
	for (int i = 0; i < count; ++i)
	{
		mHp[index].FrameX = i % 2 + 1;	//1,2
		if (mHp[index].FrameX >= 2)
		{
			index++;
			//혹시모르는 예외처리
			if (index >= mHp.size())
				break;
		}
	}
}