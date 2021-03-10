#pragma once
#define WINSTARTX 10
#define WINSTARTY 50
#define WINSIZEX 1280
#define WINSIZEY 720

#define TileCountX 10
#define TileCountY 10
#define TileSize 32

//���ڷ� ���� p�� �����ϰ� NULL�� �ʱ�ȭ �ϴ� ��ũ�� �Լ�, �����ϰ� ����
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//�̱��� ��ũ��
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

#define Resources(Path) (wstring(L"../02_Resources/").append(Path))

//�ݼ�
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}