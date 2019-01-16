@echo off

if not exist "artifacts" mkdir artifacts

cd artifacts

if not exist "win32" mkdir win32

cd win32

rem Use this line to build with logging enabled
rem cmake ..\.. -DENABLE_LOGGING=ON -G "Visual Studio 15 2017" || exit /b 1
cmake ..\.. -G "Visual Studio 15 2017" || exit /b 1

msbuild /nologo /verbosity:quiet /p:Configuration=Release binarily.sln || exit /b 1

test\Release\tests.exe || exit /b 1

cd ..\..
