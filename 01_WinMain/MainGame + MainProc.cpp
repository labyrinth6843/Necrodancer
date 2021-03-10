#include "pch.h"
#include "MainGame.h"
#include "MapToolScene.h"

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		//�޼���ť�� WM_QUIT��� �޼����� ���� GetMessage�� false�� ��ȯ�ϰ� �����. �� ������ �����Ų��
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		key = wParam;
		break;
		//���콺 �پ� ��
	case WM_MOUSEWHEEL:

		break;
		//���콺 �������� �� ������ �޼���
	case WM_MOUSEMOVE:
		//lparam : ���콺 ��ǥ�� ���� �� �ش� ����(����) �ϳ��� x,y,���� ��� ������.
		//�տ� 32��Ʈ���� y��, �ڿ� 32��Ʈ���� x���� ����(<<,>> ����Ʈ �����ڷ�)
		_mousePosition.x = LOWORD(lParam);
		_mousePosition.y = HIWORD(lParam);
		break;
	}

	if (SceneManager::GetInstance()->CheckCurrentScene(L"MapToolScene"))
	{
		MapToolScene* map = (MapToolScene*)SceneManager::GetInstance()->FindScene(L"MapToolScene");
		map->Proc(hWnd, iMessage, wParam, lParam);

	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
