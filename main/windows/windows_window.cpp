#define WIN32_LEAN_AND_MEAN
#define UNICODE

#include <windows.h>
#include "windows_window.h"

HINSTANCE Window::hInstance = nullptr;
int Window::classCount = 0;
int Window::nCmdShow = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_TIMER:
        break;
    case WM_COMMAND:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void Window::Show(const wchar_t *windowName, int width, int height, int type, int ms)
{
    std::wstring className = L"WindowClass" + std::to_wstring(++classCount);
    const wchar_t *CLASS_NAME = className.c_str();
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, CLASS_NAME, windowName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, NULL);

    if (!hwnd)
        return;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
    ShowWindow(hwnd, nCmdShow);
    onCreate();
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}