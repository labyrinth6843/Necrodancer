#include "pch.h"
#include "TitleScene.h"

void TitleScene::Init(){
	ImageManager::GetInstance()->LoadFromFile(L"Title", Resources(L"Title.bmp"), 480, 270, false);

	TitleImage = ImageManager::GetInstance()->FindImage(L"Title");
}

void TitleScene::Release(){

}

void TitleScene::Update(){
	//아무키 입력 확인
	//proc에서 인풋쪽에 함수 따로 팔 것
	//확인 완료 시 인게임 혹은 맵툴 씬으로 전환
	//SceneManager::GetInstance()->LoadScene(L"GameScene");
	//SceneManager::GetInstance()->LoadScene(L"MapToolScene");
}

void TitleScene::Render(HDC hdc){
	TitleImage->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);
}
