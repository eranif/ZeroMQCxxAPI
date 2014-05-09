ZeroMQCxxAPI
============

A small wrapper around ZeroMQ C API using CMake and wxWidgets

Requirements
----

* wxWidgets installed and compiled
* **Windows only** MinGW / g++ Compiler
* wx-config in your path (this is required for **Windows** also!). For Windows, you can [download and install it from here][1]
* CMake 2.8 or later

Build
----

You can choose the compile the code using [CodeLite IDE][2] or from the command line

Building from the command line
----
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


  [1]: http://sourceforge.net/projects/codelite/files/Releases/codelite-5.3/wxwidgets-3.0-tdm-gcc-481-32-devel.exe/download
  [2]: http://codelite.org
