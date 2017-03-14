#include "bltexture.h"

#include <QImage>
#include <QDebug>

namespace black {

Texture::Texture()
    : m_texture()
{
}

void Texture::load(string file)
{
    qDebug() << "loading" << file.c_str();

    m_texture = std::make_unique<QOpenGLTexture>(QImage(QString(file.c_str())).mirrored());

    qDebug() << "loaded: " << m_texture->width() << "x" << m_texture->height();
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
