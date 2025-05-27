#include "windows_window.h"
#include <main.h>
#include "nlohmann/json.hpp"
#include <fstream>
#include <core/paint.h>

void UseConsole()
{
    AllocConsole();
    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stderr);
}

std::wstring StringToWString(const std::string &str)
{
    if (str.empty())
        return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UseConsole(); // removeThis

    Window::Init(hInstance, nCmdShow);
    Window window;
    std::ifstream file("./UI/pages/" +mainPage +".json");
    nlohmann::json json;
    file >> json;

    window.onCreate = [&window, &json]()
    {
        Paint(json["items"]);
        Start_Main();
    };
    std::string name = json["name"];
    window.Show(StringToWString(name).c_str(), json["width"], json["height"], WS_POPUP, 16);
    return 0;
}
