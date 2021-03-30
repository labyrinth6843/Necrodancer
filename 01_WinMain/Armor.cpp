#include "pch.h"
#include "Armor.h"

Armor::Armor(float posx, float posy, ArmorMaterial material, ItemState state)
{
	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player"))
		mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	else
		mPlayer = nullptr;

	if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Ground, "Ground"))
		mGroundPtr = (Ground*)ObjectManager::GetInstance()->FindObject("Ground");
	else
		mGroundPtr = nullptr;

	mType = ItemType::Armor;
	mArmorMaterial = material;
	mState = state;

	mX = posx;
	mY = posy;

	mImage.Image = IMAGEMANAGER->FindImage(L"Armor");
	mImage.FrameY = 0;

	switch (material)
	{
	case ArmorMaterial::Leather:
		mDef = 0.5f;
		mImage.FrameX = 0;
		break;
	case ArmorMaterial::Chain:
		mDef = 1.f;
		mImage.FrameX = 1;
		break;
	case ArmorMaterial::Plate:
		mDef = 1.5f;
		mImage.FrameX = 2;
		break;
	case ArmorMaterial::HeavyPlate:
		mDef = 2.f;
		mImage.FrameX = 3;
		break;
	case ArmorMaterial::Karate:
		mDef = 0.f;
		mImage.FrameX = 4;
		break;
	case ArmorMaterial::Glass:
		mImage.FrameX = 5;
		mDef = 999.f;
		break;
	case ArmorMaterial::Obsidian:
		mDef = 1;
		mImage.FrameX = 6;
		break;
	}
}

void Armor::Release()
{
	mPlayer = nullptr;
	mGroundPtr = nullptr;
}

void Armor::Update()
{
	//습득했을때
	if (mState == ItemState::Owned)
	{
		//옵시디언 타입이면
		if (mArmorMaterial == ArmorMaterial::Obsidian)
		{
			float combo = (float)COMBO->GetCombo();
			if (combo >= 4)
				combo = 3.f;
			mDef = 0.5 * combo;
			mImage.FrameX = 5 + (int)(mDef/0.5f);	//6,7,8
		}
	}
	else
	{
		if (mArmorMaterial == ArmorMaterial::Obsidian)
		{
			mImage.FrameX = 6;
		}
		float alpha = 1.f;
		if (mGroundPtr->GetAlpha(mX, mY, alpha))
		{
			if (alpha < 0.4f)
				mIsShadow = true;
			else
				mIsShadow = false;
		}
	}
}

void Armor::Render(HDC hdc)
{
	if (mImage.Image)
	{
		if (mState == ItemState::NotOwned)
		{
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mX, mY))
			{
				if (mIsShadow)
				{
					CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage.Image,
						mX, mY,
						mImage.FrameX, mImage.FrameY + 1, TileSize, TileSize);
				}
				else
				{
					CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage.Image,
						mX, mY,
						mImage.FrameX, mImage.FrameY, TileSize, TileSize);
				}
			}
		}
		else if (mState == ItemState::Owned)
		{
			mImage.Image->ScaleFrameRender(hdc, 120, 50, mImage.FrameX, mImage.FrameY, 64, 64);
		}
	}
}
