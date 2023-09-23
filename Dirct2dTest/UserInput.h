#pragma once
#define UINT unsigned int
struct KeyStatus
{
	bool isPress = false;	// 是否按下
	bool isHold = false;	// 是否按着
	bool isRelease = false;	// 是否释放
};
class UserInput
{
public:

	enum Key
	{
		LBUTTON = 0x01,
		RBUTTON,
		CANCEL,
		MBUTTON,
		SBUTTON1,
		SBUTTON2,
		BACK = 0x08,
		TAB,
		CLEAR = 0x0C,
		RETURN,
		SHIFT = 0x10,
		CONTROL,
		// VK_MENU ...
		SPACE = 0x20,
		A = 0x41,
		B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z

	};


	static void UpdataKeyStatus(UINT key, bool status);
	static void Updata();
	static KeyStatus* GetKeyStatus(Key key);

	// 按键的状态
	static bool m_KeyNewState[256];
	static bool m_KeyOldState[256];
	static KeyStatus m_KeyboardState[256];
};

