#include "pch.h"
#include "Beat.h"

Beat::Beat()
{
	mDefaultY = WINSIZEY - 70.f;

	mNowMusic = L"";
	mTiming = 0;
	mArrive = 0;
	//이미지, 단 이미지 파일을 추가하고 주석을 제거할 것
	mHeartImage.Image = IMAGEMANAGER->FindImage(L"BeatHeart");
	mHeartImage.FrameX = 0;
	mHeartImage.FrameY = 0;

	//판정 기준이 될 하트Rect
	mHeartImage = { RectMakeCenter(WINSIZEX / 2, mDefaultY, 180, 100) , IMAGEMANAGER->FindImage(L"BeatHeart") , 0, 0, 0.f};

	//반복 사용할 노트 30 x2
	for (int i = 0; i < 30; ++i)
	{
		Note ltemp = { IMAGEMANAGER->FindImage(L"BeatBlue"), 0.f,mDefaultY , RectMakeCenter(0, mDefaultY, 5,5), NoteState::Unactive, 1.f};
		mLeftNote.push_back(ltemp);

		Note rtemp = { IMAGEMANAGER->FindImage(L"BeatBlue"), WINSIZEX, mDefaultY, RectMakeCenter(WINSIZEX, mDefaultY, 5,5),  NoteState::Unactive, 1.f };
		mRightNote.push_back(rtemp);

		FrameImage temp = { RectMakeCenter(WINSIZEX / 2, mDefaultY - 50, 60, 10), IMAGEMANAGER->FindImage(L"MissText"), 0, 0, 0.f};
		mMiss.push_back(temp);

	}
	//노트 색깔을 변경할 기준값
	mDeadLine = INT_MAX;
	//루프할지
	mIsLoop = false;
	//몬스터 행동 조건
	mTurn = false;
	//노래종료
	mMusicEnd = false;
	mNotCall = true;

	mFrontNote = 0;
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
	mFreeMode = false;
	mIsLoop = false;
	QueueClear(mRunQueue);
	QueueClear(mSaveQueue);
	for (int i = 0; i < 30; ++i)
	{
		mLeftNote[i] = { IMAGEMANAGER->FindImage(L"BeatBlue") , 0, mDefaultY , RectMakeCenter(0, mDefaultY,5,5), NoteState::Unactive , 1.f};
		mRightNote[i] = { IMAGEMANAGER->FindImage(L"BeatBlue"), WINSIZEX, mDefaultY, RectMakeCenter(WINSIZEX, mDefaultY,5,5),  NoteState::Unactive, 1.f };
		mMiss[i] = { RectMakeCenter(WINSIZEX / 2, mDefaultY - 50, 60, 10), IMAGEMANAGER->FindImage(L"MissText"), 0, 0, 0.f };
	}
	mFrontNote = 0;
}

void Beat::Update()
{
	//치트키
	if (Input::GetInstance()->GetKeyDown('L'))
		mFreeMode = !mFreeMode;
	//기본적으로 매 프레임마다 턴조건 초기화
	if(mNotCall)
		mTurn = false;

	//현재 재생중인 음악의 Position이 mTiming과 같으면 노트를 활성화 한다
	unsigned int position = SoundPlayer::GetInstance()->GetPosition(mNowMusic);
	if (mTiming <= position && !mMusicEnd)
	{
		SetNote();
		SetTiming();
	}
	//보스라면 루프시키기 위해 mRunQueue가 비어있을때 mSaveQueue로 덮어씌운다
	if (mIsLoop && mRunQueue.empty())
	{
		ResetMusic();
		mMusicEnd = false;
	}

	//활성화된 노트만 중앙으로 이동시킨다
	for (int i = 0; i < 30; ++i)
	{
		//노트 이동

		//중앙에서 만나면 서서히 흐려진다
		RECT temp;
		if (mLeftNote[i].State == NoteState::Active && mRightNote[i].State == NoteState::Active &&
			(mLeftNote[i].X >= mRightNote[i].X))
		{
			mLeftNote[i].Alpha -= 2.f* Time::GetInstance()->DeltaTime();
			mRightNote[i].Alpha -= 2.f* Time::GetInstance()->DeltaTime();
		}
		else
		{
			if (mLeftNote[i].State == NoteState::Active)
			{
				mLeftNote[i].X += mLeftNote[i].Speed * Time::GetInstance()->DeltaTime();
				mLeftNote[i].Rc = RectMakeCenter(mLeftNote[i].X, mLeftNote[i].Y, 5, 5);
			}
			else if (mLeftNote[i].State == NoteState::Miss)
			{
				mLeftNote[i].Alpha -= 2.f * Time::GetInstance()->DeltaTime();
			}

			if (mRightNote[i].State == NoteState::Active)
			{
				mRightNote[i].X -= mRightNote[i].Speed * Time::GetInstance()->DeltaTime();
				mRightNote[i].Rc = RectMakeCenter(mRightNote[i].X, mRightNote[i].Y, 5, 5);
			}
			else if (mRightNote[i].State == NoteState::Miss)
			{
				mRightNote[i].Alpha -= 2.f* Time::GetInstance()->DeltaTime();
			}
		}

		if (mMiss[i].FrameCount > 0)
		{
			mMiss[i].Rect.top -= 2.f * Time::GetInstance()->DeltaTime();
			mMiss[i].FrameCount -= 0.5f * Time::GetInstance()->DeltaTime();
		}

		if (mLeftNote[i].Alpha <= 0 && mRightNote[i].Alpha <= 0)
		{
			if (mLeftNote[i].State == NoteState::Active && mRightNote[i].State == NoteState::Active)
			{
				COMBO->ComboReset();
				MissNote();
			}

			mLeftNote[i].State = NoteState::Unactive;
			mRightNote[i].State = NoteState::Unactive;
		}	
	}
	NoteReset();
	CheckFront();

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
	mNotCall = true;
}

void Beat::Render(HDC hdc)
{
	//노트
	if (!mFreeMode)
	{
		for (int i = 0; i < 30; ++i)
		{
			if (mLeftNote[i].State != NoteState::Unactive)
			{
				mLeftNote[i].Image->AlphaScaleRender(hdc, mLeftNote[i].X - 5, mLeftNote[i].Y - 50, 10, 70, mLeftNote[i].Alpha);
				//Gizmo::GetInstance()->DrawRect(hdc, mLeftNote[i].Rc, Gizmo::Color::Green);
			}
			if (mRightNote[i].State != NoteState::Unactive)
			{
				mRightNote[i].Image->AlphaScaleRender(hdc, mRightNote[i].X - 5, mRightNote[i].Y - 50, 10, 70, mRightNote[i].Alpha);
				//Gizmo::GetInstance()->DrawRect(hdc, mRightNote[i].Rc, Gizmo::Color::Green);
			}
			if (mMiss[i].FrameCount > 0)
			{
				mMiss[i].Image->AlphaScaleRender(hdc, mMiss[i].Rect.left, mMiss[i].Rect.top, 60, 10, mMiss[i].FrameCount);
			}
		}
	}
	//심장
	//Gizmo::GetInstance()->DrawRect(hdc, mHeartImage.Rect, Gizmo::Color::Green);
	mHeartImage.Image->ScaleFrameRender(hdc, WINSIZEX/2 - 60, WINSIZEY - 176,
		mHeartImage.FrameX, mHeartImage.FrameY, 120, 150);

	//테스팅
	//Gizmo::GetInstance()->DrawRect(hdc, RectMake(-1, 0, WINSIZEX / 2, WINSIZEY +1), Gizmo::Color::Red);
	//float t = SoundPlayer::GetInstance()->GetPosition(mNowMusic);
	//wstring test = to_wstring(t);
	//TextOut(hdc,10,10,test.c_str(),test.length());
}

void Beat::SetMusic(const wstring& keyname, const wstring& beatfilename)
{
	//스테이지(필드) 진입시 해당 함수 호출
	mNowMusic = keyname;
	mDeadLine = SoundPlayer::GetInstance()->GetFullPosition(keyname) / 7 * 3;
	FileManager::LoadBeat(beatfilename,mSaveQueue);
	mRunQueue = mSaveQueue;

	mTiming = mRunQueue.front();
	mRunQueue.pop();
	mArrive = mRunQueue.front();
	mRunQueue.pop();
}

void Beat::ResetMusic()
{
	mRunQueue = mSaveQueue;

	mTiming = mRunQueue.front();
	mRunQueue.pop();
	mArrive = mRunQueue.front();
	mRunQueue.pop();
	SoundPlayer::GetInstance()->SetPosition(mNowMusic, 0.f);
}

bool Beat::IsDecision()
{
	mNotCall = false;

	if(mFreeMode)
		return true;

	POINT pos = { mLeftNote[mFrontNote].X, mLeftNote[mFrontNote].Y };
	if (PtInRect(&mHeartImage.Rect, pos))
	{
		mTurn = true;
		NoteSuccess();
		return true;
	}
	//miss
	COMBO->ComboReset();
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
	//mTiming = mRunQueue.front();
	//mRunQueue.pop();
	mTiming = mArrive;
	mArrive = mRunQueue.front();
	mRunQueue.pop();
}

void Beat::MissNote()
{
	mTurn = true;
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
	//you missed
	for (int i = 0; i < mMiss.size(); ++i)
	{
		if (mMiss[i].FrameCount <= 0)
		{
			mMiss[i].Rect = RectMakeCenter(WINSIZEX / 2, mDefaultY - 50, 60, 10);
			mMiss[i].FrameCount = 1.f;
			break;
		}
	}
	SoundPlayer::GetInstance()->Play(L"combo_missed",1.f);
}


void Beat::SetNote()
{
	float speed = 210.f;
	//float speed = (float)(WINSIZEX/2.f) / (mArrive - mTiming) * 125.f;
	//비활성화된 노트 중 가장 앞에있는 노트를 찾아 활성화
	for (int i = 0; i < 30; ++i)
	{
		if (mLeftNote[i].State == NoteState::Unactive)
		{
			mLeftNote[i].State = NoteState::Active;
			mLeftNote[i].Speed = (float)speed;
			//음악의 재생시간이 mDeadLine을 넘어가면 노트 이미지를 변경한다
			if (mNowMusic != L"")
			{
				if (mDeadLine <= SoundPlayer::GetInstance()->GetPosition(mNowMusic) && !mIsLoop)
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
			mRightNote[i].Speed = (float)speed;
			if (mNowMusic != L"")
			{
				if (mDeadLine <= SoundPlayer::GetInstance()->GetPosition(mNowMusic) && !mIsLoop)
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
			if (mLeftNote[i].X != 0)
			{
				Note temp = mLeftNote[i];
				temp.X = 0;
				temp.Y = mDefaultY;
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
			if (mRightNote[i].X != WINSIZEX)
			{
				Note temp = mRightNote[i];
				temp.X = WINSIZEX;
				temp.Y = mDefaultY;
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

void Beat::CheckFront()
{
	for (int i = 0; i < mLeftNote.size(); ++i)
	{
		if (mLeftNote[i].State == NoteState::Active)
		{
			mFrontNote = i;
			break;
		}
	}
}
