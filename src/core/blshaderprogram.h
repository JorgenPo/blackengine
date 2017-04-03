#ifndef BLSHADERPROGRAM_H
#define BLSHADERPROGRAM_H

#include "blcamera.h"

#include <src/core/blshader.h>
#include <src/core/blmaterial.h>

#include <src/utils/bllight.h>

#include <QOpenGLShaderProgram>

#include <memory>
#include <string>

namespace black {

/**
 * @brief The ShaderProgram class
 * Represents a concrete shader program.
 * This is a base class for all shader programs.
 * This class can do everything possible operations and fearures
 * and can be seen like a ideal, most powerful shader program.
 * All children of this shader can disable some features.
 *
 * @version 1.1.1 4.03.2017
 * Add oportunity to turn on and off textures in shaders.
 *
 * @version 1.1 29.03.2017
 * Move to structures of light and material.
 * Make possible to attach camera to shader
 * (view and proj. matrices and position)
 *
 * @version 1.0 27.03.2017
 * First working version.
 *
 * @author george popof <popoff96@live.com>
 */
class ShaderProgram : public QOpenGLShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(std::shared_ptr<Shader> vertex,
                  std::shared_ptr<Shader> fragment);

    virtual ~ShaderProgram();

    void create(std::shared_ptr<Shader> vertex,
                std::shared_ptr<Shader> fragment);

    virtual bool link() override;

    /* Capabilities of this shader */

    // Must be overriden properly in subclasses
    // Base shader can do anything!!
    virtual bool supportTextures() const { return true; }
    virtual bool supportPositions() const { return true; }
    virtual bool supportBuffers() const { return true; }
    virtual bool supportLight() const { return true; }
    virtual bool supportMaterials() const { return true; }
    virtual bool supportModelMatrix() const { return true; }
    virtual bool supportCameraPosition() const { return true; }
    virtual bool supportCamera() const { return true; }

    // Can be overriden, but by default
    // do this work by self
    virtual void setModelMatrix(const QMatrix4x4& model);

    virtual void setCamera(const Camera *camera);

    virtual void setLight(const Light* light);
    virtual void setMaterial(std::shared_ptr<Material> material);

    virtual void enableTextures();
    virtual void disableTextures();

    virtual bool bind();

    /* QOpenGLShader */
    virtual std::string log() const;

    std::shared_ptr<Shader> vertex() const;
    std::shared_ptr<Shader> fragment() const;

private:
    virtual void bindLocations();
    virtual void defaultUniforms();

protected:
    std::shared_ptr<Shader> m_vertex;
    std::shared_ptr<Shader> m_fragment;
};

} // end of black namespace
#endif // BLSHADERPROGRAM_H
