@echo off
REM filepath: build_win.bat

REM Path to compiler, g++ for example
set COMPILER=g++

REM Check compiler
echo Checking for compiler at %COMPILER%...
if not exist "%COMPILER%" (
    echo FATAL: Cannot find any compiler at %COMPILER%.
    echo Set the COMPILER variable mannually (or ensure g++ is in your PATH).
    exit /b 1
)

REM source code
set SRC=src
set SOURCES=^
 %SRC%/main.cpp^
 %SRC%/game/board.cpp^
 %SRC%/game/logic.cpp^
 %SRC%/ui/display.cpp^
 %SRC%/game/AI.cpp^
 %SRC%/ui/console_windows.cpp

REM headers
set INCLUDE=-I%SRC%/game -I%SRC%/ui

REM compiler flags (for g++)
set FLAGS=-std=c++17 -O2 -Wall -Wextra

REM executable
set OUT=2048.exe

REM build executable
%COMPILER% %FLAGS% %INCLUDE% %SOURCES% -o %OUT%

if %errorlevel% neq 0 (
    echo FATAL: Compilation failed.
    echo Try to compile mannually.
    exit /b 2
) else (
    echo Executable built successfully at %OUT%.
)
