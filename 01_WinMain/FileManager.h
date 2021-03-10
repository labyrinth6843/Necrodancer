#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"


class FileManager
{
	Singleton(FileManager);

public:
	void LoadMap(wstring filename, vector<vector<Tile*>>& saveList, int tilesize = 50);
};

