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
		POINT Pos;
		RECT Rc;
		NoteState State;
		float Alpha = 1.f;
	};
	struct FrameImage
	{
		Image* Image;
		int FrameX;
		int FrameY;
		float FrameCount = 0.f;
	};
private:
	wstring mNowMusic;

	int mTiming;	//노트세팅 시점 체크용
	queue<int> mRunQueue;	//txt를 읽어 노트세팅 타이밍 저장용
	queue<int> mSaveQueue;	//보스전처럼 반복 재생용
	
	vector<Note> mLeftNote;	//왼쪽에서 중앙으로 오는 노트
	vector<Note> mRightNote; //오른쪽에서 중앙으로 오는 노트

	RECT mHeart;
	float mDeadLine;

	FrameImage mHeartImage;
	Image* mNoteImage;

	bool mIsBoss;
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

	bool GetIsBoss() { return mIsBoss; };
	void SetIsBoss(bool b) { mIsBoss = b; };
private:
	void SetTiming();	//Update내부에서 호출될 함수, 노트의 등장 타이밍
	void SetNote();		//비활성화된 노트중 
	void NoteReset();	//Active가 false가 된 노트를 시작 위치에 옮기는 함수
	void MissNote();
};

