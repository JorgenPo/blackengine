#include "SelectedShader.h"
#include "SelectableGameObject.h"

#include <application/GameApplication.h>
#include <tracer/RayTracer.h>

#include <iostream>
#include <memory>
#include <utility>
#include <terrain/Terrain.h>
#include <terrain/TerrainBuilder.h>


using namespace black;

class BlackEngineApplication : public GameApplication {
  std::shared_ptr<AbstractScene> scene;
  SelectableGameObject selected;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Terrain> terrain;
  std::shared_ptr<GameObject> light;
  std::shared_ptr<ApplicationShader> hoveredShader;
  std::shared_ptr<ApplicationShader> selectedShader;
  RayTracer tracer;
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
    tracer(nullptr),
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

  void onMouseButtonPressed(MouseButtonEvent event) override {
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
    if (Input::IsKeyPressed(Key::LEFT)) {
      this->camera->strafeLeft(0.05f);
    }
    if (Input::IsKeyPressed(Key::RIGHT)) {
      this->camera->strafeRight(0.05f);
    }
    if (Input::IsKeyPressed(Key::UP)) {
      this->camera->moveForward(0.1f);
    }
    if (Input::IsKeyPressed(Key::DOWN)) {
      this->camera->moveBackward(0.1f);
    }
  }

  std::shared_ptr<GameObject> findSelectedObject(const Ray &ray) {
    for (auto i = scene->getObjects().rbegin(); i != scene->getObjects().rend(); i++) {
      const auto &object = *i;

      if (object == this->terrain) {
        continue;
      }

      if (auto bounds = object->get<BoundingComponent>(); bounds != nullptr) {
        if (!bounds->getIntersectionsWith(ray).empty()) {
          return object;
        }
      }
    }

    return nullptr;
  }

  void update(float dt) override {
    handleInput();
    auto time = this->timer->getUptime();

    float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius + this->cameraOffsetX;
    float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

    if (this->rotating) {
      // Light
      this->light->transform->setPosition({camX, 10.3f, camZ});
    }

    bool wasHovered = selected.getObject() != nullptr;

    auto ray = tracer.calculateRay(Input::GetMouseX(), Input::GetMouseY());

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
      Input::SetCursor(cursor);
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

    light = std::make_shared<GameObject>("Sun");
    light->transform->setPosition({10.0f, 200.0f, 0.0f});
    light->add(std::make_shared<LightComponent>(LightType::DIRECTIONAL));
    light->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

    scene->addObjects({light, cottage, cube});

    this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
    this->camera->setPosition({0.0f, 10.0f, 1.0f});
    this->camera->setLookAt({0.0f, -1.0f, 0.0f});

    tracer.setCamera(camera);

    scene->setCurrentCamera(camera);

    Input::AddCursor("Hovered", cursorHovered);
    Input::AddCursor("Normal", cursorNormal);
    Input::SetCursor("Normal");
  }

  void loadShaders() {
    this->selectedShader = util::ShaderManager::CreateApplicationShaderFromFile<SelectedShader>(
      "resources/selected_vertex.glsl", "resources/selected_fragment.glsl");
    this->hoveredShader = std::make_shared<SelectedShader>(this->selectedShader);

    this->hoveredShader->setAmbientLight(Color::RED, 0.1f);
    this->selectedShader->setAmbientLight(Color::GREEN, 0.1f);

    this->selected = SelectableGameObject(hoveredShader, selectedShader);
  }
};

int main(int argc, char **argv) {
  try {
    BlackEngineApplication application;
    application.start();
  } catch (const std::exception &e) {
    Logger::Get("Initialization example")->critical("Initialization Example error: {}", e.what());
    return 1;
  }

  return 0;
}