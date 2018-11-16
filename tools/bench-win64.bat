@echo off
tools\build-win64-release.bat
pushd artifacts\win64\Release\bench
bench %*
popd
