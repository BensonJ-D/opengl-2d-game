#pragma once
#include "image.hpp"
#include "../core/opengl.hpp"
#include <map>
#include <vector>

class Sprite {
    const static unsigned int SquareIndices[];
    
    float vertices[24];
    
    const int *x, *y;
    int xOffset, yOffset;
	int height, width;
	int frame;
	int frames;
	int textureID;	
	int imgh, imgw;
	int frameTime, lastFrame;
    unsigned int VBO, VAO, EBO;

public:
	Sprite() {};
    Sprite(int* _x, int* _y, int _xOffset, int _yOffset, int _width, int _height, int _frames, int _frameTime, Image* image);
    
    ~Sprite() {};
    void DrawSprite(Sprite* sprite, int x, int y, int offsetx, int offsety, double alpha);
    void PlaySprite(Sprite* sprite);
};

extern std::map<Image*, std::vector<Sprite*>*> SpriteBatch;
