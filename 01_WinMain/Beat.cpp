#include "pch.h"
#include "Beat.h"

Beat::Beat()
{
	mNowMusic = L"";
	mTiming = 0;
	//이미지, 단 이미지 파일을 추가하고 주석을 제거할 것
	//mHeartImage.Image = IMAGEMANAGER->FindImage(L"BeatHeart");
	//mHeartImage.FrameX = 0;
	//mHeartImage.FrameY = 0;
	//mNoteImage = IMAGEMANAGER->FindImage(L"BeatNote");

	//판정 기준이 될 하트Rect
	mHeart = RectMakeBottom(WINSIZEX/2, WINSIZEY, 40, 100);

	//반복 사용할 노트 30 x2
	for (int i = 0; i < 30; ++i)
	{
		POINT lpos = { 0, WINSIZEY - 50 };
		Note ltemp = { lpos, RectMakeCenter(0, WINSIZEY - 50,5,5), NoteState::Unactive};
		mLeftNote.push_back(ltemp);

		POINT rpos = { WINSIZEX, WINSIZEY - 50 };
		Note rtemp = { rpos, RectMakeCenter(WINSIZEX, WINSIZEY - 50,5,5),  NoteState::Unactive };
		mRightNote.push_back(rtemp);
	}
	//노트 색깔을 변경할 기준값
	mDeadLine = INT_MAX;
	//보스전인지 판단
	mIsBoss = false;
}

Beat::~Beat()
{

}

void Beat::Init()
{
}

void Beat::Release()
{
	mNowMusic = L"";
	mDeadLine = INT_MAX;
	QueueClear(mRunQueue);
	QueueClear(mSaveQueue);
}

void Beat::Update()
{
	//현재 재생중인 음악의 Position이 mTiming과 같으면 노트를 활성화 한다
	if (mTiming == SoundPlayer::GetInstance()->GetPosition(mNowMusic))
	{
		SetNote();
		//mRunQueue가 비어있지 않다면 다음 Timimg 세팅
		if(!mRunQueue.empty())
			SetTiming();
	}
	//보스라면 루프시키기 위해 mRunQueue가 비어있을때 mSaveQueue로 덮어씌운다
	if (mIsBoss && mRunQueue.empty())
	{
		mRunQueue = mSaveQueue;
	}

	//활성화된 노트만 중앙으로 이동시킨다
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State == NoteState::Active)
		{
			mLeftNote[i].Pos.x += 500 * Time::GetInstance()->DeltaTime();	//속도는 임의로 설정했기때문에 조정 필요
			mLeftNote[i].Rc = RectMakeCenter(mLeftNote[i].Pos.x, WINSIZEY - 50, 5, 5);
		}
		if (mRightNote[i].State == NoteState::Active)
		{
			mRightNote[i].Pos.x -= 500 * Time::GetInstance()->DeltaTime();
			mRightNote[i].Rc = RectMakeCenter(mRightNote[i].Pos.x, WINSIZEY - 50, 5, 5);
		}
		
		//Left와 Right끼리 충돌하면  Miss
		RECT temp;
		if (IntersectRect(&temp, &mLeftNote[i].Rc, &mRightNote[i].Rc))
			NoteReset();//어차피 맨 앞의 노트의 인덱스는 무조건 0이다
	}

	//음악의 재생시간이 mDeadLine을 넘어가면 노트 이미지를 변경한다
	if (mNowMusic != L"")
	{
		if (mDeadLine <= SoundPlayer::GetInstance()->GetPosition(mNowMusic))
		{
			//이미지 삽입 후 주석 제거
			//mNoteImage = IMAGEMANAGER->FindImage(L"빨간노트이미지이름");
		}
	}

	//심장의 프레임을 변경한다
	//심장 이미지 삽입 후 주석 제거
	/*
	if (mHeartImage.FrameX == 0)
	{
		mHeartImage.FrameCount += Time::GetInstance()->DeltaTime();
		if (mHeartImage.FrameCount > 5.f)
		{
			mHeartImage.FrameX = 1;
			mHeartImage.FrameCount = 0.f;
		}
	}else if (mHeartImage.FrameX == 1)
	{
		mHeartImage.FrameCount += Time::GetInstance()->DeltaTime();
		if (mHeartImage.FrameCount > 2.f)
		{
			mHeartImage.FrameX = 0;
			mHeartImage.FrameCount = 0.f;
		}
	}
	*/
}

void Beat::Render(HDC hdc)
{
	//노트
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State == NoteState::Active)
			mNoteImage->ScaleRender(hdc, mLeftNote[i].Pos.x - 12, mLeftNote[i].Pos.y - 50, 25, 100);
		if(mRightNote[i].State == NoteState::Active)
			mNoteImage->ScaleRender(hdc, mRightNote[i].Pos.x - 12, mRightNote[i].Pos.y - 50, 25, 100);
	}
	//심장
	mHeartImage.Image->ScaleFrameRender(hdc,WINSIZEX - mHeartImage.Image->GetFrameWidth(), WINSIZEY - 100,
		82, 100, mHeartImage.FrameX, mHeartImage.FrameY);
}

void Beat::SetMusic(const wstring& keyname, const wstring& beatfilename)
{
	//스테이지(필드) 진입시 해당 함수 호출
	mNowMusic = keyname;
	mDeadLine = SoundPlayer::GetInstance()->GetFullPosition(keyname) / 7 * 3;
	FileManager::GetInstance()->LoadBeat(beatfilename,mSaveQueue);
	mRunQueue = mSaveQueue;

}

bool Beat::IsDecision()
{
	if (PtInRect(&mHeart, mLeftNote[0].Pos))
	{
		//커맨드 입력에 성공했을때 몬스터를 잡는다면 콤보가 증가함 -> 이 작업은 콤보 시스템에서 처리
		NoteReset();
		return true;
	}
	//miss
	NoteReset();//임시로 해둔 것, miss시 노트 처리 추가할 것
	return false;
}

bool Beat::NextTurn()
{
	return false;
}

void Beat::SetTiming()
{
	mTiming = mRunQueue.front();
	mRunQueue.pop();
}

void Beat::SetNote()
{
	//비활성화된 노트 중 가장 앞에있는 노트를 찾아 활성화
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State == NoteState::Unactive)
		{
			mLeftNote[i].State == NoteState::Active;
		}

		if (mRightNote[i].State == NoteState::Unactive)
		{
			mRightNote[i].State == NoteState::Active;
		}
	}
}

void Beat::NoteReset()
{
	//가장 먼저 활성화 된 노트를 찾아 벡터에서 제거 한 후 다시 맨 뒤에 삽입한다 -> 속도가 걱정되면 나중에 우선순위큐를 알아보고 수정할 것
	if (mLeftNote[0].State ==  NoteState::Active)
	{
		Note temp = mLeftNote[0];
		temp.Pos = { 0, WINSIZEY - 50 };
		temp.Rc = RectMakeCenter(0, WINSIZEY - 50, 5, 5);
		temp.State = NoteState::Unactive;
		mLeftNote.erase(mLeftNote.begin());
		mLeftNote.push_back(temp);
	}

	if (mRightNote[0].State == NoteState::Active)
	{
		Note temp = mRightNote[0];
		temp.Pos = { 0, WINSIZEY - 50 };
		temp.Rc = RectMakeCenter(0, WINSIZEY - 50, 5, 5);
		temp.State = NoteState::Unactive;
		mRightNote.erase(mLeftNote.begin());
		mRightNote.push_back(temp);
	}
}
