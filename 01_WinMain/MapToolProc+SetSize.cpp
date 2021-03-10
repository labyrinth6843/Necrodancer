#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"

LRESULT MapToolScene::Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		//�޼���ť�� WM_QUIT��� �޼����� ���� GetMessage�� false�� ��ȯ�ϰ� �����. �� ������ �����Ų��
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		string strx;
		string stry;

		if (mIsInput == 0)
		{
			break;
		}

		strx = mInputX;
		stry = mInputY;

		if (wParam == VK_BACK)//backspace
		{
			if (mIsInput == 1)
				strx.pop_back();
			if (mIsInput == 2)
				stry.pop_back();
		}
		else if (wParam == VK_RETURN)
		{
			SetSize();
			mIsInput = 0;
		}
		else
		{
			if ((wParam >= 48 && wParam <= 57))
			{
				if (mIsInput == 1 && strx.size() < 5)
				{
					if (strx[0] == '1' && strx.size() == 1)
					{
						if (wParam == 48)
							strx.push_back(wParam);
						else
							strx[0] = wParam;
					}
					else
						strx.push_back(wParam);
				}
				if (mIsInput == 2 && stry.size() < 5)
				{
					if (stry[0] == '1' && stry.size() == 1)
					{
						if (wParam == 48)
							stry.push_back(wParam);
						else
							stry[0] = wParam;
					}
					else
						stry.push_back(wParam);
				}
			}
		}

		if (strx.size() <= 0 || strx[0] == '0')
		{
			strx = "1";
		}
		if (stry.size() <= 0 || stry[0] == '0')
		{
			stry = "1";
		}
		//SizeSet�� �� ���� ����
		mInputY = stry;
		mInputX = strx;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

void MapToolScene::SetSize()
{
	mIsInput = 0;

	mMaxSizeX = stoi(mInputX);
	mMaxSizeY = stoi(mInputY);

	//ũ�� ���� �� ���� Ÿ�� ����
	//�迭�� ����� ���̾���� ���ͷ� ��ȯ�ϰ� �Ʒ� �ּ� ���� �� �׽���
	/*
	int prevY = mGroundList.size();
	int prevX = mGroundList[prevY - 1].size();
	vector<vector<Tile*>> saveGround = mGroundList;
	vector<vector<Tile*>> saveDeco = mDecoList;
	vector<vector<Tile*>> saveItem = mItemList;
	vector<vector<Tile*>> saveObject = mObjectList;

	//ũ�� ������ ���� ����
	mGroundList.clear()
	mDecoList.clear()
	mItemList.clear()
	mObjectList.clear()

	mGroundList.shrink_to_fit();
	mDecoList.shrink_to_fit();
	mItemList.shrink_to_fit();
	mObjectList.shrink_to_fit();

	//size x,y�� �޾� Ÿ�ϸ��� �ִ�ũ�⿡ ���� �� Ÿ���� �������ش�
	vector<Tile*> XList;
	for (int y = 0; y < mMaxSizeY; ++y)
	{
		for (int x = 0; x < mMaxSizeX; ++x)
		{
			XList.push_back(new Tile(nullptr, TileSize * x, TileSize * y, TileSize, TileSize, 0, 0));
		}
		mGroundList.push_back(XList);
		mDecoList.push_back(XList);
		mItemList.push_back(XList);
		mObjectList.push_back(XList);
		XList.clear();	//�־��ְ� ����ֱ�
		XList.shrink_to_fit();
	}

	//������ ������ �ִ´�
	if (prevX <= mMaxSizeX && prevY <= mMaxSizeY)//�������� ���� ������ ũ�Ⱑ ũ�ų� ������
	{
		for (int y = 0; y < prevY; ++y)
		{
			for (int x = 0; x < prevX; ++x)
			{
				mGroundList[y][x] = saveGround[y][x];
				mDecoList[y][x] = saveDeco[y][x];
				mItemList[y][x] = saveItem[y][x];
				mObjectList[y][x] = saveObject[y][x];
			}
		}
	}
	else//���� �������� ���� �������� �Ѿ�� ũ��� ���� �ʴ´�
	{
		for (int y = 0; y < mMaxSizeY; ++y)
		{
			for (int x = 0; x < mMaxSizeX; ++x)
			{
				mGroundList[y][x] = saveGround[y][x];
				mDecoList[y][x] = saveDeco[y][x];
				mItemList[y][x] = saveItem[y][x];
				mObjectList[y][x] = saveObject[y][x];
			}
		}
	}
	*/
}
