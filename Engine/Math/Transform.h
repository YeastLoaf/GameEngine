#pragma once
#include "Serialization/json.h"
#include "Vector2.h"

namespace nu {
    struct Transform {
        Vector2 pos{ 0.0f, 0.0f };
        float rotation{ 0.0f };
        float scale{ 1.0f };

        void Read(const json::value_t& value) {
            JSON_READ(value, pos);
            JSON_READ(value, rotation);
            JSON_READ(value, scale);
        }
    };
}