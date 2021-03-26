#include "pch.h"
#include "Weapon.h"
#include "Item.h"
#include "Player.h"
#include "Camera.h"

Weapon::Weapon(float posx, float posy, WeaponType type, WeaponMaterial material, ItemState state)
{

	if (ObjectManager::GetInstance()->FindObject("Player"))
		mPlayer = (Player*)ObjectManager::GetInstance()->FindObject("Player");
	else
		mPlayer = nullptr;

	mType = ItemType::Weapon;
	mWeaponType = type;
	mWeaponMaterial = material;
	mState = state;

	mX = posx;
	mY = posy;

	mImage.Image = IMAGEMANAGER->FindImage(L"Weapon");

	//생성할때 타입에 따라 공격범위(mRange)와 공격력(mAtk) 지정
	switch (type)
	{
		case WeaponType::Dagger:
			mWeaponAttribute = WeaponAttribute::Throw;
			mImage.FrameY = 0;
			break;
		case WeaponType::Broadsword:
			mWeaponAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 2;
			break;
		case WeaponType::Rapier:
			mWeaponAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 4;
			break;
		case WeaponType::Spear:
			mWeaponAttribute = WeaponAttribute::Throw;
			mImage.FrameY = 6;
			break;
		case WeaponType::Longsword:
			mWeaponAttribute = WeaponAttribute::Splash;
			mImage.FrameY = 8;
			break;
		case WeaponType::Bow:
			mWeaponAttribute = WeaponAttribute::Normal;
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
	if (mState == ItemState::Owned)
	{
		//옵시디언 타입이면
		if (mMaterial == ItemMaterial::Obsidian)
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
		if (mState == ItemState::NotOwned)
		{
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mX, mY))
			{
				CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc,mImage.Image,
					mX, mY ,
					mImage.FrameX, mImage.FrameY, TileSize, TileSize);
			}
		}
		else if (mState == ItemState::Owned)
		{
			mImage.Image->ScaleFrameRender(hdc, 50, 50, mImage.FrameX, mImage.FrameY, 64, 64);
		}
	}
}

bool Weapon::SetRange(const int &key, vector<POINT> &range)
{
	if (!mPlayer)
		return false;

	int posx = mPlayer->GetIndexX();
	int posy = mPlayer->GetIndexY();
	int disx = 0;
	int disy = 0;

	if (key == VK_LEFT || key == 'A')
	{
		disx = - 1;
	}
	else if (key == VK_RIGHT || key == 'D')
	{
		disx = 1;
	}
	else if (key == VK_UP || key == 'W')
	{
		disy = - 1;
	}
	else if (key == VK_DOWN || key == 'S')
	{
		disy = 1;
	}


	switch (mWeaponType)
	{
	case WeaponType::Dagger:
		range.push_back(POINT{ posx+disx, posy+disy });
		return true;
		break;
	case WeaponType::Broadsword:
		if (disx)	//disx !=0 && disy == 0, 즉 좌우 공격(x고정 + y변경)
		{
			range.push_back(POINT{ posx + disx, posy });
			range.push_back(POINT{ posx + disx, posy - 1 });
			range.push_back(POINT{ posx + disx, posy + 1});
			return true;
		}
		else		//disx ==0 && disy != 0, 즉 상하 공격(x변경 + y고정)
		{
			range.push_back(POINT{ posx , posy + disy });
			range.push_back(POINT{ posx - 1, posy + disy });
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

bool Weapon::GetRange(const int key, vector<POINT>& range)
{
	range.clear();
	range.shrink_to_fit();

	if (key == VK_LEFT || key == 'A' ||
		key == VK_RIGHT || key == 'D' ||
		key == VK_UP || key == 'W' ||
		key == VK_DOWN || key == 'S' )
	{
		if (SetRange(key, range))
		{
			return true;
		}
	}
	return false;
}
