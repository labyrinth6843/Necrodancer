#include "pch.h"
#include "PlayerData.h"
#include "Weapon.h"
#include "Armor.h"

PlayerData::PlayerData()
{
	mIsSave = false;
	mHp = 6.f;
	mWeapon = new Weapon(-10.f, -10.f, WeaponType::Dagger, WeaponMaterial::Basic, ItemState::Owned);
	mArmor = new Armor(-10.f, -10.f, ArmorMaterial::None, ItemState::Owned);
}

PlayerData::~PlayerData()
{
}

void PlayerData::Release()
{
	mIsSave = false;
	mHp = 6.f;
}

void PlayerData::CopyPlayer(GameObject* player)
{
	CopyPlayer((Player*)player);
}
void PlayerData::CopyPlayer(Player* player)
{
	mHp = player->GetHp();

	//무기 정보
	mWeapon->SetImage(player->GetWeapon()->GetImage());
	mWeapon->SetWeaponType(player->GetWeapon()->GetWeaponType());
	mWeapon->SetWeaponMaterial(player->GetWeapon()->GetWeaponMaterial());
	mWeapon->SetWeaponAttribute(player->GetWeapon()->GetWeaponAttribute());
	mWeapon->SetFrameImage(player->GetWeapon()->GetFrameImage());
	mWeapon->SetAtk(player->GetWeapon()->GetAtk());

	//방어구 정보
	mArmor->SetImage(player->GetArmor()->GetImage());
	mArmor->SetArmorMaterial(player->GetArmor()->GetArmorMaterial());
	mArmor->SetFrameImage(player->GetArmor()->GetFrameImage());
	mArmor->SetDef(player->GetArmor()->GetDef());

	mIsSave = true;
}

void PlayerData::LoadPlayer(GameObject* player)
{
	LoadPlayer((Player*)player);
}
void PlayerData::LoadPlayer(Player* player)
{
	if (!mIsSave)
		return;
	player->SetHp(mHp);

	//무기 정보
	player->GetWeapon()->SetImage(mWeapon->GetImage());
	player->GetWeapon()->SetWeaponType(mWeapon->GetWeaponType());
	player->GetWeapon()->SetWeaponMaterial(mWeapon->GetWeaponMaterial());
	player->GetWeapon()->SetWeaponAttribute(mWeapon->GetWeaponAttribute());
	player->GetWeapon()->SetFrameImage(mWeapon->GetFrameImage());
	player->SetAtk(player->GetWeapon()->GetAtk());
	HUD->ItemEquip(player->GetWeapon());

	//방어구 정보
	player->GetArmor()->SetImage(mArmor->GetImage());
	player->GetArmor()->SetArmorMaterial(mArmor->GetArmorMaterial());
	player->GetArmor()->SetFrameImage(mArmor->GetFrameImage());
	player->SetDef(mArmor->GetDef());
	HUD->ItemEquip(player->GetArmor());
}
