#pragma once

#ifdef __EMSCRIPTEN__

#include <emscripten/emscripten.h>

EM_JS(int, canvas_get_width, (), {
        return canvas.width;
    });

EM_JS(int, canvas_get_height, (), {
        return canvas.height;
    });

#endif
