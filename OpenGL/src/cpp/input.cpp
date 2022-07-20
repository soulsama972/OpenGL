#include "input.h"
#include"GLFW/glfw3.h"

#include<vector>
#include<unordered_map>

struct KeyBoardCallBackInfo
{
    KeyBoardEventCallBack Callback;
    void* pthis;
};

std::vector< KeyBoardCallBackInfo> info;
std::unordered_map<KeyType, KeyState> keyMap;


bool Input::IsKeyPress(KeyType key)
{
    if (keyMap.find(key) != keyMap.end())
        return keyMap[key];
    return false;
}

bool Input::IsKeyDown(KeyType key)
{
    if (keyMap.find(key) != keyMap.end())
        return keyMap[key];
    return true;
}

bool Input::IsKeyHold(KeyType key)
{
    if (keyMap.find(key) != keyMap.end())
        return keyMap[key] == KeyState::HOLD;
    return false;
}

void Input::InsertCallBack(void* pThis)
{
    info.push_back({ 0, pThis });
}

void Input::InsertCallBack(KeyBoardEventCallBack Callback)
{
    info.push_back({Callback, 0 });
}

void Input::RemoveCallBack(KeyBoardEventCallBack Callback)
{
    for (auto begin = info.begin(); begin != info.end(); begin++)
    {
        if (begin->Callback == Callback)
        {
            info.erase(begin);
            break;
        }
    }
}

void Input::RemoveCallBack(void* pThis)
{
    for (auto begin = info.begin(); begin != info.end(); begin++)
    {
        if (begin->pthis == pThis)
        {
            info.erase(begin);
            break;
        }
    }
}

void InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyMap[(KeyType)key] = (KeyState)action;
    for (auto& Callback : info)
    {
        if (Callback.pthis)
            (*(Event*)(Callback.pthis).*& Event::KeyBoardEvent)((KeyType)key, (KeyState)action, (KeyMods)mods);
        else
            Callback.Callback((KeyType)key, (KeyState)action, (KeyMods)mods);
    }
}