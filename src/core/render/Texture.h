//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_TEXTURE_H
#define BLACKENGINE_TEXTURE_H

#include <memory>
#include <core/Image.h>
#include <core/Color.h>

namespace black::render {
    enum class TextureFiltering {
        NEAREST,
        LINEAR,
        TRILINEAR,
        ANISOTROPIC
    };

    enum class TextureWrapping {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };

    /**
     * Texture class
     */
    class Texture : public resources::Resource {
    protected:
        TextureFiltering filtering;
        TextureWrapping wrapping;

    public:
        static std::shared_ptr<Texture> fromFile(std::string fileName);

        explicit Texture(std::shared_ptr<Image> image, bool generateMipMaps,
                         TextureFiltering filtering,
                         TextureWrapping wrapping);

        virtual ~Texture();


        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void setBorderColor(Color color) = 0;

        TextureFiltering getFiltering() const;

        TextureWrapping getWrapping() const;
    };
}


#endif //BLACKENGINE_TEXTURE_H
