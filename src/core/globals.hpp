#pragma once

#define PI 3.14159265

#include "../render/image.hpp"
#include "opengl.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>

const int MAX_LAYERS = 5;
const int BG_LAYER = 0;
const int UI_LAYER = MAX_LAYERS - 1;

enum KeyState { ON_RELEASE = -1, RELEASE = GLFW_RELEASE, PRESS = GLFW_PRESS,  ON_PRESS = 2, HOLD = 3  };

extern int start();
