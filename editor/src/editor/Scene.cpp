//
// Created by popov on 13.11.2019.
//

#include "Scene.h"
#include "MaskedShader.h"
#include "common/Util.h"

#include <renderwindow.h>

#include <BlackEngine/Engine.h>
#include <BlackEngine/log/Logger.h>
#include <BlackEngine/camera/Camera.h>
#include <BlackEngine/util/ModelManager.h>
#include <BlackEngine/components/TerrainComponent.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TransformComponent.h>
#include <BlackEngine/components/LightComponent.h>
#include <BlackEngine/terrain/TerrainBuilder.h>
#include <BlackEngine/camera/RTSCamera.h>
#include <BlackEngine/tracer/RayTracer.h>

#include <memory>
#include <BlackEngine/util/ShaderManager.h>
#include <mainwindow.h>

using namespace blackeditor;
using namespace black;

Scene::Scene(
    std::shared_ptr<RenderWindow> window,
    std::shared_ptr<black::InputSystemInterface> input)
  : window(std::move(window))
  , scene(std::make_shared<SimpleScene>("MainScene"))
  , input(std::move(input))
  , selected(nullptr)
{
}

Scene::BlackScene Scene::get() const noexcept {
  return scene;
}

void Scene::initialize() {
  auto builder = Engine::GetTerrainBuilder("FlatTerrain");
  TerrainBuilder::Data data;
  data.width = 1000;
  data.height = 1000;
  data.lod = 5.0f;

  terrain = builder->build(data);
  terrain->get<BoundingComponent>()->setIntersectionEnabled(false);

  this->scene->addObject(terrain);

  CameraData cameraData(
      input,
      window,
      this->scene,
      ProjectionType::PERSPECTIVE,
      {0.0f, 10.0f, 0.0f});

  camera = Engine::CreateCamera<RTSCamera>(cameraData);

  // Create models
  initializeModels();

  // Create light
  auto directedLight = std::make_shared<DirectedLight>(
      Color::WHITE, 2.0f, 0.1f, glm::vec3{-1.0f, -1.0f, 0.2f});

  mainLight = std::make_shared<GameObject>("Sun");
  mainLight->transform->setPosition({10.0f, 200.0f, 0.0f});
  mainLight->add(directedLight);
  mainLight->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

  scene->addObjects({mainLight});

  auto ambientLight = scene->getAmbientLight();
  ambientLight.intensity = 0.2f;
  scene->setAmbientLight(ambientLight);

  scene->setCurrentCamera(this->camera);

  // Init raytracer
  this->tracer = std::make_unique<black::RayTracer>(camera, window);

  // Init shaders
  initializeShaders();
}

void Scene::onLightIntensityChanged(double intensity) {
  mainLight->get<LightComponent>()->setIntensity(static_cast<float>(intensity));
}

void Scene::setLightEnabled(int enable) {
  if (enable == Qt::Unchecked) {
    this->scene->removeObject(mainLight->getName());
  } else {
    this->scene->addObject(mainLight);
  }
}

void Scene::onAmbientIntensityChanged(double newIntensity) {
  this->scene->setAmbientLight({Color::WHITE, static_cast<float>(newIntensity)});
}

void Scene::update(bool focus) {
  updateSelection();

  if (focus) {
    this->camera->update();
  }
}

void Scene::updateSelection() {
  auto ray = tracer->calculateRay(input->getMouseX(), input->getMouseY());
  auto hoveredObject = this->scene->getIntersectingObject(ray);

  bool wasHovered = selected->getObject() != nullptr;
  bool hovered = hoveredObject != nullptr;

  // Set highlighting shader if some object was selected
  if (hoveredObject && !selected->isObjectSelected()) {
    selected->setObject(hoveredObject);
    input->setCursor(MainWindow::CURSOR_HAND);
  } else if (!hoveredObject) {
    if (!selected->isObjectSelected()) {
      selected->resetObject();
    }

    input->setCursor(MainWindow::CURSOR_NORMAL);
  }

  if (selected->isObjectSelected()) {
    switch (mode) {
    case Mode::TRANSLATE:
      updateSelectionTranslate(ray);
      break;
    case Mode::SCALE:
      updateSelectionScale();
      break;
    case Mode::ROTATE:
      updateSelectionRotate();
      break;
    default:
      break;
    }
  }

  if (!selected->isObjectSelected() && hovered != wasHovered) {
    auto cursor = hovered ? MainWindow::CURSOR_HAND : MainWindow::CURSOR_NORMAL;
    input->setCursor(cursor);
  }
}

void Scene::initializeShaders() {
  auto selectedShader = black::util::ShaderManager::CreateApplicationShaderFromFile<MaskedShader>(
      "resources/masked_vertex.glsl", "resources/masked_fragment.glsl");
  auto hoveredShader = std::make_shared<MaskedShader>(selectedShader);

  hoveredShader->use();
  hoveredShader->setColorMask(Color::RED * 2.5f);

  selectedShader->use();
  selectedShader->setColorMask(Color::GREEN * 2.5f);

  this->selected = std::make_unique<SelectableGameObject>(std::move(hoveredShader), std::move(selectedShader));
}

void Scene::initializeModels() {
  auto cottageModel = ModelManager::CreateFromFile("resources/cottage_obj.obj");
  auto cottage = std::make_shared<GameObject>("Cottage");

  cottage->add(cottageModel);
  cottage->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(cottage->transform, 12.0f)));

  cottage->transform->scale(0.1f);

  auto spider = std::make_shared<GameObject>("Spider");
  auto spiderModel = ModelManager::CreateFromFile("resources/spider.obj");
  spider->add(spiderModel);
  spider->transform->setPosition({5.0f, 0.0f, 0.0f});

  spider->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(spider->transform, 15.0f)));
  spider->transform->scale(0.05f);

  auto dog = std::make_shared<GameObject>("Dog");
  auto dogModel = ModelManager::CreateFromFile("resources/dog.obj");
  dog->add(dogModel);
  dog->transform->setPosition({-4.0f, 0.0f, 0.0f});
  dog->transform->scale(0.05f);
  dog->transform->rotateX(-90.0f);

  dog->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(dog->transform, 10.0f)));

  auto sphere = std::make_shared<GameObject>("Sphere");
  auto sphereModel = ModelManager::CreateFromFile("resources/sphere.obj");
  sphere->add(sphereModel);
  sphere->add(std::make_shared<BoundingComponent>(
      std::make_shared<Sphere>(sphere->transform, 1.0f)));

  scene->addObjects({std::move(cottage), std::move(spider), std::move(dog), std::move(sphere)});
}

void Scene::mousePressedEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    if (selected->isObjectSelected()) {
      selected->unselect();
      selected->resetObject();

      mode = Mode::VIEW;
      emit objectSelected(nullptr);
    } else {
      selected->select();
      emit objectSelected(selected->getObject());
    }
  }

  auto blackEvent = toBlackengineMouseButtonEvent(event);
  if (blackEvent) {
    camera->onMouseButtonPressed(blackEvent.value());
  }
}


void Scene::mouseReleasedEvent(QMouseEvent *event) {
  auto blackEvent = toBlackengineMouseButtonEvent(event);
  if (blackEvent) {
    camera->onMouseButtonReleased(blackEvent.value());
  }
}

void Scene::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_T:
    mode = mode == Mode::TRANSLATE ? Mode::VIEW : Mode::TRANSLATE;
    break;
  case Qt::Key_S:
    mode = mode == Mode::SCALE ? Mode::VIEW : Mode::SCALE;
    break;
  }

  // Disable zoom when in scaling mode
  camera->setZoomEnabled(mode != Mode::SCALE);
}

Color fromQt(const QColor &color) {
  return Color(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void Scene::onLightColorChanged(const QColor &color, LightType type) {
  switch (type) {
  case LightType::DIRECTED:
    mainLight->get<DirectedLight>()->setColor(fromQt(color));
    break;
  case LightType::AMBIENT: {
    AmbientLight light(scene->getAmbientLight());
    light.color = fromQt(color);

    scene->setAmbientLight(light);
    break;
  }
  default:
    return;
  }
}

void Scene::updateSelectionTranslate(const black::Ray &ray) {
  auto intersectPoints = this->terrain->getBounding()->getIntersectionsWith(ray);
  if (!intersectPoints.empty()) {
    auto point = intersectPoints[0];

    auto position = glm::vec3(point.x, terrain->getTerrain()->getHeightAt(point.x, point.y), point.z);
    selected->getObject()->transform->setPosition(position);
    emit selectedObjectMoved(toQtVector(selected->getObject()->transform->getPosition()));
  }
}

void Scene::updateSelectionRotate() {

}

void Scene::updateSelectionScale() {
  auto scroll = input->getScrollY();
  if (scroll == 0) {
    return;
  }

  auto transform = selected->getObject()->transform;

  static auto scaleSpeed = 0.01f;

  transform->setScale(transform->getScale() + scaleSpeed * scroll);
  Logger::Get("Scene")->debug("Scroll = {}", scroll);
}
