#pragma once
class Combo
{
	Singleton(Combo);
private:
	int mCombo;
	int mMaxCombo;
public:
	Combo();
	~Combo();

	void Render(HDC hdc);

	inline int GetCombo() { return mCombo; }
	inline void ComboUp()
	{ 
		if (mCombo == 0)
			SoundPlayer::GetInstance()->Play(L"combo_start", 1.f);
		mCombo++;
		if (mCombo > mMaxCombo)
			mCombo = mMaxCombo;
	}
	inline void ComboDown()
	{ 
		mCombo--;
		if (mCombo < 0)
			mCombo = 0;
	}
	inline void ComboReset()
	{ 
		if(mCombo != 0)
			SoundPlayer::GetInstance()->Play(L"combo_reset", 1.f);
		mCombo = 0; 
	}
};
#define COMBO Combo::GetInstance()