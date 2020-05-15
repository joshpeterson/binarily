![Binarily Logo](images/binarily-with-name.png)

[![Build Status](https://travis-ci.com/joshpeterson/binarily.svg?branch=master)](https://travis-ci.com/joshpeterson/binarily)

# Binarily

[Binarily](https://joshpeterson.github.io/binarily) is a website to view and inspect binary files.

It is written in C++ (with some JavaScript for the GUI), and compiles with
Emscripten, GCC, and Clang on Linux.

## Building

Binarily builds on Linux, and requires CMake, Ninja, and a C++ compiler to be
installed.

```
git clone git@github.com:joshpeterson/binarily.git --recursive
./build
```

