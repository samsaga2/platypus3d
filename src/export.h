#pragma once

#ifndef __EMSCRIPTEN__
#define EXPORT
#else
#include <emscripten/emscripten.h>
#define EXPORT EMSCRIPTEN_KEEPALIVE extern "C"
#endif
