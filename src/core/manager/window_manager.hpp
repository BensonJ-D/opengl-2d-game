#pragma once
#include "core/globals.hpp"

class WindowManager
{
public:
    WindowManager() { mWindow = NULL; };
    ~WindowManager() { };

    GLFWwindow* createWindow(int width, int height);
    GLFWwindow* getWindow();

private:
    GLFWwindow* mWindow;
};
