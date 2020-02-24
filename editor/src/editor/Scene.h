//
// Created by popov on 13.11.2019.
//

#ifndef BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H
#define BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H

#include "SelectableGameObject.h"

#include <BlackEngine/components/LightComponent.h>

#include <QObject>
#include <QtGui/QMouseEvent>

namespace black {
class RTSCamera;
class ObjectCamera;
class SimpleScene;
class Terrain;
class AbstractRenderWindow;
class RayTracer;
class Ray;
}

namespace blackeditor {

class RenderWindow;

/**
 * The edtior main scene
 */
class Scene : public QObject {
  Q_OBJECT;

  std::shared_ptr<black::SimpleScene> scene;
  std::shared_ptr<black::Camera> currentCamera;
  std::shared_ptr<black::RTSCamera> rtsCamera;
  std::shared_ptr<black::ObjectCamera> objectCamera;
  std::shared_ptr<black::Terrain> terrain;
  std::shared_ptr<black::GameObject> mainLight;
  std::shared_ptr<black::AbstractRenderWindow> window;
  std::shared_ptr<black::InputSystemInterface> input;
  std::shared_ptr<black::RayTracer> tracer;

  std::unique_ptr<SelectableGameObject> selected;

  using BlackScene = std::shared_ptr<black::SimpleScene>;

  enum class Mode {
    VIEW,
    TRANSLATE,
    SCALE,
    ROTATE,
  };

  Mode mode = Mode::VIEW;
public:
  Scene(
      std::shared_ptr<RenderWindow> window,
      std::shared_ptr<black::InputSystemInterface> input);

  void initialize();
  void initializeShaders();
  void initializeModels();
  void update(bool focus);

  [[nodiscard]] BlackScene get() const noexcept;

signals:
  void objectSelected(std::shared_ptr<black::GameObject> object);
  void selectedObjectTransformed();

public slots:
  void onLightIntensityChanged(double newIntensity);
  void onAmbientIntensityChanged(double newIntensity);
  void onLightColorChanged(const QColor &color, LightType type);
  void setLightEnabled(int state);

  void mousePressedEvent(QMouseEvent *event);
  void mouseReleasedEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);

private:
  void updateSelection();
  void updateSelectionTranslate(const black::Ray &ray);
  void updateSelectionRotate();
  void updateSelectionScale();
};

}

#endif //BLACKENGINE_EDITOR_SRC_EDITOR_SCENE_H
