#include "bltexture.h"

#include <src/utils/bllogger.h>

#include <QImage>
#include <QDebug>

namespace black {

Texture::Texture()
    : m_texture()
{
}

void Texture::load(string file)
{
    Logger::getInstance() << "Loading " << file << " texture...";

    m_texture = std::make_unique<QOpenGLTexture>(QImage(QString(file.c_str())).mirrored());

    Logger::getInstance() << " Done! " << std::endl;
}

Texture::~Texture()
{
    m_texture.release();
}

void Texture::bind()
{
    m_texture->bind();
}

void Texture::release()
{
    m_texture->release();
}

}
