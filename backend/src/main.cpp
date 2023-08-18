#include "BackEnd.hpp"
#include <iostream>
#include <string>
#include <emscripten.h>

extern "C" int EMSCRIPTEN_KEEPALIVE helloWasm()
{
    return 1234;
}

int main()
{
    return 0;
}