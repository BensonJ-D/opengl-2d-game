#include "image_factory.hpp"
#include "../domain/image.hpp"
#include "../../core/opengl.hpp"

namespace render {
    ImageFactory::IImageResource::~IImageResource() { };
    inline unsigned int ImageFactory::IImageResource::getWidth() { return mWidth; }
    inline unsigned int ImageFactory::IImageResource::getHeight() { return mHeight; }
    inline GLuint ImageFactory::IImageResource::getTextureId() { return mTextureId; }

    ImageFactory::PNGResource::PNGResource(FILE* pFile, BYTE* sig) {
        rewind(pFile);
        
        png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!pngPtr) {
            printf("Couldn't initialize png read struct.\nExiting.");
            exit(7);
        }
        
        png_infop infoPtr = png_create_info_struct(pngPtr);
        if (!infoPtr) {
            png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
            printf("Couldn't initialize png info struct.\nExiting.");
            exit(9);
        }

        if(setjmp(png_jmpbuf(pngPtr))) {
            printf("Couldn't initialize png info struct.\nExiting.");
            exit(9);
        }

        png_bytep* rowPtrs = NULL;
        char* data = NULL;

        png_init_io(pngPtr, pFile);

        png_read_info(pngPtr, infoPtr);

        printf("Read info struct.\n");

        png_uint_32 imgWidth =  png_get_image_width(pngPtr, infoPtr);
        png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);
        
        png_uint_32 bitDepth   = png_get_bit_depth(pngPtr, infoPtr);
        png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
        printf("Channels: %d\n", channels);
        png_uint_32 colourType = png_get_color_type(pngPtr, infoPtr);
        
        switch (colourType) {
                
            case PNG_COLOR_TYPE_PALETTE:
                png_set_palette_to_rgb(pngPtr);
                channels = 3;
                break;
                
            case PNG_COLOR_TYPE_GRAY:
                if (bitDepth < 8)
                    png_set_expand_gray_1_2_4_to_8(pngPtr);
            
                bitDepth = 8;
                break;
        }
        
        if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
            png_set_tRNS_to_alpha(pngPtr);
            printf("Has Alpha\n");
            channels+=1;
        }

        if (bitDepth == 16) {
            png_set_strip_16(pngPtr);
        }

        rowPtrs = new png_bytep[imgHeight];
        data = new char[imgWidth * imgHeight * bitDepth * channels / 8];
        const unsigned int stride = imgWidth * bitDepth * channels / 8;

        
        for (unsigned int i = 0; i < imgHeight; i++) {
            png_uint_32 q = (imgHeight- i - 1) * stride;
            rowPtrs[imgHeight - 1 - i] = (png_bytep)data + q;
        }

        png_read_image(pngPtr, rowPtrs);
        
        printf("Loading image in to RAM...\n");
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("Saving dimensions...\n");
        
        mWidth = imgWidth;
        mHeight = imgHeight;

        delete[] (png_bytep)rowPtrs;
        png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
    };

    ImageFactory::ImageFactory() {};
    ImageFactory::~ImageFactory() {};

    Image* ImageFactory::loadImage(std::string filename) {
        IImageResource* resource;
        FILE* pFile = fopen(filename.c_str(), "rb");

        if(pFile == NULL) {
            delete pFile;
            throw std::runtime_error("Could not open " + filename);
        }

        BYTE sig[8];
        fread(sig, 8, 1, pFile);

        if(sig[0] == 137 && sig[1] == 80 && sig[2] == 78 && sig[3] == 71 &&
           sig[4] == 13 && sig[5] == 10 && sig[6] == 26 && sig[7] == 10) {
            resource = new PNGResource(pFile, sig);
        }
        else {
            resource = NULL;
            printf("Unsupported format\n");
        }

        fclose(pFile);

        Image* pImage = new Image(resource->getWidth(), resource->getHeight(), resource->getTextureId());
        
        delete resource;
        return pImage;
    }
}
