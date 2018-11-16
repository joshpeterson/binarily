@echo off
tools\build-win32-release.bat
pushd artifacts\win32\Release\bench
bench %*
popd
