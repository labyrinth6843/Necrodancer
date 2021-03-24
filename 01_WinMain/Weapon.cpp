#include "pch.h"
#include "Weapon.h"
#include "Player.h"
void Weapon::Init(WeaponType type, WeaponMaterial material, WeaponState state)
{
	mType = type;
	mMaterial = material;
	mState = state;

	//생성할때 타입에따라 공격범위(mRange)와 공격력(mAtk) 지정
	switch (type)
	{
		case WeaponType::Dagger:
		case WeaponType::Broadsword:
		case WeaponType::Longsword:
		case WeaponType::Spear:
		case WeaponType::Rapier:
		case WeaponType::Bow:

		case WeaponType::None: default:
			break;
	}

}

void Weapon::Release()
{
}

void Weapon::Update()
{
}

void Weapon::Render(HDC hdc)
{
}
