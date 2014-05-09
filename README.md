ZeroMQCxxAPI
============

A small wrapper around ZeroMQ C API using CMake and wxWidgets

Requirements
============

* wxWidgets installed and compiled
* wx-config in your path (this is required for Windows also!)
* CMake 2.8 or later

Build
=====

* A workspace is provided for CodeLite IDE
* From command line:
  
Windows / MinGW:

```
  mkdir build-debug
  cd build-debug
  cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Debug
  mingw32-make -j8
```

Linux:
```
  mkdir build-debug
  cd build-debug
  cmake .. -DCMAKE_BUILD_TYPE=Debug
  make -j8
```

