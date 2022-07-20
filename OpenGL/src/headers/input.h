#pragma once
#include"event.h"


class Input
{
public:
	Input() = default;
	static bool IsKeyPress(KeyType key);
	static bool IsKeyDown(KeyType key);
	static bool IsKeyHold(KeyType key);

	static void InsertCallBack(void* pThis);
	static void InsertCallBack(KeyBoardEventCallBack KeyBoardEvent);

	static void RemoveCallBack(KeyBoardEventCallBack KeyBoardEvent);
	static void RemoveCallBack(void* pThis);
};