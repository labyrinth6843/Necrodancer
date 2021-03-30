#include "pch.h"
#include "KingConga.h"

KingConga::KingConga(const string& name, int x, int y): Enemy(name)
{
	mX = x * TileSize;
	mY = y * TileSize;

	mThronePosX = x * TileSize;
	mThronePosY = y * TileSize;

	mHp = 10;
	mCoin = 50;
	mAtk = 2;

	mOpacity = 0.f;
	mIsVisible = false;

	mImage = ImageManager::GetInstance()->FindImage(L"KingConga");
	mThroneImage = ImageManager::GetInstance()->FindImage(L"KingCongaThrone");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.1f);
	mIdleAnimation->Play();

	mMoveAnimation = new Animation();
	mMoveAnimation->InitFrameByStartEnd(5, 0, 6, 0, false);
	mMoveAnimation->SetIsLoop(true);
	mMoveAnimation->SetFrameUpdateTime(0.5f);
	mMoveAnimation->Play();

	mCurrentAnimation = mIdleAnimation;
}

void KingConga::Init()
{

}

void KingConga::Update()
{
	if (Beat::GetInstance()->NextTurn() == true) {
		if (mIsMove == false) {
			if (mIsMoveState == true) {
				POINT temp = DestinationValidationCheck();
				if (WallCheck(temp.x, temp.y) == false) {
					if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
						if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
							Attack();
						else
							Move(temp.x, temp.y);
					}

				}
			}
		}
	}
	if (mIsMove == true) {
		mMoveTime += Time::GetInstance()->DeltaTime();
		float ratio = mMoveTime / 0.15f;
		mX = Math::Lerp(mInitX, mDestX, ratio);
		mY = Math::Lerp(mInitY, mDestY, ratio);

		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();

		if (ratio >= 1.f)
		{
			mX = mDestX;
			mY = mDestY;
			mIsMove = false;
			mCorrectionY = 0.f;
		}
	}

	mGroundPtr->GetAlpha((int)(mThronePosX / TileSize), (int)(mThronePosY / TileSize), mThroneOpacity);

	if (mThroneOpacity > 0.5f)
		mIsThroneVisible = true;
	else
		mIsThroneVisible = false;

	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
	if (mOpacity > 0.7f) {
		mIsMoveState = true;
		mCurrentAnimation = mMoveAnimation;
	}
		

	//흑백에서 컬러로 넘어가는 시점
	if (mOpacity > 0.5f)
		mIsVisible = true;
	else
		mIsVisible = false;

	mCurrentAnimation->Update();
}

void KingConga::Release()
{
	SafeDelete(mIdleAnimation);
	SafeDelete(mMoveAnimation);
}

void KingConga::Render(HDC hdc)
{
	if(mIsMoveState == true && mIsThroneVisible == true)
		CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mThroneImage, mThronePosX - 3, mThronePosY - 39, 44, 78);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX - 11, mY + mCorrectionY - 39, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 58, 78);
}

void KingConga::Attack()
{
	float damage = (float)mAtk - mPlayerPtr->GetDef();
	if (damage <= 0.f)
		damage = 1.f;
	mPlayerPtr->HpDown(damage);

	int random = Random::GetInstance()->RandomInt(100) % 3;
	switch (random) {
	case 0:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_1", 1.f);
		break;
	case 1:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_2", 1.f);
		break;
	case 2:
		SoundPlayer::GetInstance()->Play(L"kingconga_attack_3", 1.f);
		break;
	}
}

void KingConga::IsAttacked(int dmg)
{
	mHp -= dmg;
	mIsMoveState = true;
	if (mHp <= 0) {
		SoundPlayer::GetInstance()->Play(L"kingconga_death", 1.f);

		this->SetIsActive(false);
		this->SetIsDestroy(true);
		Combo::GetInstance()->ComboUp();
	}
	else {
		mX = Random::GetInstance()->RandomInt(mWallPtr->GetMapSize().x) * TileSize;
		mY = Random::GetInstance()->RandomInt(mWallPtr->GetMapSize().y) * TileSize;
		while (mWallPtr->GetFrameIndexX(mX / TileSize, mY / TileSize) != 0 || mWallPtr->GetFrameIndexY(mX / TileSize, mY / TileSize) != 0) {
			mX = Random::GetInstance()->RandomInt(mWallPtr->GetMapSize().x) * TileSize;
			mY = Random::GetInstance()->RandomInt(mWallPtr->GetMapSize().y) * TileSize;
		} 

		int random = Random::GetInstance()->RandomInt(100) % 3;
		switch (random) {
		case 0:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_1", 1.f);
			break;
		case 1:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_2", 1.f);
			break;
		case 2:
			SoundPlayer::GetInstance()->Play(L"kingconga_hit_3", 1.f);
			break;
		}
	}
}

void KingConga::Move(int dirX, int dirY)
{
	mMoveTime = 0.f;
	mIsMove = true;

	mDestX = mX + TileSize * dirX;
	mDestY = mY + TileSize * dirY;

	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	mInitX = mX;
	mInitY = mY;
	mCorrectionY = 0.f;
	mJumpPower = 150.f;

	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
		mIsMove = true;
	else
		mIsMove = false;
}

POINT KingConga::DestinationValidationCheck()
{
	mDestX = mPlayerPtr->GetX();
	mDestY = mPlayerPtr->GetY();
	mDestIndexX = mDestX / TileSize;
	mDestIndexY = mDestY / TileSize;

	int disX = abs(mX / TileSize - mDestIndexX);
	int disY = abs(mY / TileSize - mDestIndexY);


	if (disX > disY) {
		if (mX > mDestX) {
			return { -1,0 };
		}
		else {
			return { 1, 0 };
		}
	}
	else if (disX < disY) {
		if (mY > mDestY) {
			return { 0, -1 };
		}
		else {
			return { 0, 1 };
		}
	}
	else {
		if (mX > mDestX) {
			if (mY > mDestY)
				return { -1, -1 };
			else
				return { -1, 1 };
		}
		else {
			if (mY > mDestY)
				return { 1, -1 };
			else
				return { 1, 1 };
		}
	}
}