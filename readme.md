# 2048 重构

一个基于命令行的 2048 游戏实现，使用现代 C++ 重构原有 C 语言代码。

## 功能特点

- 支持多种 AI 策略，并可由用户自行拓展；
- 跨平台（Windows/Unix-like 系统）支持；
- 基于命令行的用户界面；
- 模块化设计。

## 项目结构

```bash
src/                        # 源代码目录
├── main.cpp                # 程序入口
├── game/                   # 游戏核心逻辑
│   ├── board.h/cpp         # 游戏棋盘
│   ├── logic.h/cpp         # 游戏主逻辑
│   ├── AI.h/cpp            # AI 策略实现
│   └── AI_TMP.h            # AI 模板元编程
└── ui/                     # 用户界面
    ├── console.h           # 控制台接口
    ├── console_unix.cpp    # Unix 平台实现
    ├── console_windows.cpp # Windows 平台实现
    └── display.h/cpp       # 显示逻辑
```

## 编译要求

- CMake 3.10 或更高版本
- 支持 C++17 的编译器
- 在 macOS Sonoma (Apple M2)、Windows 10、Ubuntu 22.04.4 LTS 上均测试通过。Windows 系统需要额外的编译步骤。

## 构建步骤

推荐 CMake 构建编译。

```bash

mkdir build && cd build
cmake ..
make
./2048
```

## AI 策略

游戏支持多种 AI 策略：

1. Corner AI：优先向左上角集中数字
2. Swing AI：在垂直和水平方向间交替移动
3. Swirl AI：按固定顺序循环移动
4. Random AI：随机选择移动方向

可以通过继承 `src/AI.h` 中的 `AIBase` 类实现用户自定义策略。

## 玩家控制方式

- W/A/S/D：上/左/下/右移动
- Q：退出游戏

## 技术特点

- 使用模板元编程实现 AI 类型管理；
- RAII 资源管理；
- 跨平台控制台操作抽象；
- 现代 C++ 特性的运用。

## 构建系统

使用 CMake 构建系统，支持：

- 自动检测平台；
- 条件编译；
- 头文件依赖管理；
- 可见性控制。

## 许可证

MIT License

Copyright (c) 2025 qwq automaton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
