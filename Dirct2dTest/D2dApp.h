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
	virtual bool OnUserInit();//�û��Զ����ʼ��
	virtual void OnUserUpdate(float deltaTime);//�û��Զ�����Ⱦ
	void Render();
	void UpdateCoreDate();
protected:
	HWND hWnd;//���ھ��
	HRESULT BuildWindow();
	
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	
	D2dRender* m_render;//���������Ⱦ����


	UINT FPS;
	std::chrono::system_clock::time_point m_cp1, m_cp2;
	float dt;//��Ϸ��ʵʱ��


	
};

