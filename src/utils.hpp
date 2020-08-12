#pragma once

#include <iostream>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

inline void printE( const char* tag, const char* message ){
    std::cerr << "Error: " << tag << ": " << message << std::endl;
}