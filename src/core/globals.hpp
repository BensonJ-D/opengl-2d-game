#pragma once

#define PI 3.14159265

#include "opengl.hpp"

typedef unsigned char BYTE;
typedef unsigned long DWORD;


enum KeyState { ON_RELEASE = -1, RELEASE = GLFW_RELEASE, PRESS = GLFW_PRESS,  ON_PRESS = 2, HOLD = 3  };

extern int start();
