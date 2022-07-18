#pragma once

#include"typing.h"
#include<vector>
#include<unordered_map>
#include"GLFW/glfw3.h"


enum KeyType
{
KEY_UNKNOWN = -1,
KEY_SPACE = 32,
KEY_APOSTROPHE = 39, // '
KEY_COMMA = 44, // ,
KEY_MINUS, // -
KEY_PERIOD, //.
KEY_SLASH, // /
KEY_0,
KEY_1,
KEY_2,
KEY_3,
KEY_4,
KEY_5,
KEY_6,
KEY_7,
KEY_8,
KEY_9,
KEY_SEMICOLON = 59, // ;
KEY_EQUAL =61, // =
KEY_A = 65,
KEY_B,
KEY_C,
KEY_D,
KEY_E,
KEY_F,
KEY_G,
KEY_H,
KEY_I,
KEY_J,
KEY_K,
KEY_L,
KEY_M,
KEY_N,
KEY_O,
KEY_P,
KEY_Q,
KEY_R,
KEY_S,
KEY_T,
KEY_U,
KEY_V,
KEY_W,
KEY_X,
KEY_Y,
KEY_Z,
KEY_LEFT_BRACKET =  91, // [
KEY_BACKSLASH,/* \ */
KEY_RIGHT_BRACKET,// ]
KEY_GRAVE_ACCENT = 96, // `
KEY_ESCAPE = 256,
KEY_ENTER,
KEY_TAB,
KEY_BACKSPACE,
KEY_INSERT,
KEY_DELETE,
KEY_RIGHT,
KEY_LEFT,
KEY_DOWN,
KEY_UP,
KEY_PAGE_UP,
KEY_PAGE_DOWN,
KEY_HOME,
KEY_END,
KEY_CAPS_LOCK,
KEY_SCROLL_LOCK,
KEY_NUM_LOCK,
KEY_PRINT_SCREEN,
KEY_PAUSE,
KEY_F1 = 290,
KEY_F2,
KEY_F3,
KEY_F4,
KEY_F5,
KEY_F6,
KEY_F7,
KEY_F8,
KEY_F9,
KEY_F10,
KEY_F11,
KEY_F12,
KEY_F13,
KEY_F14,
KEY_F15,
KEY_F16,
KEY_F17,
KEY_F18,
KEY_F19,
KEY_F20,
KEY_F21,
KEY_F22,
KEY_F23,
KEY_F24,
KEY_F25,
KEY_KP_0 = 320,
KEY_KP_1,
KEY_KP_2,
KEY_KP_3,
KEY_KP_4,
KEY_KP_5,
KEY_KP_6,
KEY_KP_7,
KEY_KP_8,
KEY_KP_9,
KEY_KP_DECIMAL,
KEY_KP_DIVIDE,
KEY_KP_MULTIPLY,
KEY_KP_SUBTRACT,
KEY_KP_ADD,
KEY_KP_ENTER,
KEY_KP_EQUAL,
KEY_LEFT_SHIFT,
KEY_LEFT_CONTROL,
KEY_LEFT_ALT,
KEY_LEFT_SUPER,
KEY_RIGHT_SHIFT,
KEY_RIGHT_CONTROL,
KEY_RIGHT_ALT,
KEY_RIGHT_SUPER,
KEY_MENU
};

enum KeyState
{
	DOWN,
	UP,
};

enum KeyMods
{
	SHIFT = 1,
	CONTORL = 2,
	ALT = 4,
	SPUER = 8,
	CAPS_LOCK = 16,
	NUM_LOCK = 32
};


class TemplateInputClass
{
public:
	virtual void callback(KeyType key, KeyState state, KeyMods mods) = 0;
};

using _InputCallBack = void(__stdcall*)(KeyType key, KeyState state, KeyMods mods);
using _InputCCallBack = void (TemplateInputClass::*)(KeyType key, KeyState state, KeyMods mods);

class Input
{
public:
	Input() = default;
	static bool IsKeyPress(KeyType key);
	static bool IsKeyDown(KeyType key);

	void AddClassCallback(_InputCCallBack callback, void* pThis);
	void AddCallback(_InputCallBack callback);

	static void InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
};