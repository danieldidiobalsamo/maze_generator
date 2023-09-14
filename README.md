# About

This app consists in a maze generator and solver taking advantage of web assembly : the C++ backend is imported from Vue.js frontend as a javascript module, using Emscripten.

The following algorithms are implemented :
- solvers: A*, Dijkstra
- generators: Backtracking, Hunt and Kill

![image info](./img/example.png)

# How to launch

The following dependencies must be installed:
- CMake
- ![Emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended)
- clang (needed for emscripten)
- node.js
- (optional) Boost.test to launch unit tests

Then just launch this script:
~~~
./launch_dev.sh
~~~

Compile and launch unit tests without the http server :
~~~
./launch_dev.sh --no-wasm
~~~