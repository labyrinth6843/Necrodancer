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
		mCombo = 0; 
		//SoundPlayer 콤보 끊겼을 때 소리
	}
};
#define COMBO Combo::GetInstance()

