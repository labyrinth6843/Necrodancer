#pragma once
class Weapon;
class Armor;
class Player;
class PlayerData
{
	Singleton(PlayerData);
private:
	//���� ����
	bool mIsSave;
	//������ ����
	float mHp;
	Weapon* mWeapon;
	Armor* mArmor;
public:
	PlayerData();
	void Release();
	void CopyPlayer(GameObject* player);
	void CopyPlayer(Player* player);
	void LoadPlayer(GameObject* player);
	void LoadPlayer(Player* player);
};
#define PDATA PlayerData::GetInstance()

