#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <vector>
#include <functional>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
private:
    static HINSTANCE hInstance;
    static int nCmdShow;

public:
    HWND hwnd;
    static int classCount;
    std::function<void()> onCreate;
    static void Init(HINSTANCE ins, int cmd)
    {
        hInstance = ins;
        nCmdShow = cmd;
        classCount = 0;
    }
    void Show(const wchar_t *windowName, int width, int height, int type, int ms = -1);
};

#endif
