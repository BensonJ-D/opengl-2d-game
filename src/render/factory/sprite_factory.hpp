#pragma once
#include <vector>
#include <map>

#include "image.hpp"
#include "sprite.hpp"

namespace render {
class SpriteFactory {
    Sprite* create(Image* image);
};
}
