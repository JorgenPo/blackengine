#ifndef BLRENDERER_H
#define BLRENDERER_H

#include <QOpenGLFunctions>

#include <blshaderprogram.h>
#include <blgameobject.h>
#include <bllight.h>

#include <memory>

namespace black {

class Renderer : public QOpenGLFunctions
{
public:
    static Renderer& getInstance() {
        static Renderer renderer;

        return renderer;
    }

    void renderModel(const std::shared_ptr<Model> &model);
    void renderTerrain(const std::shared_ptr<Terrain> &terrain);
    //void renderScene(const std::shared_ptr<Scene> &scene);

    void setProgram(const std::unique_ptr<ShaderProgram>& program);
    const ShaderProgram *getProgram() const;

    std::shared_ptr<Camera> getCamera() const;
    void setCamera(const std::shared_ptr<Camera> &camera);

    std::shared_ptr<Light> getLight() const;
    void setLight(const std::shared_ptr<Light> &light);

private:
    Renderer();

    ~Renderer();
private:
    ShaderProgram* m_program;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Light> m_light;
};

} // end of black namespace
#endif // BLRENDERER_H
