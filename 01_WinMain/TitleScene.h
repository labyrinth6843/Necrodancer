#pragma once
#include "Scene.h"

class Image;
class TitleScene:public Scene{
	Image* TitleImage;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

