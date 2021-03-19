#pragma once
class Image;
class InteractionManager
{
	Singleton(InteractionManager);
private:
	Image* mShovelImage;
public:
	InteractionManager();

	bool ShowShovel(int x, int y);
	Image* GetShovelImg(int x, int y) { return mShovelImage; };
};

