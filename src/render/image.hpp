#pragma once

#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <string>

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
        Image(std::string filename);
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
    PNG(std::string filename, bool keepData);
    BYTE* pixelData;
    
private:
    bool keepData;
    DWORD written;
    BYTE* tempPixelData;
};
