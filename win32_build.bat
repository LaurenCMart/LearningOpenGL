@echo off

rem Variables to set
set RELEASE=false

rem Setup Visual Studio 2015.
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

rem Warnings to ignore.
set COMMON_WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129 -wd4201 -wd4577 -wd4244 -wd4623 -wd4619 -wd4774 -wd4101 -wd4191 -wd4255 -wd4204 -wd4306

rem Debug/Release
set DEBUG_COMMON_COMPILER_FLAGS=-nologo -MDd -Gm- -GR- -EHsc- -Od -Oi %COMMON_WARNINGS% -DINTERNAL=1 -FC -Zi -GS- -Gs9999999
set RELEASE_COMMON_COMPILER_FLAGS=-nologo -MD -fp:fast -Gm- -GR- -EHa- -O2 -Oi %COMMON_WARNINGS% -DINTERNAL=0 -FC -Zi -GS- -Gs9999999

rem Add new files here. The format is: "../src/<filename>.cpp"
set FILES="../src/main.cpp"

IF NOT EXIST "build" mkdir "build"
pushd "build"
if "%RELEASE%"=="true" (
    cl -Fegame %RELEASE_COMMON_COMPILER_FLAGS% -Wall %FILES% -link -subsystem:console,5.2 kernel32.lib glew32.lib glfw3dll.lib opengl32.lib
) else (
    cl -Fegame %DEBUG_COMMON_COMPILER_FLAGS% -Wall %FILES% -link -subsystem:console,5.2 kernel32.lib glew32.lib glfw3dll.lib opengl32.lib
)
popd