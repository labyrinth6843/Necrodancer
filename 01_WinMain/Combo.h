#pragma once
class Combo
{
	Singleton(Combo);
private:
	int mCombo;
	int mMaxCombo;
	Image* mText;
	FrameImage mNum;
public:
	Combo();
	~Combo();

	void Render(HDC hdc);

	inline int GetCombo() { return mCombo; }
	inline void ComboUp()
	{ 
		if (mCombo == 1)
			SoundPlayer::GetInstance()->Play(L"combo_start", 1.f);
		mCombo++;
		if (mCombo > mMaxCombo)
			mCombo = mMaxCombo;
	}
	inline void ComboDown()
	{ 
		mCombo--;
		if (mCombo < 1)
			mCombo = 1;
	}
	inline void ComboReset()
	{ 
		if(mCombo != 1)
			SoundPlayer::GetInstance()->Play(L"combo_reset", 1.f);
		mCombo = 1; 
	}
};
#define COMBO Combo::GetInstance()