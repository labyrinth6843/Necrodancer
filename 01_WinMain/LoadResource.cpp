﻿#include "pch.h"
#include "FileManager.h"

#pragma comment(lib, "msimg32.lib")

void FileManager::LoadResource()
{
	//{{ 버튼 관련 이미지 ~
	ImageManager::GetInstance()->LoadFromFile(L"Save", Resources(L"ButtonIcon/Save.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Load", Resources(L"ButtonIcon/Load.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Undo", Resources(L"ButtonIcon/Undo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Redo", Resources(L"ButtonIcon/Redo.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Clear", Resources(L"ButtonIcon/Clear.bmp"), 88, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Play", Resources(L"ButtonIcon/Play.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Tool", Resources(L"ButtonIcon/Tool.bmp"), 72, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"GroundButton", Resources(L"ButtonIcon/Ground.bmp"), 104, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"WallButton", Resources(L"ButtonIcon/Wall.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"DecoButton", Resources(L"ButtonIcon/Deco.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"ItemButton", Resources(L"ButtonIcon/Item.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"ObjectButton", Resources(L"ButtonIcon/Object.bmp"), 104, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Prev", Resources(L"ButtonIcon/Prev.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Next", Resources(L"ButtonIcon/Next.bmp"), 72, 48, 1, 2, false);

	ImageManager::GetInstance()->LoadFromFile(L"Select", Resources(L"ButtonIcon/Select.bmp"), 104, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Drag", Resources(L"ButtonIcon/Drag.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Fill", Resources(L"ButtonIcon/Fill.bmp"), 72, 48, 1, 2, false);
	ImageManager::GetInstance()->LoadFromFile(L"Set", Resources(L"ButtonIcon/Set.bmp"), 56, 48, 1, 2, false);

	//}}

	//{{ 맵 + 오브젝트 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"SelectTile", Resources(L"SelectTile.bmp"), 32, 32, true);
	ImageManager::GetInstance()->LoadFromFile(L"Black", Resources(L"black.bmp"), 1183, 736, true);
	
	//{{ 팔레트 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"GroundPallet", Resources(L"Pallet/GroundPallet.bmp"), 130, 26, 5, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"WallPallet", Resources(L"Pallet/WallPallet.bmp"), 130, 182, 5, 7, true);
	ImageManager::GetInstance()->LoadFromFile(L"DecoPallet", Resources(L"Pallet/DecoPallet.bmp"), 130, 26, 5, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"ItemPallet1", Resources(L"Pallet/ItemPallet1.bmp"), 130, 260, 5, 10, true);
	ImageManager::GetInstance()->LoadFromFile(L"ItemPallet2", Resources(L"Pallet/ItemPallet2.bmp"), 130, 78, 5, 3, true);
	ImageManager::GetInstance()->LoadFromFile(L"MonsterPallet", Resources(L"Pallet/MonsterPallet.bmp"), 130, 52, 5, 2, true);
	//}}

	//{{ 아이템 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Weapon", Resources(L"Item/Weapon.bmp"), 243, 324, 9, 12, true);
	ImageManager::GetInstance()->LoadFromFile(L"Armor", Resources(L"Item/Armor.bmp"), 260, 52, 10, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Torch", Resources(L"Item/Torch.bmp"), 189, 54, 7, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Shovel", Resources(L"Item/Shovel.bmp"), 208, 52, 8, 2, true);
	//}}

	//{{ 캐릭터 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Head", Resources(L"Player/Head.bmp"), 112, 22, 8, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Body", Resources(L"Player/Body.bmp"), 136, 150, 8, 10, true);
	//}}

	//{{ 적 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"Zombie", Resources(L"Enemy/Zombie.bmp"), 320, 150, 16, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime1", Resources(L"Enemy/Slime1.bmp"), 104, 104, 4, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime2", Resources(L"Enemy/Slime2.bmp"), 208, 104, 8, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"Slime3", Resources(L"Enemy/Slime3.bmp"), 104, 104, 4, 4, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton1", Resources(L"Enemy/Skeleton1.bmp"), 208, 208, 8, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton2", Resources(L"Enemy/Skeleton2.bmp"), 234, 208, 9, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Skeleton3", Resources(L"Enemy/Skeleton3.bmp"), 234, 208, 9, 8, true);
	ImageManager::GetInstance()->LoadFromFile(L"Nightmare1", Resources(L"Enemy/Nightmare1.bmp"), 285, 84, 5, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Nightmare2", Resources(L"Enemy/Nightmare2.bmp"), 285, 84, 5, 2, true);
	//}}

	//{{ NPC 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"ShopKeeper", Resources(L"NPC/ShopKeeper.bmp"), 376, 76, 8, 2, true);
	//}}

	//{{ 맵 타일 이미지
	ImageManager::GetInstance()->LoadFromFile(L"GroundTile", Resources(L"Tile/GroundTile.bmp"), 208, 52, 8, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"WallTile", Resources(L"Tile/WallTile.bmp"), 125, 336, 5, 7, true);
	//}}

	//{{ HUD 관련 이미지
	ImageManager::GetInstance()->LoadFromFile(L"BeatBlue", Resources(L"HUD/BeatMark1.bmp"), 6, 32, true);
	ImageManager::GetInstance()->LoadFromFile(L"BeatGreen", Resources(L"HUD/BeatMark2.bmp"), 6, 32, true);
	ImageManager::GetInstance()->LoadFromFile(L"BeatRed", Resources(L"HUD/BeatMakr3.bmp"), 6, 32, true);
	ImageManager::GetInstance()->LoadFromFile(L"BeatHeart", Resources(L"HUD/Heart.bmp"), 82, 52, 2, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"HUDCoin", Resources(L"HUD/HUDCoin.bmp"), 20, 20, true);
	ImageManager::GetInstance()->LoadFromFile(L"HUDHealth", Resources(L"HUD/HUDHealth.bmp"), 72, 22, 3, 1, true);
	//}}

	//{{ ost 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_1", Resources(L"Sound/ost/zone1_1.mp3"),false);
	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_1_shopkeeper", Resources(L"Sound/ost/zone1_1_shopkeeper.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_2", Resources(L"Sound/ost/zone1_2.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_2_shopkeeper", Resources(L"Sound/ost/zone1_2_shopkeeper.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_3", Resources(L"Sound/ost/zone1_3.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"zone1_3_shopkeeper", Resources(L"Sound/ost/zone1_3_shopkeeper.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga", Resources(L"Sound/ost/kingconga.mp3"), true);
	//}}


	//{{ 효과음 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"move_dirt", Resources(L"Sound/sfx/move/mov_dig_dirt.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"move_stone", Resources(L"Sound/sfx/move/mov_dig_stone.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"move_brick", Resources(L"Sound/sfx/move/mov_dig_brick.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"move_fail", Resources(L"Sound/sfx/move/mov_dig_fail.mp3"), false);
	//}}

	//{{캐릭터 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_1_1", Resources(L"Sound/voice/Player/melee/vo_cad_melee_1_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_1_2", Resources(L"Sound/voice/Player/melee/vo_cad_melee_1_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_1_3", Resources(L"Sound/voice/Player/melee/vo_cad_melee_1_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_1_4", Resources(L"Sound/voice/Player/melee/vo_cad_melee_1_04.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"melee_2_1", Resources(L"Sound/voice/Player/melee/vo_cad_melee_2_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_2_2", Resources(L"Sound/voice/Player/melee/vo_cad_melee_2_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_2_3", Resources(L"Sound/voice/Player/melee/vo_cad_melee_2_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_2_4", Resources(L"Sound/voice/Player/melee/vo_cad_melee_2_04.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"melee_3_1", Resources(L"Sound/voice/Player/melee/vo_cad_melee_3_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_3_2", Resources(L"Sound/voice/Player/melee/vo_cad_melee_3_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_3_3", Resources(L"Sound/voice/Player/melee/vo_cad_melee_3_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_3_4", Resources(L"Sound/voice/Player/melee/vo_cad_melee_3_04.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"melee_4_1", Resources(L"Sound/voice/Player/melee/vo_cad_melee_4_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_4_2", Resources(L"Sound/voice/Player/melee/vo_cad_melee_4_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_4_3", Resources(L"Sound/voice/Player/melee/vo_cad_melee_4_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"melee_4_4", Resources(L"Sound/voice/Player/melee/vo_cad_melee_4_04.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_1", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_2", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_3", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_4", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_04.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_5", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_05.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"hurt_6", Resources(L"Sound/voice/Player/hurt/vo_cad_hurt_06.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"trapdoor_1", Resources(L"Sound/voice/Player/trapdoor/vo_cad_trapdoor_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"trapdoor_2", Resources(L"Sound/voice/Player/trapdoor/vo_cad_trapdoor_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"trapdoor_3", Resources(L"Sound/voice/Player/trapdoor/vo_cad_trapdoor_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"trapdoor_4", Resources(L"Sound/voice/Player/trapdoor/vo_cad_trapdoor_04.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"trapdoor_5", Resources(L"Sound/voice/Player/trapdoor/vo_cad_trapdoor_05.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"death_1", Resources(L"Sound/voice/Player/death/vo_cad_death_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"death_2", Resources(L"Sound/voice/Player/death/vo_cad_death_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"death_3", Resources(L"Sound/voice/Player/death/vo_cad_death_03.mp3"), false);

	SoundPlayer::GetInstance()->LoadFromFile(L"dig_1", Resources(L"Sound/voice/Player/dig/vo_cad_dig_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"dig_2", Resources(L"Sound/voice/Player/dig/vo_cad_dig_02.mp3"), false);	
	SoundPlayer::GetInstance()->LoadFromFile(L"dig_3", Resources(L"Sound/voice/Player/dig/vo_cad_dig_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"dig_4", Resources(L"Sound/voice/Player/dig/vo_cad_dig_04.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"dig_5", Resources(L"Sound/voice/Player/dig/vo_cad_dig_05.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"dig_6", Resources(L"Sound/voice/Player/dig/vo_cad_dig_06.mp3"), false);
	//}}

	//{{ 좀비 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"zombie_attack", Resources(L"Sound/voice/Enemy/zombie/en_zombie_attack.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"zombie_death", Resources(L"Sound/voice/Enemy/zombie/en_zombie_death.mp3"), false);
	//}}

	//{{ 킹콩가 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_announcer", Resources(L"Sound/voice/Enemy/kingconga/vo_announcer_kingconga.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_cry_1", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_cry_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_cry_2", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_cry_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_attack_1", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_attack_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_attack_2", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_attack_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_attack_3", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_attack_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_hit_1", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_hit_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_hit_2", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_hit_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_hit_3", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_hit_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"kingconga_death", Resources(L"Sound/voice/Enemy/kingconga/en_kingconga_death.mp3"), false);
	//}}
	
	//{{ 슬라임 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_attack", Resources(L"Sound/voice/Enemy/slime/en_slime_attack.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_hit_1", Resources(L"Sound/voice/Enemy/slime/en_slime_hit_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_hit_2", Resources(L"Sound/voice/Enemy/slime/en_slime_hit_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_hit_3", Resources(L"Sound/voice/Enemy/slime/en_slime_hit_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_death_1", Resources(L"Sound/voice/Enemy/slime/en_slime_death_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_death_2", Resources(L"Sound/voice/Enemy/slime/en_slime_death_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"slime_death_3", Resources(L"Sound/voice/Enemy/slime/en_slime_death_03.mp3"), false);
	//}}

	//{{ 스켈레톤 관련 사운드
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_attack", Resources(L"Sound/voice/Enemy/skeleton/en_skel_attack.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_death", Resources(L"Sound/voice/Enemy/skeleton/en_skel_eath.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_hit_1", Resources(L"Sound/voice/Enemy/skeleton/en_skel_hit_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_hit_2", Resources(L"Sound/voice/Enemy/skeleton/en_skel_hit_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_hit_3", Resources(L"Sound/voice/Enemy/skeleton/en_skel_hit_03.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_head_loss_1", Resources(L"Sound/voice/Enemy/skeleton/en_skel_head_loss_01.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_head_loss_2", Resources(L"Sound/voice/Enemy/skeleton/en_skel_head_loss_02.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"skeleton_head_loss_3", Resources(L"Sound/voice/Enemy/skeleton/en_skel_head_loss_03.mp3"), false);
	//}}
}