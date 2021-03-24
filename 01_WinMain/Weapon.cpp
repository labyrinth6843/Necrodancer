﻿#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "Camera.h"

void Weapon::Init(float posx, float posy, WeaponType type, WeaponMaterial material, WeaponState state)
{
	if (ObjectManager::GetInstance()->FindObject("Player"))
		mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	else
		mPlayer = nullptr;

	mType = type;
	mMaterial = material;
	mState = state;

	mImage.Image = IMAGEMANAGER->FindImage(L"Weapon");

	//생성할때 타입에 따라 공격범위(mRange)와 공격력(mAtk) 지정
	switch (type)
	{
		case WeaponType::Dagger:
			mAttribute = WeaponAttribute::Throw;
			mImage.FrameY = 0;
			break;
		case WeaponType::Broadsword:
			mAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 2;
			break;
		case WeaponType::Rapier:
			mAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 4;
			break;
		case WeaponType::Spear:
			mAttribute = WeaponAttribute::Throw;
			mImage.FrameY = 6;
			break;
		case WeaponType::Longsword:
			mAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 8;
			break;
		case WeaponType::Bow:
			mAttribute = WeaponAttribute::Normal;
			mImage.FrameY = 10;
			break;
		case WeaponType::None:
		default:
			mImage.Image = nullptr;
			break;
	}
	switch (material)
	{
	case WeaponMaterial::Basic:	
		mAtk = 1;
		mImage.FrameX = 0;
		break;
	case WeaponMaterial::Blood:	
		mAtk = 1;
		mImage.FrameX = 1;
		break;
	case WeaponMaterial::Glass:
		mImage.FrameX = 2;
		mAtk = 4;
		break;
	case WeaponMaterial::Gold:	
		mAtk = 1;
		mImage.FrameX = 3;
		break;
	case WeaponMaterial::Titanium:
		mAtk = 2;
		mImage.FrameX = 4;
		break;
	case WeaponMaterial::Obsidian:
		mAtk = 1;
		mImage.FrameX = 5;
		break;
	}

	if (mImage.Image)
	{
		mImage.PositionX = posx;
		mImage.PositionY = posy;
		mImage.FrameWidth = mImage.Image->GetFrameWidth();
		mImage.FrameHeight = mImage.Image->GetFrameHeight();
	}
}

void Weapon::Release()
{
	mPlayer = nullptr;
}

void Weapon::Update()
{

	//습득했을때
	if (mState == WeaponState::Owned)
	{
		//옵시디언 타입이면
		if (mMaterial == WeaponMaterial::Obsidian)
		{
			mAtk = COMBO->GetCombo();
			if (mAtk >= 3)	//1...3
				mAtk = 3;
			mImage.FrameX = 4 + mAtk;	//5~7
		}
	}
}

void Weapon::Render(HDC hdc)
{
	if (mImage.Image)
	{
		if (mState == WeaponState::NotOwned)
			CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc,mImage.Image, mImage.PositionX, mImage.PositionY,
				mImage.FrameX, mImage.FrameY, mImage.FrameWidth, mImage.FrameHeight);
	}
}

bool Weapon::SetRange(const int &key, vector<POINT> &range)
{
	range.clear();
	range.shrink_to_fit();

	int posx = mPlayer->GetIndexX() / TileSize;
	int posy = mPlayer->GetIndexY() / TileSize;
	int disx = 0;
	int disy = 0;

	if (key == VK_LEFT || 'A')
	{
		disx = - 1;
	}
	else if (key == VK_RIGHT || 'D')
	{
		disx = 1;
	}
	else if (key == VK_UP || 'W')
	{
		disy = - 1;
	}
	else if (key == VK_DOWN || 'S')
	{
		disy = 1;
	}


	switch (mType)
	{
	case WeaponType::Dagger:
		range.push_back(POINT{ posx+disx, posy+disy });
		return true;
		break;
	case WeaponType::Broadsword:
		if (disx)	//disx !=0 && disy == 0, 즉 좌우 공격(x고정 + y변경)
		{
			range.push_back(POINT{ posx + disx, posy - 1 });
			range.push_back(POINT{ posx + disx, posy });
			range.push_back(POINT{ posx + disx, posy + 1});
			return true;
		}
		else		//disx ==0 && disy != 0, 즉 상하 공격(x변경 + y고정)
		{
			range.push_back(POINT{ posx - 1, posy + disy });
			range.push_back(POINT{ posx , posy + disy });
			range.push_back(POINT{ posx + 1, posy + disy });
			return true;
		}
		break;
	case WeaponType::Longsword:
	case WeaponType::Rapier:
	case WeaponType::Spear:
		if (disx)	//disx !=0 && disy == 0, 즉 좌우 공격(x 2칸 + y고정)
		{
			range.push_back(POINT{ posx + disx, posy });
			range.push_back(POINT{ posx + disx*2, posy });
			return true;
		}
		else		//disx ==0 && disy != 0, 즉 상하 공격(x고정 + y 2칸)
		{
			range.push_back(POINT{ posx , posy + disy });
			range.push_back(POINT{ posx , posy + disy*2 });
			return true;
		}
		break;
	case WeaponType::Bow:
		if (disx)	//disx !=0 && disy == 0, 즉 좌우 공격(x 3칸 + y고정)
		{
			range.push_back(POINT{ posx + disx, posy });
			range.push_back(POINT{ posx + disx * 2, posy });
			range.push_back(POINT{ posx + disx * 3, posy });
			return true;
		}
		else		//disx ==0 && disy != 0, 즉 상하 공격(x고정 + y 3칸)
		{
			range.push_back(POINT{ posx , posy + disy });
			range.push_back(POINT{ posx , posy + disy * 2 });
			range.push_back(POINT{ posx , posy + disy * 3 });
			return true;
		}
		break;
	case WeaponType::None:
	default:
		break;
	}
	return false;
}

bool Weapon::GetRange(const int key, vector<POINT> &range)
{
	range.clear();
	range.shrink_to_fit();

	if (key == VK_LEFT || 'A')
	{
		if (SetRange(key, mLeftRange))
		{
			range = mLeftRange;
			return true;
		}
	}
	else if (key == VK_RIGHT || 'D')
	{
		if (SetRange(key, mRightRange))
		{
			range = mRightRange;
			return true;
		}
	}
	else if (key == VK_UP || 'W')
	{
		if (SetRange(key, mTopRange))
		{
			range = mTopRange;
			return true;
		}
	}
	else if (key == VK_DOWN || 'S')
	{
		if (SetRange(key, mBottomRange))
		{
			range = mBottomRange;
			return true;
		}
	}
	return false;
}