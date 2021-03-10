#pragma once
class Button final
{
	enum class State : int
	{
		Normal, Push,
	};

	function<void(void)> mFunc;	//��ư�������� ����� �Լ�
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	int mFrameX;
	int mFrameY;
	RECT mRect;
	State mState;
	wstring mText;
	class Image* mImage;
public:
	Button(wstring imagekey, wstring text,float x, float y, float sizeX, float sizeY, function<void(void)> func);

	void Update();
	void Render(HDC hdc);

	RECT GetRect() { return mRect; }
};

