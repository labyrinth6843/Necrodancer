#pragma once
#include <queue>

//Note : ���ڸ� ���� �뵵�� �̹����� ����ϱ� ���� struct
struct Note {
	POINT Pos;
	RECT Rc;		//�Ⱦ����� ������ �ϴ� ����
	bool Active = false;
};

class Beat
{
private:
	Singleton(Beat);

private:
	wstring mNowMusic;

	int mTiming;	//��Ʈ���� ���� üũ��
	queue<int> mRunQueue;	//txt�� �о� ��Ʈ���� Ÿ�̹� �����
	queue<int> mSaveQueue;	//������ ó�� �ݺ� �����
	
	vector<Note> mLeftNote;	//���ʿ��� �߾����� ���� ��Ʈ
	vector<Note> mRightNote;//�����ʿ��� �߾����� ���� ��Ʈ

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
	void SetMusic(const wstring &keyname);//��������(�ʵ�) ���۽� ���ǿ� ���� ������ �� �Լ�
	bool IsDecision();	//�÷��̾� Ŀ�ǵ��
	bool NextTurn();	//���� �̵� Ȥ�� ���� �� Ȯ�ο�
};

