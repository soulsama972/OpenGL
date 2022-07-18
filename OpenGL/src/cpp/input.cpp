#include "input.h"

struct KeyBoardCallBackInfo
{
    _InputCCallBack cCallback;
    _InputCallBack callback;
    void* pthis;
};

std::vector< KeyBoardCallBackInfo> callbacks;
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

void Input::AddClassCallback(_InputCCallBack callback, void* pThis)
{
    callbacks.push_back({ callback, 0, pThis });
}

void Input::AddCallback(_InputCallBack callback)
{
    callbacks.push_back({ 0, callback, 0 });
}

void Input::InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    for (auto& callback : callbacks)
    {
        if (callback.pthis)
            (*(TemplateInputClass*)(callback.pthis).*callback.cCallback)((KeyType)key, (KeyState)action, (KeyMods)mods);
        else
            callback.callback((KeyType)key, (KeyState)action, (KeyMods)mods);
    }
    
    keyMap[(KeyType)key] = (KeyState)action;
}
