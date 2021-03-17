#include "pch.h"
#include "Beat.h"

Beat::Beat()
{
	mDefaultY = WINSIZEY - 70;

	mNowMusic = L"";
	mTiming = 0.f;
	//이미지, 단 이미지 파일을 추가하고 주석을 제거할 것
	mHeartImage.Image = IMAGEMANAGER->FindImage(L"BeatHeart");
	mHeartImage.FrameX = 0;
	mHeartImage.FrameY = 0;

	//판정 기준이 될 하트Rect
	mHeart = RectMakeCenter(WINSIZEX/2, mDefaultY, 150, 100);

	//반복 사용할 노트 30 x2
	for (int i = 0; i < 30; ++i)
	{
		POINT lpos = { 0, mDefaultY };
		Note ltemp = { IMAGEMANAGER->FindImage(L"BeatBlue"), lpos, RectMakeCenter(0, mDefaultY, 5,5), NoteState::Unactive, 1.f};
		mLeftNote.push_back(ltemp);

		POINT rpos = { WINSIZEX, mDefaultY };
		Note rtemp = { IMAGEMANAGER->FindImage(L"BeatBlue"), rpos, RectMakeCenter(WINSIZEX, mDefaultY, 5,5),  NoteState::Unactive, 1.f };
		mRightNote.push_back(rtemp);
	}
	//노트 색깔을 변경할 기준값
	mDeadLine = INT_MAX;
	//보스전인지 판단
	mIsBoss = false;
	//몬스터 행동 조건
	mTurn = false;
	//노래종료
	mMusicEnd = false;
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
	mIsBoss = false;
	QueueClear(mRunQueue);
	QueueClear(mSaveQueue);
	for (int i = 0; i < 30; ++i)
	{
		mLeftNote[i] = { IMAGEMANAGER->FindImage(L"BeatBlue") ,{ 0, mDefaultY } , RectMakeCenter(0, mDefaultY,5,5), NoteState::Unactive , 1.f};
		mRightNote[i] = { IMAGEMANAGER->FindImage(L"BeatBlue"), { WINSIZEX,mDefaultY }, RectMakeCenter(WINSIZEX, mDefaultY,5,5),  NoteState::Unactive, 1.f };
	}
}

void Beat::Update()
{
	if (Input::GetInstance()->GetKeyDown('N'))//노트 절반 날림 + 
	{
		for (int i = 0; i < mRunQueue.size() / 2; ++i)
		{
			mRunQueue.pop();
		}
		SetTiming();
		SoundPlayer::GetInstance()->SetPosition(mNowMusic,mTiming);
	}
	if (Input::GetInstance()->GetKeyDown('B'))
		IsDecision();
	//기본적으로 매 프레임마다 턴조건 초기화
	mTurn = false;
	//현재 재생중인 음악의 Position이 mTiming과 같으면 노트를 활성화 한다
	float position = SoundPlayer::GetInstance()->GetPosition(mNowMusic);
	cout << position << endl;
	if (mTiming <= position && !mMusicEnd)
	{
		SetNote();
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
		//노트 이동
		if (mLeftNote[i].State == NoteState::Active)
		{
			mLeftNote[i].Pos.x += 300 * Time::GetInstance()->DeltaTime();	//속도는 임의로 설정했기때문에 조정 필요
			mLeftNote[i].Rc = RectMakeCenter(mLeftNote[i].Pos.x, mLeftNote[i].Pos.y, 5, 5);
		}
		else if (mLeftNote[i].State == NoteState::Miss)
		{
			mLeftNote[i].Pos.y -= 100 * Time::GetInstance()->DeltaTime();
			mLeftNote[i].Rc = RectMakeCenter(mLeftNote[i].Pos.x, mLeftNote[i].Pos.y, 5, 5);
			mLeftNote[i].Alpha -= 2.f* Time::GetInstance()->DeltaTime();
		}

		if (mRightNote[i].State == NoteState::Active)
		{
			mRightNote[i].Pos.x -= 300 * Time::GetInstance()->DeltaTime();
			mRightNote[i].Rc = RectMakeCenter(mRightNote[i].Pos.x, mLeftNote[i].Pos.y, 5, 5);
		}
		else if (mRightNote[i].State == NoteState::Miss)
		{
			mRightNote[i].Pos.y -= 100 * Time::GetInstance()->DeltaTime();
			mRightNote[i].Rc = RectMakeCenter(mRightNote[i].Pos.x, mRightNote[i].Pos.y, 5, 5);
			mRightNote[i].Alpha -= 2.f* Time::GetInstance()->DeltaTime();
		}

		//Left와 Right끼리 충돌하면  Miss 처리
		RECT temp;
		if (mLeftNote[i].State == NoteState::Active && mRightNote[i].State == NoteState::Active &&
			(mLeftNote[i].Pos.x >= mRightNote[i].Pos.x))
		{
			MissNote();
		}
		if (mLeftNote[i].Alpha <= 0 && mRightNote[i].Alpha <= 0)
		{
			//플레이어가 커맨드를 입력하지 않고 지나가면 몬스터의 턴 진행
			mTurn = true;
			mLeftNote[i].State = NoteState::Unactive;
			mRightNote[i].State = NoteState::Unactive;
		}	
	}
	NoteReset();

	//심장의 프레임을 변경한다
	if (mHeartImage.FrameX == 0)
	{
		mHeartImage.FrameCount += 15 * Time::GetInstance()->DeltaTime();
		if (mHeartImage.FrameCount > 5.f)
		{
			mHeartImage.FrameX = 1;
			mHeartImage.FrameCount = 0.f;
		}
	}else if (mHeartImage.FrameX == 1)
	{
		mHeartImage.FrameCount += 15 * Time::GetInstance()->DeltaTime();
		if (mHeartImage.FrameCount > 2.f)
		{
			mHeartImage.FrameX = 0;
			mHeartImage.FrameCount = 0.f;
		}
	}
	
}

void Beat::Render(HDC hdc)
{
	//노트
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State != NoteState::Unactive)
		{
			mLeftNote[i].Image->AlphaScaleRender(hdc, mLeftNote[i].Pos.x - 12, mLeftNote[i].Pos.y - 50, 15, 100, mLeftNote[i].Alpha);
			//Gizmo::GetInstance()->DrawRect(hdc, mLeftNote[i].Rc, Gizmo::Color::Green);
		}
		if (mRightNote[i].State != NoteState::Unactive)
		{
			mRightNote[i].Image->AlphaScaleRender(hdc, mRightNote[i].Pos.x - 12, mRightNote[i].Pos.y - 50, 15, 100, mRightNote[i].Alpha);
			//Gizmo::GetInstance()->DrawRect(hdc, mRightNote[i].Rc, Gizmo::Color::Green);
		}
	}
	//심장
	Gizmo::GetInstance()->DrawRect(hdc, mHeart, Gizmo::Color::Green);
	mHeartImage.Image->ScaleFrameRender(hdc, WINSIZEX/2 - 60, WINSIZEY - 160,
		mHeartImage.FrameX, mHeartImage.FrameY, 120, 150);

	//테스팅
	//Gizmo::GetInstance()->DrawRect(hdc, RectMake(0, 0, WINSIZEX / 2, WINSIZEY), Gizmo::Color::Red);
	float t = SoundPlayer::GetInstance()->GetPosition(mNowMusic);
	wstring test = to_wstring(t);
	TextOut(hdc,10,10,test.c_str(),test.length());
}

void Beat::SetMusic(const wstring& keyname, const wstring& beatfilename)
{
	//스테이지(필드) 진입시 해당 함수 호출
	mNowMusic = keyname;
	mDeadLine = SoundPlayer::GetInstance()->GetFullPosition(keyname) / 7 * 3;
	FileManager::GetInstance()->LoadBeat(beatfilename,mSaveQueue);
	mRunQueue = mSaveQueue;

	mTiming = mRunQueue.front();
	mRunQueue.pop();
}

bool Beat::IsDecision()
{
	if (PtInRect(&mHeart, mLeftNote[0].Pos))
	{
		//커맨드 입력에 성공했을때 몬스터를 잡는다면 콤보가 증가함 -> 이 작업은 콤보 시스템에서 처리

		NoteSuccess();
		return true;
	}
	//miss
	//콤보시스템을 호출하여 콤보 감소 나중에 추가할 것
	MissNote();
	return false;
}

bool Beat::NextTurn()
{
	//Left와 Right가 만나거나 플레이어가 미스가 아닌 커맨드를 입력했을때 true반환
	return mTurn;
}

void Beat::SetTiming()
{
	if (mRunQueue.empty())
	{
		mMusicEnd = true;
		return;
	}

	mTiming = mRunQueue.front();
	mRunQueue.pop();
}

void Beat::MissNote()
{
	//활성화된 노트중 가장 심장에 가까운 노트를 찾아 Miss상태로 만든다
	for (int i = 0; i < mLeftNote.size(); ++i)
	{
		if (mLeftNote[i].State == NoteState::Active)
		{
			mLeftNote[i].State = NoteState::Miss;
			break;
		}
	}
	for (int i = 0; i < mRightNote.size(); ++i)
	{
		if (mRightNote[i].State == NoteState::Active)
		{
			mRightNote[i].State = NoteState::Miss;
			break;
		}
	}
}

void Beat::SetNote()
{
	//비활성화된 노트 중 가장 앞에있는 노트를 찾아 활성화
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State == NoteState::Unactive)
		{
			mLeftNote[i].State = NoteState::Active;
			//음악의 재생시간이 mDeadLine을 넘어가면 노트 이미지를 변경한다
			if (mNowMusic != L"")
			{
				if (mDeadLine <= SoundPlayer::GetInstance()->GetPosition(mNowMusic))
				{
					//이미지 삽입 후 주석 제거
					mLeftNote[i].Image = IMAGEMANAGER->FindImage(L"BeatRed");
				}
			}
			break;
		}
	}
	for (int i = 0; i < 30; ++i)
	{
		if (mRightNote[i].State == NoteState::Unactive)
		{
			mRightNote[i].State = NoteState::Active;
			if (mNowMusic != L"")
			{
				if (mDeadLine <= SoundPlayer::GetInstance()->GetPosition(mNowMusic))
				{
					//이미지 삽입 후 주석 제거
					mRightNote[i].Image = IMAGEMANAGER->FindImage(L"BeatRed");
				}
			}
			break;
		}
	}
}
void Beat::NoteSuccess()
{
	for (int i = 0; i < mLeftNote.size(); ++i)
	{
		if (mLeftNote[i].State == NoteState::Active)
		{
			mLeftNote[i].State = NoteState::Unactive;
			break;
		}
	}
	for (int i = 0; i < mRightNote.size(); ++i)
	{
		if (mRightNote[i].State == NoteState::Active)
		{
			mRightNote[i].State = NoteState::Unactive;
			break;
		}
	}
}
void Beat::NoteReset()
{
	//가장 먼저 활성화 된 노트를 찾아 벡터에서 제거 한 후 다시 맨 뒤에 삽입한다 -> 속도가 걱정되면 나중에 우선순위큐를 알아보고 수정할 것
	for (int i = 0; i < mLeftNote.size(); ++i)
	{
		if (mLeftNote[i].State ==  NoteState::Unactive)
		{
			if (mLeftNote[i].Pos.x != 0)
			{
				Note temp = mLeftNote[i];
				temp.Pos = { 0, mDefaultY };
				temp.Rc = RectMakeCenter(0, mDefaultY, 5, 5);
				temp.State = NoteState::Unactive;
				temp.Alpha = 1.f;
				mLeftNote.erase(mLeftNote.begin()+i);
				mLeftNote.push_back(temp);
				break;
			}
		}
	}
	for (int i = 0; i < mRightNote.size(); ++i)
	{
		if (mRightNote[i].State == NoteState::Unactive)
		{
			if (mRightNote[i].Pos.x != WINSIZEX)
			{
				Note temp = mRightNote[i];
				temp.Pos = { WINSIZEX, mDefaultY };
				temp.Rc = RectMakeCenter(WINSIZEX, mDefaultY, 5, 5);
				temp.State = NoteState::Unactive;
				temp.Alpha = 1.f;
				mRightNote.erase(mRightNote.begin()+i);
				mRightNote.push_back(temp);
				break;
			}
		}
	}
}
