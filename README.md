# Seewk GUI v0.0.1

基于 Vulkan 的 C++ 图形化渲染框架

## 项目介绍

本项目为使用 C++ 调用 Vulkan 渲染后端来绘制图形化界面的桌面应用框架。该项目中采用与 `.NET C#` 的 `WinForm` 框架类似的结构。用户通过自定义类并继承框架中提供的 `Form` 基类，并重载基类的 `OnLoad()` 函数来初始化窗口。`main` 函数将有框架内部接管。用户需要自行写框架提供的入口函数的实现。

## 特性

-   使用现代化 C++ 的模块功能以防止宏污染和缩短编译时间
-   高性能以及小体积

### 待做事项 (后续的更新)

-   文本的渲染以及自动排版功能
-   自定义的 Shader 以及渲染管道
-   图片以及其他资产的打包
-   多平台支持

# 开始使用

## 技术栈

-   C++20 及以上版本  
    本项目中主要使用的 C++20 的新功能`模块`为亮点而不是传统的头文件。
-   Vulkan  
     近 10 年内的 Windows 电脑里应该会有 `vulkan-1.dll` 文件，因此可以不用单独安装 VulkanSDK 就可以进行开发，但如果有编辑着色器的需求，请自行安装 VulkanSDK 并使用 SDK 提供的 `glslangValidator` 工具来编译着色器。
    ### 使用到的核心库
    -   Vulkan: 提供开发用的 vulkan.hpp 头文件
    -   glfw: 窗口管理器
    -   stb: 图片的读取
    #### 以上库将会使用 vcpkg 来自动安装

## 环境搭建

### Windows 10/11

-   MSVC 2022 及以上版本
-   CMake 3.30 及以上版本
-   Ninja (可选)
-   vcpkg (最新版本即可)

#### 你也可以使用自动化的环境搭建工具 [Seewk Runner](https://github.com/WBhlietue/seewkRunner)。

使用该工具时请`不要`在安装 MSVC 时在 VisualStudio Installer 中`一起安装` vcpkg，可能会出现一些错误。

该工具会自动安装 CMake, Ninja, vcpkg 等工具，并在运行项目时自动配置 MSVC 的 `vcvarsall.bat` 文件和 `VCPKG_ROOT` 环境变量。

如果你不会安装 MSVC 也可以根据 [Seewk Runner](https://github.com/WBhlietue/seewkRunner) 的`README`文件中提供的步骤来安装

## 安装与构建

此教程将使用 [Seewk Runner](https://github.com/WBhlietue/seewkRunner) 工具提供的命令。你也可以直接调用 `cmake`, `ninja` 等命令进行构建和编译

1. 把项目克隆到本地

```bat
git clone https://github.com/WBhlietue/Seewk.git
```

2. 进入项目根目录并进行构建

```bat
seewk make
```

3. 进行编译并启动

```bat
seewk start
```

## 用法

- 在 `src` 目录中创建 `main.cpp` 文件并打开它。  
在此文件中导入框架的核心库

#### src/main.cpp

```cpp
//此处的头文件为测试中的文件。之后会改成模块并合并到 seewk 模块中。

#include <core/main/seewkObject.hpp>
#include <core/core.h>
import seewk;
```

- 定义一下两个函数作为程序的入口以及出口。

#### src/main.cpp

```cpp
void OnStart() // 程序开始时调用
{
}

void OnOver() // 程序结束时调用
{
}
```

- 创建自定义类并继承 `Form` 基类并重载 `OnLoad()` 函数

#### src/main.cpp

```cpp
class Form1 : public seewk::main::Form
{
  void OnLoad() override
  {
  }
}
```

此处的每个 `Form` 为一个窗口，你也可以通过创建多个继承于 `Form` 的子类来实现多窗口(该功能目前有 BUG，不建议尝试在)。

- 现在为 `Form1` 窗口中使用 `CreateObject()` 添加一个矩形

#### src/main.cpp

```cpp
  void OnLoad() override
  {
    CreateObject();
  }
```

也可以使用链式调用来直接初始化矩形, 这将在窗口中央绘画一个 500x500 的蓝色正方形。

#### src/main.cpp

```cpp
  void OnLoad() override
  {
    CreateObject()
      .SetPosition(Vec2(0, 0))
      .SetSize(Vec2(500, 500))
      .SetColor(Color(0, 0, 1, 1));
  }
```

也可以把引用存进变量里来初始化。

#### src/main.cpp

```cpp
  void OnLoad() override
  {
    SeewkObject& obj = CreateObject();
    obj.SetPosition(Vec2(0, 0));
    obj.SetSize(Vec2(500, 500));
    obj.SetColor(Color(0, 1, 1, 1));
  }
```

- 如果需要在此作用域以外使用该对象，可以将该对象以指针的形式存进类的成员函数中。

#### src/main.cpp

```cpp
class Form1 : public seewk::main::Form
{
  SeewkObject *obj = nullptr;
  void OnLoad() override
  {
    obj = &CreateObject()
      .SetPosition(Vec2(0, 0))
      .SetSize(Vec2(500, 500))
      .SetColor(Color(0, 0, 1, 1));
  }
}
```

- 要使用贴图需要在继承于 `Form` 的子类中重载 `PreLoad()` 函数并在这里加载贴图并存进成员函数中。并使用 UI 物件的 `SetTexture()` 来设置贴图

#### src/main.cpp

```cpp
class Form1 : public seewk::main::Form
{
  SeewkObject *obj = nullptr;
  int texture = -1;
  void PreLoad() override
  {
    texture = GetTexture("assets/moon.png");
  }
  void OnLoad() override
  {
    obj = &CreateObject()
      .SetPosition(Vec2(0, 0))
      .SetSize(Vec2(500, 500))
      .SetColor(Color(0, 0, 1, 1))
      .SetTexture(texture);
  }
}
```

- 如果需要循环请在继承于 `Form` 的子类里重载 `OnLoop()` 函数，此函数为每帧调用一次。

#### src/main.cpp

```cpp
class Form1 : public seewk::main::Form
{
  void OnLoop(float deltaTime) override
  { // 每帧调用一次，1 / deltaTime 的计算结果为目前的帧数
  }
}
```

- 然后你需要在之前写的 `OnStart()` 函数中创建此窗口

#### src/main.cpp

```cpp
void OnStart()
{
    seewk::WindowManager::CreateWindow<Form1>();
}
```

- 然后运行 `seewk start` 将会自动编译并运行该窗口。

## 进阶用法

- UI 物件还提供一下函数

```cpp
Vec2 GetPosition(); // 获得物件的位置
SeewkObject &SetPosition(Vec2 position); // 更改物件的位置
Vec2 GetSize(); // 获得物件的大小
SeewkObject &SetSize(Vec2 size) ; // 更改物件的大小
Color GetColor(); // 获得物件的颜色
SeewkObject &SetColor(Color c); // 更改物件的颜色
SeewkObject &SetTexture(int textureId); // 更改物件的贴图
int GetBorderRadius(); // 获得物件的圆角值
SeewkObject &SetBorderRadius(int r); // 更改物件的圆角值

// 一下函数为为物件设置可互动的功能
SeewkObject &SetMouseEnter(std::function<void()> f); // 当鼠标进入范围时调用
SeewkObject &SetMouseExit(std::function<void()> f); // 当鼠标出范围时调用
SeewkObject &SetMouseStay(std::function<void()> f); // 当鼠标在范围时一直调用
SeewkObject &SetMouseUp(std::function<void(int)> f); // 当松开鼠标按键时调用，参数为鼠标键的编号
SeewkObject &SetMouseDown(std::function<void(int)> f); // 当按下鼠标按键时调用，参数为鼠标键的编号
SeewkObject &SetClick(std::function<void(int)> f); // 当点击鼠标按键时调用，参数为鼠标键的编号
SeewkObject &SetDrag(std::function<void(int)> f); // 当使用鼠标拖拽时调用，参数为鼠标键的编号
```

- 使用以上函数可以实现以下范例，此范例为圆角会随时间变化而且可点击并拖拽的带贴图的矩形的完整代码。可直接复制并运行。

#### src/main.cpp

```cpp
#include <core/main/seewkObject.hpp>
#include <core/core.h>
import seewk;

class Form1 : public seewk::main::Form
{
  public:
  int border = 30;
  int borderSpeed = 1;
  SeewkObject *obj = nullptr;
  Vec2 objPosOffset;
  int texture = -1;

  void PreLoad() override
  {
    texture = GetTexture("assets/moon.png");
  }

  void OnLoad() override
  {
    obj = &CreateObject()
      .SetPosition(Vec2(0, 0))
      .SetSize(Vec2(500, 500))
      .SetColor(Color(1, 1, 1, 1))
      .SetBorderRadius(border)
      .SetClick([this](int button) { std::cout << "click\n";})
      .SetMouseDown([this](int button) 
        { this->objPosOffset = GetMousePosition() - this->obj->GetPosition(); })
      .SetDrag([this](int button)
        {
          Vec2 mousePosition = GetMousePosition();
          this->obj->SetPosition(mousePosition - this->objPosOffset); 
        })
      .SetTexture(texture);
  }
  void OnLoop(float deltaTime) override
  {
    border += borderSpeed;
    if (border < 10 || border > 100)
    {
      borderSpeed *= -1;
    }
    obj->SetBorderRadius(border);
  }
};

void OnStart()
{
  seewk::WindowManager::CreateWindow<Form1>();
}

void OnOver()
{
  std::cout << "over\n";
}
```