#include "pch.h"
#include "Beat.h"

Beat::Beat()
{
	mNowMusic = L"";
	mTiming = 0;
	//이미지, 단 이미지 파일을 추가하고 주석을 제거할 것
	//mHeartImage = IMAGEMANAGER->FindImage(L"BeatHeart");
	//mNoteImage = IMAGEMANAGER->FindImage(L"BeatNote");

	//판정 기준이 될 하트
	mHeart = RectMakeBottom(WINSIZEX/2, WINSIZEY, 40, 100);
	//반복 사용할 노트 30 x2
	for (int i = 0; i < 30; ++i)
	{
		POINT lpos = { 0, WINSIZEY - 50 };
		Note ltemp = { lpos, RectMakeCenter(0, WINSIZEY - 50,5,5), false};
		mLeftNote.push_back(ltemp);

		POINT rpos = { WINSIZEX, WINSIZEY - 50 };
		Note rtemp = { rpos, RectMakeCenter(WINSIZEX, WINSIZEY - 50,5,5), false };
		mLeftNote.push_back(rtemp);
	}
	//노트 색깔을 변경할  bool값
	mDeadLine = false;
}

Beat::~Beat()
{
}

void Beat::Init()
{
}

void Beat::Release()
{
}

void Beat::Update()
{
}

void Beat::Render()
{
}

void Beat::SetMusic(const wstring& keyname)
{

}

bool Beat::IsDecision()
{
	return false;
}

bool Beat::NextTurn()
{
	return false;
}
