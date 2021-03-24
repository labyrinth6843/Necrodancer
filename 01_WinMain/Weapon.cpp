#include "pch.h"
#include "Weapon.h"
#include "Player.h"
void Weapon::Init(WeaponType type, WeaponMaterial material, WeaponState state)
{
	mType = type;
	mMaterial = material;
	mState = state;

	//�����Ҷ� Ÿ�Կ����� ���ݹ���(mRange)�� ���ݷ�(mAtk) ����
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
