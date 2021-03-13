#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"

void MapToolScene::PushCommand(ICommand* command) {
	command->Execute();
	mCommandList.emplace(command);
}

void MapToolScene::Undo() {
	if (mCommandList.size() == 0)
		return;

	mReCommandList.emplace(mCommandList.top());
	mCommandList.top()->Undo();
	mCommandList.pop();
}

void MapToolScene::Redo() {
	if (mReCommandList.size() == 0)
		return;

	mCommandList.emplace(mReCommandList.top());
	mReCommandList.top()->Redo();
	mReCommandList.pop();
}