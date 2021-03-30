#include "pch.h"
#include "Combo.h"

Combo::Combo()
{
	mCombo = 1;
	mMaxCombo = 4;
	mText = IMAGEMANAGER->FindImage(L"CoinMultiplier");
	mNum = { IMAGEMANAGER->FindImage(L"NumberFont"), WINSIZEX / 2 + 60, 694, 0, 0, 6, 8 };
}

Combo::~Combo()
{
}

void Combo::Render(HDC hdc)
{
	//몇 콤보인지 표시
	mText->Render(hdc, WINSIZEX / 2 - 84, 700);
	mNum.Image->ScaleFrameRender(hdc, mNum.PositionX, mNum.PositionY, mCombo, 0, 24, 24);
}
