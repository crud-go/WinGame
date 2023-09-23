#include "Render.h"

D2dRender::D2dRender():
hWnd(NULL)
{
	

}

D2dRender::~D2dRender()
{

}

bool D2dRender::Init(HWND hwnd)
{
	HRESULT hr  = S_OK;
	this->hWnd = hwnd;
	hr=CoInitialize(NULL);
	assert(SUCCEEDED(hr));
//创建D2D工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory1), (void**)&m_d2dFactory);
	assert(SUCCEEDED(hr));

UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

// This array defines the set of DirectX hardware feature levels this app  supports.
// The ordering is important and you should  preserve it.
// Don't forget to declare your app's minimum required feature level in its
// description.  All apps are assumed to support 9.1 unless otherwise stated.
D3D_FEATURE_LEVEL featureLevels[] =
{
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1
};

// 创建D3D设备
//ComPtr<ID3D11Device> device;
//ComPtr<ID3D11DeviceContext> context;

D3D_FEATURE_LEVEL m_featureLevel;

hr=D3D11CreateDevice(
	nullptr,                    // specify null to use the default adapter
	D3D_DRIVER_TYPE_HARDWARE,
	0,
	creationFlags,              // optionally set debug and Direct2D compatibility flags
	featureLevels,              // list of feature levels this app can support
	ARRAYSIZE(featureLevels),   // number of possible feature levels
	D3D11_SDK_VERSION,
	&m_d3dDevice,                    // returns the Direct3D device created
	&m_featureLevel,            // returns feature level of device created
	&m_d3dDeviceContext                    // returns the device immediate context
);
assert(SUCCEEDED(hr));

//IDXGIDevice1* dxgiDevice=NULL;

// Obtain the underlying DXGI device of the Direct3D11 device.

m_d3dDevice.As(&m_dxgiDevice);

// Obtain the Direct2D device for 2-D rendering.

hr=m_d2dFactory->CreateDevice(m_dxgiDevice.Get(), &m_d2dDevice);
assert(SUCCEEDED(hr));

// Get Direct2D device's corresponding device context object.

	hr=m_d2dDevice->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&m_d2dDeviceContext
	);
	assert(SUCCEEDED(hr));

	// Allocate a descriptor.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;                           // use automatic sizing
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
	swapChainDesc.Flags = 0;

	// Identify the physical adapter (GPU or card) this device is runs on.
	ComPtr<IDXGIAdapter> dxgiAdapter;

	hr=m_dxgiDevice->GetAdapter(&dxgiAdapter);
	assert(SUCCEEDED(hr));

	// Get the factory object that created the DXGI device.
	//ComPtr<IDXGIFactory2> dxgiFactory;

	hr=dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory));
	assert(SUCCEEDED(hr));

	UINT dpi = GetDpiForWindow(hWnd);
	// Get the final swap chain for this window from the DXGI factory.

	hr = m_dxgiFactory->CreateSwapChainForHwnd(
		 m_d3dDevice.Get(),
		this->hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&m_dxgiSwapChain
	);
	assert(SUCCEEDED(hr));

	// Ensure that DXGI doesn't queue more than one frame at a time.

	hr=m_dxgiDevice->SetMaximumFrameLatency(1);
	assert(SUCCEEDED(hr));

	// Get the backbuffer for this window which is be the final 3D render target.
	//ID3D11Texture2D* backBuffer;
	
	//m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));


	// Now we set up the Direct2D render target bitmap linked to the swapchain. 
	// Whenever we render to this bitmap, it is directly rendered to the 
	// swap chain associated with the window.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpi,
			dpi
		);

	// Direct2D needs the dxgi version of the backbuffer surface pointer.
	//ComPtr<IDXGISurface> dxgiBackBuffer;

	hr=m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&m_dxgiSurface));

	assert(SUCCEEDED(hr));

	// Get a D2D surface from the DXGI back buffer to use as the D2D render target.

	hr=m_d2dDeviceContext->CreateBitmapFromDxgiSurface(
		m_dxgiSurface.Get(),
		&bitmapProperties,
		&m_d2dTarget
	);
	assert(SUCCEEDED(hr));

	// Now we can set the Direct2D render target.
	m_d2dDeviceContext->SetTarget(m_d2dTarget.Get());

	hr=m_d2dDeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_Brush);
	assert(SUCCEEDED(hr));
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		&m_pDWriteFactory);

	assert(SUCCEEDED(hr));



	m_d2dDeviceContext->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	return true;
}

void D2dRender::BeginDraw()
{

	m_d2dDeviceContext->BeginDraw();
}

void D2dRender::Clear(const colorVec4<float>& color)
{
	
	m_d2dDeviceContext->Clear(D2D1::ColorF(color.r, color.g, color.b, color.a));

}

void D2dRender::FillRoundedRect(const vec2<float>& pos, const vec2<float>& size, float radius, const colorVec4<float>& color)
{
	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	this->m_d2dDeviceContext->FillRoundedRectangle(
		D2D1::RoundedRect(D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y), radius, radius),
		m_Brush.Get());
}

void D2dRender::DrawRect(const vec2<float>& pos, const vec2<float>& size, const colorVec4<float>& color, float strokeWidth)
{
	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	this->m_d2dDeviceContext->DrawRectangle(
		D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y),
		m_Brush.Get(), strokeWidth);

}

void D2dRender::FillRect(const vec2<float>& pos, const vec2<float>& size, ID2D1Brush* brush)
{
	this->m_d2dDeviceContext->FillRectangle(
		D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y),
		brush);

}

void D2dRender::FillCircle(const vec2<float>& pos, float radius, const colorVec4<float>& color)
{
	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	this->m_d2dDeviceContext->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), radius, radius),
		m_Brush.Get());

}

void D2dRender::FillCircle(const vec2<float>& pos, float radius, ID2D1Brush* brush)
{
	this->m_d2dDeviceContext->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), radius, radius),
		brush);


}

void D2dRender::DrawLine(const vec2<float>& p1, const vec2<float>& p2, const colorVec4<float>& color, float strokeWidth)
{
	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	this->m_d2dDeviceContext->DrawLine(
		D2D1::Point2F(p1.x, p1.y),
		D2D1::Point2F(p2.x, p2.y),
		m_Brush.Get(),
		strokeWidth);
}

void D2dRender::DrawTextCenter(const std::wstring& text, const vec2<float>& pos, const vec2<float>& rect, const colorVec4<float>& color, float Textsize)
{
	HRESULT hr  = S_OK;

	if (Textsize <= 0) return;

	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	if (FAILED(hr)) return;

	hr  = m_pDWriteFactory->CreateTextFormat(
		L"微软雅黑",
		NULL,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		Textsize,
		L"en-us",
		&this->m_pTextFormat
	);
	if (FAILED(hr)) return;
	

	hr =  m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if (FAILED(hr)) return;
	hr =  m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	if (FAILED(hr)) return;

	hr =  this->m_pDWriteFactory->CreateTextLayout(
		text.c_str(),
		(UINT32)text.length(),
		m_pTextFormat.Get(),
		rect.x, 
		rect.y,
		&m_pTextLayout
	);
	if (FAILED(hr)) return;

	this->m_d2dDeviceContext->DrawTextLayout({ pos.x, pos.y }, m_pTextLayout.Get(), m_Brush.Get());
}

void D2dRender::DrawTexti(const std::wstring& text, const vec2<float>& pos, const vec2<float>& rect, const colorVec4<float>& color, float Textsize)
{
	HRESULT hr  = S_OK;

	if (Textsize <= 0) return;

	this->m_Brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));

	if (FAILED(hr)) return;

	hr  = this->m_pDWriteFactory->CreateTextFormat(
		L"微软雅黑",
		NULL,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		Textsize,
		L"en-us",
		&this->m_pTextFormat
	);
	if (FAILED(hr)) return;

	hr  = this->m_pDWriteFactory->CreateTextLayout(
		text.c_str(),
		(UINT32)text.length(),
		this->m_pTextFormat.Get(),
		rect.x, rect.y,
		&this->m_pTextLayout
	);
	if (FAILED(hr)) return;

	this->m_d2dDeviceContext->DrawTextLayout({ pos.x, pos.y }, m_pTextLayout.Get(), m_Brush.Get());

}

void D2dRender::DrawBitmap(ID2D1Bitmap1* bitmap, const vec2<float>& pos, const vec2<float>& size)
{

	m_d2dDeviceContext->DrawBitmap(bitmap, D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y), 1.0f, D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

}

void D2dRender::EndDraw()
{

	HRESULT hr;

	

	hr  = this->m_d2dDeviceContext->EndDraw();
	hr = this->m_dxgiSwapChain->Present(1, 0);




}

ID2D1DeviceContext* D2dRender::getD2dDeviceContext()
{
	return m_d2dDeviceContext.Get();
}

ID2D1Bitmap1* D2dRender::getRenderTarget()
{
	return m_d2dTarget.Get();
}


