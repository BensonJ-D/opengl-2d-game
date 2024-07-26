#pragma once
#include "globals.hpp"

class GameManager
{
public:
//    StateMachine state;

    double nextFrameTimer, fpsTimer, updateTimer, interpol;
    int frameCount, FPS, frameLimiter, prev_fps;
    bool newFrame;

    int sprites[10][3];

    GameManager();
    ~GameManager();

    GLFWwindow* SetupWindow();

    static void MouseCall(int button, int state, int x, int y);
    static void UpdateMousePos(int x, int y);
    static void CharacterPress(unsigned char key, int x, int y);
    static void CharacterRelease(unsigned char key, int x, int y);
    static void SymbolPress(int key, int x, int y);
    static void SymbolRelease(int key, int x, int y);
    static void Update(int i);
    static void Main();
    static void Redraw();
    static void ObjectUpdate(int val);

};
extern GameManager Game;
