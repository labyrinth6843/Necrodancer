#pragma once
#include <bitset>

class Input final
{
public:
	static Input* GetInstance()
	{
		static Input _instance;
		return &_instance;
	}
private:
	enum : int {KeyMax = 256};
private:
	//�ߺ� Ű ����� ���� ���� Ű�� ���� Ű ���� ���
	std::bitset<KeyMax> mKeyPast;
	std::bitset<KeyMax> mKeyCurrent;
private:

	Input();
	virtual ~Input();
public:
	void Update();
	//�ѹ� ���ȴٸ�
	bool GetKeyDown(const int& key);
	//Ű���� ���� ���ٸ�
	bool GetKeyUp(const int& key);
	//Ű�� ������ �ִٸ�
	bool GetKey(const int& key);
	//��� Ű
	bool ToggleKey(const int& key);

		//2��Ű�Է�
	bool DoubleKeyDown(const int& key1, const int& key2);
	bool DoubleKey(const int& key1, const int& key2);
};

#define _Input Input::Get()
