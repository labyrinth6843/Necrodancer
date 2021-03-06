#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

//64비트일 경우에는 해당 라이브러리 불러오게
#ifdef _WIN64
#pragma comment(lib,"../03_Libraries/lib/fmodex64_vc")
//이외의 경우에는 32비트 운영체제에 맞는 라이브러리 불러오기
#else
#pragma comment(lib,"../03_Libraries/lib/fmodex_vc")
#endif

#include "../03_Libraries/inc/fmod.hpp"

#include "DefineHeader.h"
#include "Figure.h"
#include "Random.h"
#include "Input.h"
#include "Math.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "Time.h"
#include "SoundPlayer.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "GameEventManager.h"
#include "Gizmo.h"
#include "Helper.h"
#include "FileManager.h"
#include "Beat.h"
#include "Combo.h"
#include "PathFinder.h"
#include "Hud.h"
#include "PlayerData.h"

//Test용 콘솔창
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

extern POINT _mousePosition;	//마우스 좌표
extern HWND	_hWnd;
extern HINSTANCE	_hInstance;
extern bool key;


