# HatchitCore

[![Build Status](https://travis-ci.org/thirddegree/HatchitCore.svg?branch=master)](https://travis-ci.org/thirddegree/HatchitCore)
[![Documentation](https://codedocs.xyz/thirddegree/HatchitCore.svg)](https://codedocs.xyz/thirddegree/HatchitCore/)
[![Join the chat at https://gitter.im/thirddegree/HatchitDiscussion](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/thirddegree/HatchitDiscussion)


The core utilities and OS interfacing library for [Hatchit](https://github.com/thirddegree/Hatchit)   

---

### Contributing

If you have an issue with Hatchit specific to OS level utility put it on this repo. This includes routines such as opening files and threadable file structures.

If you would like to make a contribution please make a fork and submit a pull request.

### Build instructions

#### Linux

Simply install CMake and a C++ compiler. Then follow these commands:

```
mkdir build
cd build
cmake ..
make
```

#### Windows

On Window's you'll just need CMake and a C++ compiler as well. However,
when selecting the generator in CMake, make sure to use the 64-bit target!
(E.g. "Visual Studio 14 2015 Win64")

### Building tests

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
