#pragma once
#include <wrl/client.h>
#include <dwrite.h>
#include <d2d1.h>
#include <dxgi1_2.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d2d1_1helper.h>
#include <assert.h>
#include <wincodec.h>
#include "vec.h"
using namespace Microsoft::WRL;
using namespace D2D1;
class D2dRender //
{
public:
	 


	~D2dRender();
	D2dRender& operator=(const D2dRender&) = delete;
	D2dRender(const D2dRender& )=delete;
	static D2dRender* Instance() {
		static D2dRender m_render;//静态变量只会初始化一次
		return &m_render;
	};

	
	
	bool Init(HWND hwnd);

	// 以下是一些封装的绘图函数，但Direct2d的绘图函数太多，所以就用到哪封装到哪吧，你也可以
	// 调用 Direct2dRender::GetDC 方法获取原始的设备上下文 ID2D1DeviceContext
	void BeginDraw();

	void Clear(const colorVec4<float>& color);

	void FillRoundedRect(const vec2<float>& pos, const vec2<float>& size, float radius, const colorVec4<float>& color);

	void DrawRect(const vec2<float>& pos, const vec2<float>& size, const colorVec4<float>& color, float strokeWidth = 1.0f);
	void FillRect(const vec2<float>& pos, const vec2<float>& size, ID2D1Brush* brush);

	void FillCircle(const vec2<float>& pos, float radius, const colorVec4<float>& color);
	void FillCircle(const vec2<float>& pos, float radius, ID2D1Brush* brush);

	void DrawLine(const vec2<float>& p1, const vec2<float>& p2, const colorVec4<float>& color, float strokeWidth = 1.0f);

	void DrawTextCenter(const std::wstring& text, const vec2<float>& pos, const vec2<float>& rect, const colorVec4<float>& color, float Textsize);
	void DrawTexti(const std::wstring& text, const vec2<float>& pos, const vec2<float>& rect, const colorVec4<float>& color, float Textsize);

	void DrawBitmap(ID2D1Bitmap1* bitmap, const vec2<float>& pos, const vec2<float>& size);

	void EndDraw();

	ID2D1DeviceContext* getD2dDeviceContext();
	ID2D1Bitmap1* getRenderTarget();
private:
	HWND hWnd;

	D2dRender();
	ComPtr<ID2D1SolidColorBrush>	m_Brush;

	ComPtr<ID2D1Factory1>			m_d2dFactory;
	ComPtr<ID2D1Device>			    m_d2dDevice;
	ComPtr<ID2D1DeviceContext>		m_d2dDeviceContext;
	ComPtr<ID2D1Bitmap1>			m_d2dTarget;

	ComPtr<ID3D11Device>			m_d3dDevice;
	ComPtr<ID3D11DeviceContext>	    m_d3dDeviceContext;
	ComPtr<ID3D11RenderTargetView>  m_d3dRenderTar;

	ComPtr<IDXGIFactory2>			m_dxgiFactory;
	ComPtr<IDXGIDevice1>			m_dxgiDevice;
	ComPtr<IDXGISwapChain1>			m_dxgiSwapChain;
	ComPtr<IDXGISurface1>			m_dxgiSurface;

	ComPtr<IDWriteFactory>			m_pDWriteFactory;
	ComPtr<IDWriteTextFormat>		m_pTextFormat;
	ComPtr<IDWriteTextLayout>		m_pTextLayout;

	



};

