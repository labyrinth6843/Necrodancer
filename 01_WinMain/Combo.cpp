#include "pch.h"
#include "Combo.h"

Combo::Combo()
{
	mCombo = 0;
	mMaxCombo = 4;
}

Combo::~Combo()
{
}

void Combo::Render(HDC hdc)
{
	cout << mCombo << endl;
}
