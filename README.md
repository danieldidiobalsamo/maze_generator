# About

This app consists in a maze generator taking advantage of web assembly : the C++ backend is imported from Vue.js frontend as a javascript module, using Emscripten.

![image info](./img/example.png)

# How to launch

## Dev instance

CMake and Emscripten must be installed.

~~~
./launch_dev.sh
~~~

Compile and launch unit tests without the http server :
~~~
./launch_dev.sh --no-wasm
~~~

## Prod instance

Future versions will include a docker image, which will allow you to only call docker run to launch the app.