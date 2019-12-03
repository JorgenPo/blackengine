#include "SelectedShader.h"
#include "SelectableGameObject.h"

#include <application/GameApplication.h>
#include <tracer/RayTracer.h>
#include <terrain/Terrain.h>
#include <terrain/TerrainBuilder.h>

#include <iostream>
#include <memory>


using namespace black;

class BlackEngineApplication : public GameApplication {
  std::shared_ptr<AbstractScene> scene;
  SelectableGameObject selected;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Terrain> terrain;
  std::shared_ptr<DirectedLight> light;
  std::shared_ptr<SelectedShader> hoveredShader;
  std::shared_ptr<SelectedShader> selectedShader;
  std::unique_ptr<RayTracer> tracer;
  Image cursorHovered;
  Image cursorNormal;

  float cameraRadius = 10.0f;
  float cameraSpeed = 0.1f;
  float cameraOffsetX = 0.0f;

  bool rotating = true;
public:
  BlackEngineApplication() :
  GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
    800, 600, false),
    scene(new SimpleScene("Test")),
    cursorHovered("resources/cursor_hovered.png"),
    cursorNormal("resources/cursor_normal.png")
    {}

protected:
  void onKeyReleased(KeyEvent keyEvent) override {
    switch (keyEvent.key) {
      case Key::ESCAPE:
        this->stop();
        break;
      default:
        return;
    }
  }

  void onMouseButtonPressed(const MouseButtonEvent &event) override {
    switch (event.button) {
      case MouseButton::LEFT:
        if (selected.isObjectSelected()) {
          selected.unselect();
        } else {
          selected.select();
        }
        break;
      case MouseButton::RIGHT:
        break;
      case MouseButton::MIDDLE:
        break;
    }
  }

private:
  void handleInput() {
    if (input->isKeyPressed(Key::LEFT)) {
      this->camera->strafeLeft(0.05f);
    }
    if (input->isKeyPressed(Key::RIGHT)) {
      this->camera->strafeRight(0.05f);
    }
    if (input->isKeyPressed(Key::UP)) {
      this->camera->moveForward(0.1f);
    }
    if (input->isKeyPressed(Key::DOWN)) {
      this->camera->moveBackward(0.1f);
    }

    if (input->isKeyPressed(Key::BACKSPACE)) {
      if (selected.getObject() && selected.isObjectSelected()) {
        this->scene->removeObject(selected.getObject()->getName());
        selected.resetObject();
      }
    }

    static auto multiplyLightIntensityBy = [this](float multiplier) {
      this->light->setIntensity(
        light->getIntensity() * multiplier);
      this->light->setSpectacularIntensity(
        light->getSpectacularIntensity() * multiplier);
    };

    if (input->isKeyPressed(Key::RIGHT_SHIFT)) {
      multiplyLightIntensityBy(1.1f);
    } else if (input->isKeyPressed(Key::LEFT_SHIFT)) {
      multiplyLightIntensityBy(0.9f);
    }
  }

  std::shared_ptr<GameObject> findSelectedObject(const Ray &ray) {
    return this->scene->getIntersectingObject(ray);
  }

  void update(float dt) override {
    handleInput();

    auto time = this->timer->getUptime();

    float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius + this->cameraOffsetX;
    float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

    bool wasHovered = selected.getObject() != nullptr;

    auto ray = tracer->calculateRay(input->getMouseX(), input->getMouseY());

    auto hoveredObject = findSelectedObject(ray);
    auto hovered = hoveredObject != nullptr;

    // Set highlighting shader if some object was selected
    if (hoveredObject && !selected.isObjectSelected()) {
      selected.setObject(hoveredObject);
    } else if (!hoveredObject && !selected.isObjectSelected()) {
      selected.resetObject();
    } else if (selected.getObject() && selected.isObjectSelected()) {
      auto intersectPoints = this->terrain->getBounding()->getIntersectionsWith(ray);
      if (!intersectPoints.empty()) {
        auto point = intersectPoints[0];

        auto position = glm::vec3(point.x, terrain->getTerrain()->getHeightAt(point.x, point.y), point.z);
        selected.getObject()->transform->setPosition(position);
      }
    }

    this->renderer->render(this->scene);

    if (hovered != wasHovered) {
      auto cursor = hovered ? "Hovered" : "Normal";
      input->setCursor(cursor);
    }
  }

  void initializeResources() override {
    loadShaders();
    initScene();
  }

  void initScene() {
    auto builder = Engine::GetTerrainBuilder("Flat");
    TerrainBuilder::Data data;
    data.width = 1000;
    data.height = 1000;
    data.lod = 5.0f;

    terrain = builder->build(data);
    this->scene->addObject(terrain);

    auto cottageModel = ModelManager::CreateFromFile("resources/cottage_obj.obj");
    auto cubeModel = ModelManager::CreateFromFile("resources/cube.obj");

    auto cottage = std::make_shared<GameObject>("Cottage");
    cottage->add(cottageModel);
    cottage->add(
      std::make_shared<BoundingComponent>(
        std::make_shared<Sphere>(cottage->transform, 12.0f)));

    cottage->transform->scale(0.1f);

    auto cube = std::make_shared<GameObject>("Cube");
    cube->add(cubeModel);
    cube->transform->scale(1.0f);
    cube->transform->rotateX(35.0f);
    cube->transform->setPosition({3.0f, 0.5f, 3.0f});
    cube->add(
      std::make_shared<BoundingComponent>(
        std::make_shared<Sphere>(cube->transform, 1.0f)));

    light = std::make_shared<DirectedLight>(Color::RED, 1.0f, 0.1f,
      glm::vec3{0.2f, -1.0f, -1.0f});

    auto lightObject = std::make_shared<GameObject>("Sun");
    lightObject->add(light);

    scene->addObjects({lightObject, cottage, cube});

    Camera::Data cameraData{
      window,
      ProjectionType::PERSPECTIVE,
      {0.0f, 10.0f, 1.0f}};
    cameraData.lookAt = {0.0f, -1.0f, 0.0f};

    this->camera = std::make_shared<Camera>(std::move(cameraData));
    this->camera->getRenderTarget()->subscribe(camera);

    this->tracer = std::make_unique<RayTracer>(camera, window);

    scene->setCurrentCamera(camera);

    input->addCursor("Hovered", cursorHovered);
    input->addCursor("Normal", cursorNormal);
    input->setCursor("Normal");
  }

  void loadShaders() {
    this->selectedShader = util::ShaderManager::CreateApplicationShaderFromFile<SelectedShader>(
      "resources/selected_vertex.glsl", "resources/selected_fragment.glsl");
    this->hoveredShader = std::make_shared<SelectedShader>(this->selectedShader);

    this->hoveredShader->use();
    this->hoveredShader->setColor(Color::RED, 1.0f);

    this->selectedShader->use();
    this->selectedShader->setColor(Color::GREEN, 1.0f);

    this->selected = SelectableGameObject(hoveredShader, selectedShader);
  }
};

int main(int argc, char **argv) {
  try {
    auto application = std::make_shared<BlackEngineApplication>();
    application->start();
  } catch (const std::exception &e) {
    Logger::Get("Initialization example")->critical("Initialization Example error: {}", e.what());
    return 1;
  }

  return 0;
}