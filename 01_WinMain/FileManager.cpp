#include "pch.h"
#include "FileManager.h"
#include "Tile.h"
#include <stack>
#include <fstream>
#include <iostream>

void FileManager::LoadMap(wstring filename, vector<vector<Tile*>>& saveList, int tilesize)
{
	ifstream loadStream(L"../04_Data/" + filename + L".txt");

	bool isNew = false;
	if (saveList.size() == 0)	//���ο� ���Ϳ� ���� �����ų�
		isNew = true;
	else
	{
		int maxY = saveList.size();
		int maxX = saveList[maxY - 1].size();
		for (int y = 0; y < maxY; ++y)
		{
			for (int x = 0; x < maxX; ++x)
			{
				SafeDelete(saveList[y][x]);
			}
		}
		saveList.clear();
		saveList.shrink_to_fit();
		isNew = true;
	}

	vector<vector<Tile*>> YList;
	vector<Tile*> XList;
	bool sizeCheck = false;	//���� ���߿� ũ�Ⱑ �ٸ� ���Ϳ� �� ���� �������� �Ҷ� ����
	int sizeY = 0;
	int sizeX = 0;

	if (loadStream.is_open())
	{
		while (loadStream.eof() == false)
		{
			string line;
			getline(loadStream, line);	//���� ������ line�� �ִ´�

			vector<string> subList;	//�ϳ��� [y][x]�� ������
			//0 key, 1 indexX, 2 indexY, 3 frameX, 4 frameY, 5 ObjectType, 6 TileType
			//�̷��� �ϸ� line�ϳ� �ҷ��������ϱ� 
			while (true)
			{
				int cutIndex = line.find(",");	// find�� ��ū(,)�� line�ȿ��� ��ã���� -1
				if (cutIndex == -1)	//0~-1�� ���� ��ã�µ� ���� line�� �����ϱ�
				{
					subList.push_back(line);//�־��ְ� break
					break;
				}
				string sub = line.substr(0, cutIndex);	//0���� cutIndex���� �и�
				line = line.substr(cutIndex + 1, line.length());	//�и��� ������ line�� ���̰�
				subList.push_back(sub);//�����ϰ�
			}//���Ͽ��� ���� �б� ��


			if (subList.size() <= 1)	//size = 1 �̸� ���鸻�� �о���ΰ� ����.
			{
				if (isNew)
				{
					YList.push_back(XList);
					saveList = YList;
				}

				return;
			}


			//������ ����
			/*
			*/
			if (!isNew)
			{
				//���1 ũ�Ⱑ �´� ����
				int x = stoi(subList[1]);
				int y = stoi(subList[2]);

				wstring wstr;
				wstr.assign(subList[0].begin(), subList[0].end());
				saveList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				saveList[y][x]->SetFrameIndexX(stoi(subList[3]));
				saveList[y][x]->SetFrameIndexY(stoi(subList[4]));
				saveList[y][x]->SetTileType((TileType)stoi(subList[6]));
			}
			else
			{
				int x = stoi(subList[1]);
				int y = stoi(subList[2]);

				wstring wstr;
				wstr.assign(subList[0].begin(), subList[0].end());

				//ũ�� �ø��°�
				Tile* tile = new Tile(ImageManager::GetInstance()->FindImage(wstr),
					tilesize * stof(subList[1]), tilesize * stof(subList[2]), tilesize, tilesize,
					stof(subList[3]), stof(subList[4]), (TileType)stoi(subList[5]));
				//���� ������

				if (sizeY == y - 1)
				{
					YList.push_back(XList);
					XList.clear();
					XList.shrink_to_fit();

					XList.push_back(tile);
					sizeY++;
					sizeCheck = true;
				}
				else
				{
					XList.push_back(tile);
					if (!sizeCheck)
						sizeX++;
				}
			}
		}
	}
}
