#include "sprite.hpp"

std::map<Image*, std::vector<Sprite*>*> SpriteBatch {{}};

const unsigned int Sprite::SquareIndices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Sprite::Sprite(int* _x, int* _y, int _xOffset, int _yOffset, int _width, int _height, int _frames, int _frameTime, Image* image) :
    x(_x), y(_y), xOffset(_xOffset), yOffset(_yOffset), height(_height), width(_width), frames(_frames), frameTime(_frameTime), textureID(image->id), imgh(image->height), imgw(image->width) {
        frame = 0;
        auto keyExists = SpriteBatch.count(image);
        if (keyExists != 1) {
            auto pair = std::pair<Image*, std::vector<Sprite*>*>(image, new std::vector<Sprite*>{ this });
            SpriteBatch.insert(pair);
            printf("New batch\n");
        } else {
            auto vector = SpriteBatch.at(image);
            vector->push_back(this);
            printf("Existing batch\n");
        }
        
        printf("Number of sprite in batch: %lu\n", SpriteBatch.at(image)->size());
};

void Sprite::DrawSprite(Sprite* sprite, int x, int y, int offsetx, int offsety, double alpha)
{
	int height = sprite->height;
	int width = sprite->width;
	int frame = sprite->frame;
	int imgh = sprite->imgh;
	int imgw = sprite->imgw;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sprite->textureID);
}

void Sprite::PlaySprite(Sprite* sprite)
{
	sprite->frame = (sprite->frame + 1) % sprite->frames;
}
