#include "bltexture.h"

#include <QImage>

namespace black {

Texture::Texture(string path)
{
    load(path);
}

void Texture::load(string file)
{
    m_texture = std::make_unique<QOpenGLTexture>(
                QImage(file.c_str()));
}

Texture::~Texture()
{
    m_texture.release();
}

}
