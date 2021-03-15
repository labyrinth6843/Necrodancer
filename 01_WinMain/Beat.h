#pragma once
#include <queue>

//Note : 박자를 맞출 용도의 이미지를 출력하기 위한 struct
struct Note {
	POINT Pos;
	RECT Rc;		//안쓸지도 모르지만 일단 생성
	bool Active = false;
};

class Beat
{
private:
	Singleton(Beat);

private:
	wstring mNowMusic;

	int mTiming;	//노트세팅 시점 체크용
	queue<int> mRunQueue;	//txt를 읽어 노트세팅 타이밍 저장용
	queue<int> mSaveQueue;	//보스전 처럼 반복 재생용
	
	vector<Note> mLeftNote;	//왼쪽에서 중앙으로 오는 노트
	vector<Note> mRightNote;//오른쪽에서 중앙으로 오는 노트

	RECT mHeart;
	bool mDeadLine;

	Image* mHeartImage;
	Image* mNoteImage;
public:
	Beat();
	~Beat();

	void Init();
	void Release();
	void Update();
	void Render();

public:
	void SetMusic(const wstring &keyname);//스테이지(필드) 시작시 음악에 대한 세팅을 할 함수
	bool IsDecision();	//플레이어 커맨드용
	bool NextTurn();	//몬스터 이동 혹은 공격 턴 확인용
};

