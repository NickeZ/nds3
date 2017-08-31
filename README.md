# NDS v3

## Introduction

NDS (Nominal Device Support) is a library that allows to write device supports
for a variety of control systems (CS) by hiding the details of the chosen CS
and focusing on device functionalities.

NDS provides the following features:

- organizes your device in a tree-like structure, containing one or more
  devices, channels, attributes (PVs), state machine, etc.
- provides the data pull mode (passive scanning on EPICS, polling on Tango) and
  the push mode (Interrupt on EPICS, push on Tango)
- your code uses standard C++ types and Unix EPOCH timing to communicate with
  the library
- on EPICS there is no need to supply separate db files (but you still can if
  you want)
- supplies an hierarchical state machine
- supplies a specialized data acquisition module
- guaranteed binary compatibility between minor versions allow to easily
  upgrade existing installations without recompiling the device support

[![Build Status](https://travis-ci.org/Cosylab/nds3.svg?branch=master)](https://travis-ci.org/Cosylab/nds3)

## Documentation

- [Online Reference](https://cosylab.github.io/nds3/)
- Build doxygen reference with `make doc`. Requires doxygen and latex. The
  generated documentation is then found at `doc/api/html/index.html` and
  `doc/api/hlatex/refman.pdf`.

## Developer Dependencies

* CMake 2.8.8+
* GCC >= 4.8.1
* GCC >= 4.9 is recommended because of [GCC 57869](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=57869).
* clang-format >= 3.9 is recommended to correctly format the code.

## Package Installation

Packages are not available yet.

## Manual Installation

### Using cmake

```
mkdir build
cd build
cmake ../CMake
make
sudo make install
```

### Build with optimizations

```
mkdir build
cd build
cmake ../CMake -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

### Using make

```
make
sudo make install
```

### List configure options

```
$ cmake -LH ../CMake/
...
// Build as shared library
BUILD_SHARED_LIBS:BOOL=ON

// Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.
CMAKE_BUILD_TYPE:STRING=Debug

// Install path prefix, prepended onto install directories.
CMAKE_INSTALL_PREFIX:PATH=/usr/local
```

## Run unit tests

- Build NDS3 with CMake
- Build and run tests
    ```
    mkdir tests/build
    cd tests/build
    cmake ../CMake -DLIBRARY_LOCATION=../../build
    make
    ./nds3tests
    ```
## Build example drivers

- Build NDS3 with CMake
- Build examples
    ```
    mkdir doc/examples/build
    cd doc/examples/build
    cmake ../CMake -DLIBRARY_LOCATION=../../../build
    make
    sudo make install
    ```
