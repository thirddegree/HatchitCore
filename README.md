# HatchitCore

Core Utilities library for Hatchit 3D Game Engine   

[![Build Status](https://travis-ci.org/thirddegree/HatchitCore.svg?branch=master)](https://travis-ci.org/thirddegree/HatchitCore)

## Build instructions

### Linux

Simply install CMake and a C++ compiler. Then follow these commands:

```
mkdir build
cd build
cmake ..
make
```

### Windows

On Window's you'll just need CMake and a C++ compiler as well. However,
when selecting the generator in CMake, make sure to use the 64-bit target!
(E.g. "Visual Studio 14 2015 Win64")

## Building tests

Building tests works best on Linux. Travis CI is used to automate tests whenever
you push to the repo.

The tests can be run manually with

```
mkdir build
cd build
cmake .. -DBUILD_TEST=TRUE
make
ctest -VV
```
