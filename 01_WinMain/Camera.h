#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	enum class Mode : int
	{
		Follow, Smooth, Free
	};
protected:
	Mode mMode;
	GameObject* mTarget;		//ÂÑ¾Æ°¡¾ßÇÒ Å¸°Ù

	float mMoveSpeed;
public:
	Camera();
	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render(HDC hdc)override;

	void SetTarget(GameObject* target) { mTarget = target; }
	void ChangeMode(Mode mode) { mMode = mode; }
public:
	void Render(HDC hdc, class Image* image, int x, int y);
	void Render(HDC hdc, class Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	void FrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY);
	void AlphaRender(HDC hdc, class Image* image, int x, int y, float alpha);
	void AlphaFrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, float alpha);
	void ScaleRender(HDC hdc, class Image* image, int x, int y, int width, int height);
	void ScaleFrameRender(HDC hdc,class Image* image, int x, int y, int frameX, int frameY, int width, int height);
	void AlphaScaleRender(HDC hdc,class Image* image, int x, int y, int width, int height, float alpha);
	void AlphaScaleFrameRender(HDC hdc, class Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha);

	void RenderRect(HDC hdc, RECT rc);
	void RenderEllipse(HDC hdc, float x, float y, float radius);
	void RenderTextBox(HDC hdc, RECT rc, wstring st);

	bool IsInCameraArea(int x, int y);
	bool IsInCameraArea(int x, int y, int range);
	bool IsInCameraArea(float x, float y, float width, float height);
	bool IsInCameraArea(RECT rc);

	inline int GetCameraLeft() { return mRect.left; }
	inline int GetCameraRight() { return mRect.right; }
	inline int GetCameraTop() { return mRect.top; }
	inline int GetCameraBottom() { return mRect.bottom; }

	inline float GetMoveSpeed()const { return mMoveSpeed; }
	inline void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
};

