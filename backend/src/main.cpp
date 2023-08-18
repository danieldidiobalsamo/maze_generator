#include "BackEnd.hpp"
#include <emscripten.h>
#include <iostream>
#include <string>

extern "C" int EMSCRIPTEN_KEEPALIVE helloWasm()
{
    return 1234;
}

int main()
{
    return 0;
}