#pragma once
class Image;
class InteractionManager
{
	Singleton(InteractionManager);
private:
	Image* mShovelImage = ImageManager::GetInstance()->FindImage(L"Shovel");
public:
	InteractionManager();

	void Render(HDC hdc);

	bool ShowShovel(int x, int y);
	Image* GetShovelImg(int x, int y) { return mShovelImage; };
};

