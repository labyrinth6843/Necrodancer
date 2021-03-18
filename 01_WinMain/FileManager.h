#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"

class FileManager
{
public:
	static void LoadMap(wstring filename, vector<vector<Tile*>>& saveList, int tilesizeX = TileSize, int tilesizeY = TileSize);
	static void LoadResource();
	static void LoadBeat(wstring filename, queue<int> &savequeue);
};

