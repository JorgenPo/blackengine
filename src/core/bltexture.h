#ifndef BLTEXTURERESOURCE_H
#define BLTEXTURERESOURCE_H

#include "blresource.h"

#include <QOpenGLTexture>

#include <memory>

namespace black {

class ResourceManager;

/**
 * @brief The Texture class
 *  Texture is 2D image with mipmaps.
 * Based on QOpenGLTexture class.
 * Implements a @class resource interface.
 *
 * @author george popoff <popoff96@live.com>
 * @date 12.03.2017
 * @version 1.0 Working version
 */
class Texture : public Resource
{
    using pointer = std::unique_ptr<QOpenGLTexture>;

    friend class ResourceManager;
public:

    /**
     * @brief Constructs texture from file with
     *  given path
     * @param path file path to find a texture file.
     *  must contain a file type.
     */
    Texture();
    ~Texture();

    void bind();
    void release();

    // Interface for manager
private:
    // Resource interface
    void load(string file) override;
public:
    std::string defaultName() override { return std::string("default.jpg"); }
    std::string folderName()  override { return std::string("textures");    }

private:
    pointer m_texture;
};

}
#endif // BLTEXTURERESOURCE_H
