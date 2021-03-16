#include "pch.h"
#include "FileManager.h"
#include "Tile.h"
#include <stack>
#include <fstream>
#include <iostream>

void FileManager::LoadMap(wstring filename, vector<vector<Tile*>>& saveList, int tilesizeX, int tilesizeY)
{
	ifstream loadStream(L"../04_Data/" + filename + L".txt");

	bool isNew = false;
	if (saveList.size() == 0)	//새로운 벡터에 맵을 넣을거냐
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
	bool sizeCheck = false;	//만약 나중에 크기가 다른 벡터에 새 맵을 넣으려고 할때 쓴거
	int sizeY = 0;
	int sizeX = 0;

	if (loadStream.is_open())
	{
		while (loadStream.eof() == false)
		{
			string line;
			getline(loadStream, line);	//맨위 한줄을 line에 넣는다

			vector<string> subList;	//하나의 [y][x]에 넣을거
			//0 key, 1 indexX, 2 indexY, 3 frameX, 4 frameY, 5 ObjectType, 6 TileType
			//이렇게 하면 line하나 불러와졌으니까 
			while (true)
			{
				int cutIndex = line.find(",");	// find가 토큰(,)을 line안에서 못찾으면 -1
				if (cutIndex == -1)	//0~-1는 값을 못찾는데 남은 line이 있으니까
				{
					subList.push_back(line);//넣어주고 break
					break;
				}
				string sub = line.substr(0, cutIndex);	//0부터 cutIndex까지 분리
				line = line.substr(cutIndex + 1, line.length());	//분리한 다음에 line을 줄이고
				subList.push_back(sub);//저장하고
			}//파일에서 한줄 읽기 끝


			if (subList.size() <= 1)	//size = 1 이면 공백말곤 읽어들인게 없다.
			{
				if (isNew)
				{
					YList.push_back(XList);
					saveList = YList;
				}

				return;
			}


			//읽은거 저장
			/*
			*/
			if (!isNew)
			{
				//방법1 크기가 맞는 벡터
				int x = stoi(subList[1]);
				int y = stoi(subList[2]);

				wstring wstr;
				wstr.assign(subList[0].begin(), subList[0].end());
				saveList[y][x]->SetImage(ImageManager::GetInstance()->FindImage(wstr));
				saveList[y][x]->SetFrameIndexX(stoi(subList[3]));
				saveList[y][x]->SetFrameIndexY(stoi(subList[4]));
				saveList[y][x]->SetTileType((TileType)stoi(subList[5]));
			}
			else
			{
				int x = stoi(subList[1]);
				int y = stoi(subList[2]);

				wstring wstr;
				wstr.assign(subList[0].begin(), subList[0].end());

				//크기 늘리는거
				Tile* tile = new Tile(ImageManager::GetInstance()->FindImage(wstr),
					tilesizeX * x, tilesizeY * y, tilesizeX, tilesizeY,
					stof(subList[3]), stof(subList[4]), (TileType)stoi(subList[5]));
				//원래 사이즈

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
		loadStream.close();
	}
}

void FileManager::LoatBeat(wstring filename, queue<int> &savequeue)
{
	//경로 조정 필요함
	ifstream loadStream(L"../02_Resources/Sound/ost/"+filename+L".txt");	//파일 열기


	if (loadStream.is_open())
	{
		while (loadStream.eof() == false)	//파일의 끝에 도달하면 -1을 반환한다
		{
			string line;
			getline(loadStream, line);	//한줄을 읽어들음, 비트txt는 한줄로 이루어져 있어 모두 읽은 것과 마찬가지

			while (true)
			{
				int cutIndex = line.find(",");	//,를 토큰으로 분리함
				if (cutIndex == -1)	//,를 찾지못한 경우
				{
					savequeue.emplace(stoi(line));
					break;
				}
				int sub =stoi(line.substr(0, cutIndex));	//앞에서부터 찾아낸 cutIndex(,가 있는 위치)까지 잘라냄
				line = line.substr(cutIndex + 1, line.length());//line에서 sub에 해당되는 부분을 제거함
				savequeue.emplace(sub);
			}

		}
	}
}
