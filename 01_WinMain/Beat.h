#pragma once
#include <queue>

class Beat
{
private:
	Singleton(Beat);

private:
	enum class NoteState
	{
		Active,
		Unactive,
		Miss,
		end
	};
	//Note : 박자를 맞출 용도의 이미지를 출력하기 위한 struct
	struct Note {
		Image* Image;
		float X;
		float Y;
		RECT Rc;
		NoteState State;
		float Alpha = 1.f;
		float Speed = 10.f;
	};
	struct FrameImage
	{
		RECT Rect;
		Image* Image;
		int FrameX;
		int FrameY;
		float FrameCount = 0.f;
	};
private:
	float mDefaultY;	//노트의 기본 Y

	wstring mNowMusic;

	float mTiming;	//노트세팅 시점 체크용
	float mArrive;
	queue<int> mRunQueue;	//txt를 읽어 노트세팅 타이밍 저장용
	queue<int> mSaveQueue;	//보스전처럼 반복 재생용
	
	vector<Note> mLeftNote;	//왼쪽에서 중앙으로 오는 노트
	vector<Note> mRightNote; //오른쪽에서 중앙으로 오는 노트

	float mDeadLine;

	FrameImage mHeartImage;
	vector<FrameImage> mMiss;

	bool mIsLoop;
	bool mTurn;
	bool mMusicEnd;
	bool mNotCall;

	int mFrontNote;

	bool mFreeMode = false; //박자 상관없이 무조건 이동 가능한 상태
public:
	Beat();
	~Beat();

	void Init();
	void Release();	//mRun/SaveQueue만 비운다
	void Update();
	void Render(HDC hdc);

public:
	void SetMusic(const wstring &keyname, const wstring& beatfilename);//스테이지(필드) 시작시 음악에 대한 세팅을 할 함수
	bool IsDecision();	//플레이어 커맨드용
	bool NextTurn();	//몬스터 이동 및 공격 턴 확인용

	bool GetIsLoop() { return mIsLoop; };
	void SetIsLoop(bool b) { mIsLoop = b; };

	void SetFreeMode(bool mod) { mFreeMode = mod; }
private:
	void SetTiming();	//Update내부에서 호출될 함수, 노트의 등장 타이밍
	void SetNote();		//비활성화된 노트중 
	void NoteSuccess();
	void NoteReset();	//Active가 false가 된 노트를 시작 위치에 옮기는 함수
	void CheckFront();

	void MissNote();
};
#define BEAT Beat::GetInstance()

