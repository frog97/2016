// LinearAlgebra.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LinearAlgebra.h"
//_20180519_jintaeks
#include "KVectorUtil.h"
#include <MMSystem.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <complex>
#include <valarray>

#pragma comment(lib,"winmm.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// _20180519_jintaeks
HWND    g_hwnd = NULL;
HDC     g_hdc = 0;
HBITMAP g_hBitmap = 0;
RECT    g_clientRect;
const double PI = 3.141592653589793238460;
const double XSTEP_SIZE = 2 * PI / 400;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void                Initialize();
void                Finalize();
void                OnSize();
void                OnPaint();
void                OnIdle(float fElapsedTime_);
void fft(CArray& x);
void ifft(CArray& x);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LINEARALGEBRA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LINEARALGEBRA));

    Initialize();

    DWORD dwOldTime = ::timeGetTime();

    MSG msg;

    // Main message loop:
    while (true)
    {
        ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        const DWORD dwNewTime = ::timeGetTime();
        const BOOL bIsTranslateMessage = TranslateAccelerator(msg.hwnd, hAccelTable, &msg);
        if (!bIsTranslateMessage)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }//if

        OnIdle(float(dwNewTime - dwOldTime) / 1000.f);
        Sleep(10);

        dwOldTime = dwNewTime;

        if (msg.message == WM_QUIT)
        {
            break;
        }//if
    }//while

    Finalize();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LINEARALGEBRA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LINEARALGEBRA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // _20180519_jintaeks
   g_hwnd = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//_20180519_jintaeks
void OnPaint(HDC hdc)
{
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            // _20180519_jintaeks
            OnPaint( hdc );
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        OnSize();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Initialize()
{
}//Initialize()

void Finalize()
{
    if (g_hdc != 0) {
        DeleteDC(g_hdc);
        g_hdc = 0;
    }//if
    if (g_hBitmap != 0) {
        DeleteObject(g_hBitmap);
        g_hBitmap = 0;
    }//if
}//Finalize()

void OnSize()
{
    Finalize();

    ::GetClientRect(g_hwnd, &g_clientRect);
    const int iWidth = g_clientRect.right - g_clientRect.left + 1;
    const int iHeight = g_clientRect.bottom - g_clientRect.top + 1;

    KVector2 origin;
    origin.x = 32;// iWidth / 2.0f;
    origin.y = iHeight / 2.0f;
    KVectorUtil::g_screenCoordinate.SetInfo(KVector2(100, 0), KVector2(0, -100), origin);

    HDC hdc = ::GetDC(g_hwnd);
    g_hdc = CreateCompatibleDC(hdc);
    g_hBitmap = CreateCompatibleBitmap(hdc, iWidth, iHeight);
    SelectObject(g_hdc, g_hBitmap);
}//OnSize()


double SignalFunction(double t)
{
    // A = 0.5, frequency fc = 3Hz and phase ϕ = π / 6 radians(or 30∘)
    //0.5 * cos(2.0 * M_PI * 3.0 * t + M_PI / 6.0)
    //return 0.5 * cos(2.0 * M_PI * 3.0 * t + M_PI / 6.0);

    //return cos(2.0 * M_PI * t) + 0.5 * cos(2.0 * M_PI * 4 * t + M_PI / 4.0) + cos(2.0 * M_PI * 8 * t);
    return cos(2.0 * M_PI * t) + 0.5 * cos(2.0 * M_PI * 4 * t + M_PI / 4.0);
    //return cos(2.0 * M_PI * t);
}

void DrawInputSignal()
{
    double oldY = SignalFunction(0);
    double oldX = 0;
    double x = 0;
    for (int i = 1; i < 256; ++i)
    {
        x += XSTEP_SIZE;
        double y = SignalFunction(x);
        KVectorUtil::DrawLine(g_hdc, KVector2(oldX, oldY), KVector2((double)x, (double)y), 2, PS_SOLID, RGB(0, 0, 0));
        oldX = x;
        oldY = y;
    }
}

void OnRender( HDC hdc, float fElapsedTime_ )
{
    KVectorUtil::DrawGrid(g_hdc, 10, 10);
    KVectorUtil::DrawAxis(g_hdc, 10, 10);
    DrawInputSignal();

    {
        //KScreenCoordinate oldCoord = KVectorUtil::g_screenCoordinate;
        //KScreenCoordinate newCoord = oldCoord;
        //newCoord.origin.y += 200;
        //KVectorUtil::SetScreenCoordinate( newCoord );

        const int DATA_SIZE = 256;
        Complex test[256];
        // fill test signal data
        double x = 0;
        double y;
        for (int i = 0; i < DATA_SIZE; ++i)
        {
            test[i] = Complex(SignalFunction(x));
            x += XSTEP_SIZE;
        }
        CArray data(test, DATA_SIZE );

        // forward fft
        fft(data);

        const double AMPLITUDE_MULTIPLIER = 0.02;
        double re = data[0].real();
        double im = data[0].imag();
        double amplitude = sqrt(re*re + im*im);
        double oldX = 0;
        double oldY = amplitude * AMPLITUDE_MULTIPLIER;
        x = oldX;
        y = oldY;
        for (int i = 1; i < DATA_SIZE/2; ++i)
        {
            x += XSTEP_SIZE * 2;
            re = data[i].real();
            im = data[i].imag();
            amplitude = sqrt(re*re + im*im);
            y = amplitude * AMPLITUDE_MULTIPLIER;

            //std::cout << data[i] << std::endl;
            KVectorUtil::DrawLine(g_hdc, KVector2(oldX, oldY), KVector2((double)x, (double)y), 2, PS_SOLID, RGB(255, 0, 0));
            oldX = x;
            oldY = y;
        }
    }
}

void OnIdle(float fElapsedTime_)
{
    const int iWidth = g_clientRect.right - g_clientRect.left + 1;
    const int iHeight = g_clientRect.bottom - g_clientRect.top + 1;

    HDC hdc = ::GetDC(g_hwnd);

    HBRUSH brush;
    brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(g_hdc, brush);
    Rectangle(g_hdc, 0, 0, iWidth, iHeight);

    {
        OnRender(g_hdc, fElapsedTime_);
    }

    BitBlt(hdc, 0, 0, iWidth, iHeight, g_hdc, 0, 0, SRCCOPY);
    DeleteObject(brush);

    ::ReleaseDC(g_hwnd, hdc);
}//OnIdle()

// Cooley?밫ukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N / 2, 2)];
    CArray  odd = x[std::slice(1, N / 2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N / 2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    fft(x);

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}
