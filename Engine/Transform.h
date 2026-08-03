#pragma once

#include "Vector2.h"

namespace nu {
    struct Transform {
        Vector2 pos;
        float rotation;
        float scale;
    };
}