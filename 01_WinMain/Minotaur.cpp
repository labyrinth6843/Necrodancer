//#include "pch.h"
//#include "Minotaur.h"
//
//Minotaur::Minotaur(const string & name, int x, int y):Enemy(name)
//{
//	FileManager::LoadMap(L"Test01", mWallList, TileSize, 72);
//
//	mX = x * TileSize;
//	mY = y * TileSize;
//
//	mHp = 3;
//	mCoin = 10;
//	mAtk = 2.f;
//
//	mOpacity = 0.f;
//	mIsVisible = false;
//
//	mImage = ImageManager::GetInstance()->FindImage(L"Minotaur");
//
//	mLeftAnimation = new Animation();
//	mLeftAnimation->InitFrameByStartEnd(0,0,4,0,false);
//	mLeftAnimation->SetFrameUpdateTime(0.1f);
//	mLeftAnimation->SetIsLoop(true);
//	mLeftAnimation->Play();
//
//	mRightAnimation = new Animation();
//	mRightAnimation->InitFrameByStartEnd(0,2,4,2,false);
//	mRightAnimation->SetFrameUpdateTime(0.1f);
//	mRightAnimation->SetIsLoop(true);
//	mRightAnimation->Play();
//
//	mLeftWallImpactAnimation = new Animation();
//	mLeftWallImpactAnimation->InitFrameByStartEnd(5, 0, 8, 0, false);
//	mLeftWallImpactAnimation->SetFrameUpdateTime(0.1f);
//	mLeftWallImpactAnimation->SetIsLoop(true);
//	mLeftWallImpactAnimation->Play();
//
//	mRightWallImpactAnimation = new Animation;
//	mRightWallImpactAnimation->InitFrameByStartEnd(5,2,8,2,false);
//	mRightWallImpactAnimation->SetFrameUpdateTime(0.1f);
//	mRightWallImpactAnimation->SetIsLoop(true);
//	mRightWallImpactAnimation->Play();
//
//	mDirection = Random::GetInstance()->RandomInt(100) % 2;
//
//	if (mDirection == 0) {
//		mCurrentAnimation = mLeftAnimation;
//		mIsLeft = true;
//	}
//	else {
//		mCurrentAnimation = mRightAnimation;
//		mIsLeft = false;
//	}
//}
//
//void Minotaur::Move(int indexX, int indexY)
//{
//	mMoveTime = 0.f;
//	mIsMove = true;
//
//	mDestX = indexX;
//	mDestY = indexY;
//
//	mDestIndexX = mDestX / TileSize;
//	mDestIndexY = mDestY / TileSize;
//
//	mInitX = mX;
//	mInitY = mY;
//	mCorrectionY = 0.f;
//	mJumpPower = 150.f;
//
//	if (mX > mDestX) {
//		mCurrentAnimation = mLeftAnimation;
//		mIsLeft = true;
//	}
//	else {
//		mCurrentAnimation = mRightAnimation;
//		mIsLeft = false;
//	}
//
//	if (mGroundPtr->IsMove(mDestIndexX, mDestIndexY))
//		mIsMove = true;
//	else
//		mIsMove = false;
//}
//
//POINT Minotaur::DestinationValidationCheck()
//{
//	mDestX = mX;
//	mDestIndexX = mDestX / TileSize;
//	mDestY = mY;
//	mDestIndexY = mDestY / TileSize;
//	
//	mRouteList = PathFinder::GetInstance()->FindPath(mWallList, mX /TileSize, mY  /TileSize, mPlayerPtr->GetX()/TileSize, mPlayerPtr->GetY()/TileSize);
//	Tile* temp = mRouteList.front();
//	mRouteList.erase(mRouteList.begin());
//	return { (int)(temp->GetX()) / TileSize, (int)(temp->GetY()) / TileSize };
//}
//
//void Minotaur::Dig(int indexX, int indexY)
//{
//	
//}
//
//void Minotaur::Init()
//{
//
//}
//
//void Minotaur::Update()
//{
//	if (Beat::GetInstance()->NextTurn() == true) {
//		if (mIsMove == false) {
//			if (mIsLeft == true)
//				mCurrentAnimation = mLeftAnimation;
//			else
//				mCurrentAnimation = mRightAnimation;
//			POINT temp = DestinationValidationCheck();
//			if (WallCheck(temp.x, temp.y) == false) {
//				if (ObjectManager::GetInstance()->FindObject(ObjectLayer::Enemy, POINT{ mDestIndexX, mDestIndexY }) == nullptr) {
//					if (mPlayerPtr->GetX() / TileSize == mDestIndexX && mPlayerPtr->GetY() / TileSize == mDestIndexY)
//						Attack();
//					else
//						Move(temp.x, temp.y);
//				}
//			}
//		}
//	}
//	if (mIsMove == true) {
//		mMoveTime += Time::GetInstance()->DeltaTime();
//		float ratio = mMoveTime / 0.15f;
//		mX = Math::Lerp(mInitX, mDestX, ratio);
//		mY = Math::Lerp(mInitY, mDestY, ratio);
//
//		mCorrectionY -= mJumpPower * Time::GetInstance()->DeltaTime();
//		mJumpPower -= 200.f * Time::GetInstance()->DeltaTime();
//
//		if (ratio >= 1.f)
//		{
//			mX = mDestX;
//			mY = mDestY;
//			mIsMove = false;
//			mCorrectionY = 0.f;
//		}
//	}
//
//	mGroundPtr->GetAlpha((int)(mX / TileSize), (int)(mY / TileSize), mOpacity);
//	//흑백에서 컬러로 넘어가는 시점
//	if (mOpacity > 0.5f)
//		mIsVisible = true;
//	else
//		mIsVisible = false;
//
//	mCurrentAnimation->Update();
//}
//
//void Minotaur::Release()
//{
//	SafeDelete(mLeftAnimation);
//	SafeDelete(mRightAnimation);
//	SafeDelete(mLeftWallImpactAnimation);
//	SafeDelete(mRightWallImpactAnimation);
//}
//
//void Minotaur::Render(HDC hdc)
//{
//	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY + mCorrectionY, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY() + (int)mIsVisible, 39, 39);
//}
//
//void Minotaur::Attack()
//{
//	mPlayerPtr->SetHp(GetHp() - mAtk);
//	SoundPlayer::GetInstance()->Play(L"minotaur_attack", 1.f);
//}
//
//void Minotaur::IsAttacked(int dmg)
//{
//	mHp -= dmg;
//	if (mHp <= 0) {
//		SoundPlayer::GetInstance()->Play(L"minotaur_death",1.f);
//		this->SetIsActive(false);
//		this->SetIsDestroy(true);
//		Combo::GetInstance()->ComboUp();
//	}
//	else {
//		int random = Random::GetInstance()->RandomInt(100) % 3;
//		switch (random) {
//		case 0:
//			SoundPlayer::GetInstance()->Play(L"minotaur_hit_1", 1.f);
//			break;
//		case 1:
//			SoundPlayer::GetInstance()->Play(L"minotaur_hit_2", 1.f);
//			break;
//		case 2:
//			SoundPlayer::GetInstance()->Play(L"minotaur_hit_3", 1.f);
//			break;
//		}
//	}
//}