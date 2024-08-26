#include "image_manager.hpp"

Image* ImageManager::loadImage(std::string name, std::string resourcePath) {
	Image* image = new Image(resourcePath);
	mImages.emplace(name, image);
	return image;
}

