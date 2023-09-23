#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>
#include "Render.h"
#include <thread>
#include <string>
#include "UserInput.h"
#include "Resource.h"
#include "GameData.h"
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
template<class Interface>
inline void
SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif


class D2dApp
{
public :
	D2dApp();
	virtual ~D2dApp();
    HRESULT init();
	void Run();
	void MessageLoop();
	void RenderLoop();
	virtual bool OnUserInit();//用户自定义初始化
	virtual void OnUserUpdate(float deltaTime);//用户自定义渲染
	void Render();
	void UpdateCoreDate();
protected:
	HWND hWnd;//窗口句柄
	HRESULT BuildWindow();
	
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	
	D2dRender* m_render;//完成所有渲染任务


	UINT FPS;
	std::chrono::system_clock::time_point m_cp1, m_cp2;
	float dt;//游戏真实时间


	
};

