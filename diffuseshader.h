#ifndef DIFFUSESHADER_H
#define DIFFUSESHADER_H

#include <src/core/blshaderprogram.h>

class DiffuseShader : public black::ShaderProgram
{
public:
    DiffuseShader();

    // ShaderProgram interface
public:
    bool supportTextures() const override { return true; }
    bool supportPositions() const override { return true; }
    bool supportBuffers() const override { return false; }
    bool supportLight() const override  { return false; }
    bool supportMaterials() const override { return false; }
    bool supportCamera() const override { return true; }
};

#endif // DIFFUSESHADER_H
