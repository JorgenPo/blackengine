//
// Created by popof on 25.04.2018.
//

#include "GLTexture.h"

namespace black::render {

    int getGLWrappingType(TextureWrapping wrapping) {
        switch (wrapping) {
            case TextureWrapping::CLAMP_TO_BORDER:
                return GL_CLAMP_TO_BORDER;
            case TextureWrapping::CLAMP_TO_EDGE:
                return GL_CLAMP_TO_EDGE;
            case TextureWrapping::REPEAT:
                return GL_REPEAT;
            case TextureWrapping::MIRRORED_REPEAT:
                return GL_MIRRORED_REPEAT;
        }
    }
    int getGLFilteringType(TextureFiltering filtering) {
        switch (filtering) {
            case TextureFiltering::NEAREST:
                return GL_NEAREST;
            case TextureFiltering::LINEAR:
                return GL_LINEAR;
            case TextureFiltering::TRILINEAR:
            case TextureFiltering::ANISOTROPIC:
                return GL_LINEAR;
        }
    }

    GLTexture::GLTexture(const std::shared_ptr<Image> &image, bool generateMipMaps,
                         TextureFiltering filtering = TextureFiltering::NEAREST,
                         TextureWrapping wrapping = TextureWrapping::CLAMP_TO_BORDER)
            : Texture(image, generateMipMaps, filtering, wrapping) {

        glGenTextures(1, &this->texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGLWrappingType(wrapping));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGLWrappingType(wrapping));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGLFilteringType(filtering));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGLFilteringType(filtering));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());

        if (generateMipMaps) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    void GLTexture::bind() {
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }

    void GLTexture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTexture::setBorderColor(Color color) {
        if (this->wrapping != TextureWrapping::CLAMP_TO_BORDER) {
            return;
        }

        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color.getArray().data());
    }
}