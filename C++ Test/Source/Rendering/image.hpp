#pragma once

#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>

typedef long LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

class Image
{
    public:
        FILE* hfile;
        BYTE* pixelData;
        unsigned int height;
        unsigned int width;
        GLuint id;
        Image() {};
        Image(const char* Filename);
        ~Image();
};
//
//class Bitmap: public Image
//{
//public:
//    Bitmap(const char* Filename, bool keepData);
//    ~Bitmap();
//    BYTE* pixelData;
//
//private:
//    bool keepData;
//    DWORD written;
//    BITMAPFILEHEADER bfh;
//    BITMAPINFOHEADER bih;
//    BYTE* tempPixelData;
//    int padding;
//};

class PNG: public Image
{
public:
    PNG(const char* Filename, bool keepData);
    BYTE* pixelData;
    
private:
    bool keepData;
    DWORD written;
    BYTE* tempPixelData;
};
