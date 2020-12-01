# SciPP - A simple C++ Scientific Library


## Introduction

SciPP (pronounced "cpp") is a little C++ scientific library I coded to help me during my computer science studies.
This library, a bit messy, implements all kind of tools usually needed to do applied mathematics or computer sciences, but that are not in the standard library.
These tools are, for example: Big Integers, Matrices, Vectors, Fourier Transforms, Quaternions...


## Including SciPP in your projects

For the moment, SciPP does not depend on any other library, but in a near future, a plot module may be added and might require some additional dependencies.

The git repository contains a Makefile and a Visual Studio Solution to help you include SciPP in your own projects. First, start by cloning the repository.

```bash
git clone https://github.com/Reiex/SciPP.git
cd SciPP
```

You will need compiled version of the library, you can either compile it yourself or directly use the compiled version in the folder `lib`.
I suggest you recompile the version you need, as it is easy and more reliable.

---

### Compile SciPP on Linux

A Makefile is available with a target for everything you need:
* Compiling SciPP: `make SciPP`
* Compiling SciPP tests (requires Google Tests and Posix Threads): `make tests`
* Compiling SciPP examples: `make examples`
* Cleaning everything and recompiling everything: `make` or `make all`

The executables eventually created are stored in `build`. The compiled version of SciPP is stored in `lib` under `libSciPP.so`.

### Compile SciPP on Windows

A file `SciPP.sln` at the root of the repository will allow you to compile directly SciPP into `lib` as `SciPP.lib`.

This Visual Studio solution contains three projects: SciPP, SciPPTests, SciPPExamples.
Any project you run will compile SciPP, but if you want to test it, just select the right project to run.

---

Once it is compiled, you just need to link SciPP with your project as you would do with any other library, the SciPP headers are in the folder `include` and you can get the compiled library in `lib`.


## Using SciPP

You can include SciPP in your projects with a single line:

```cpp
#include <SciPP/SciPP.hpp>
```

A documentation can be generated using the comments of the code and doxygen with the command:

```bash
make docs
```
