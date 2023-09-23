#include "D2dApp.h"


D2dApp::D2dApp():
    hWnd(NULL),
    FPS(0),
    dt(0)
{

}

D2dApp::~D2dApp()
{
}

HRESULT D2dApp::init()
{

   HRESULT hr= BuildWindow();
   
   if (SUCCEEDED(hr))
   {
       m_render = D2dRender::Instance();
       if (!m_render->Init(hWnd)) hr = E_FAIL;

   }
   OnUserInit();//初始化用户
   m_cp1 = std::chrono::system_clock::now();
   m_cp2 = std::chrono::system_clock::now();
    return hr;
}

void D2dApp::Run()
{
    std::thread t(&D2dApp::Render, this);
    t.detach();
}

HRESULT D2dApp::BuildWindow()
{
    HRESULT hr= E_FAIL;
   
    // 注册窗口类
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = D2dApp::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = L"D2DApp";

    RegisterClassEx(&wcex);

    hWnd = CreateWindow(
        L"D2DApp",
        L"Direct2D demo application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        NULL,
        NULL,
        HINST_THISCOMPONENT,
        this);

    if (hWnd)
    {  
        float dpi = GetDpiForWindow(hWnd);

        SetWindowPos(
        hWnd,
        NULL,
        NULL,
        NULL,
        static_cast<int>(GameData::screen_size.x),
        static_cast<int>(GameData::screen_size.y),
        SWP_NOMOVE);
        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
        hr = S_OK;
    }


    return hr;
}

void D2dApp::MessageLoop()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void D2dApp::RenderLoop()
{
 

  //  OnUserUpdate( );

}
bool D2dApp::OnUserInit()
{
    return true;
}

void D2dApp::OnUserUpdate(float dt)
{


}

void D2dApp::Render()
{

 
    while (1)
    {
        UpdateCoreDate();
        OnUserUpdate(dt);
 
    }



}

void D2dApp::UpdateCoreDate()
{
    static float FrameTimer = 0.0f;
    static uint32_t FrameCount = 0;

    // 更新帧间隔
    m_cp1 = std::chrono::system_clock::now();
    std::chrono::duration<float> t = m_cp1 - m_cp2;
    m_cp2 = m_cp1;
    dt = t.count();

    // 更新FPS
    FrameTimer += dt;
    FrameCount++;
    if (FrameTimer >= 1.0f)
    {
       FrameTimer -= 1.0f;
       FPS = FrameCount;
       FrameCount = 0;
       
    }
    UserInput::Updata();

}

LRESULT D2dApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        D2dApp* pApp = (D2dApp*)pcs->lpCreateParams;
        ::SetWindowLongPtrW(
            hWnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pApp)
        );
        return 1;
    }
    else
    {
 
        D2dApp* pApp = reinterpret_cast<D2dApp*>(
            ::GetWindowLongPtrW(
                hWnd,
                GWLP_USERDATA
            ));

        switch (message)
        {
            case WM_KEYDOWN:
                UserInput::UpdataKeyStatus(static_cast<uint32_t>(wParam), true);
            return 1;
            case WM_KEYUP:
                UserInput::UpdataKeyStatus(static_cast<uint32_t>(wParam), false);
            return 1;


            case WM_PAINT:
           
                return 1;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 1;





        }



    }
    

    return DefWindowProc(hWnd, message, wParam,lParam);
}

