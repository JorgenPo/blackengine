#include "SelectedShader.h"

#include <application/GameApplication.h>
#include <tracer/RayTracer.h>

#include <iostream>
#include <memory>


using namespace black;

class BlackEngineApplication : public GameApplication {
  std::vector<std::shared_ptr<GameEntity>> scene;
  std::shared_ptr<GameEntity> selectedObject;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<ApplicationShader> selectedShader;
  RayTracer tracer;

  float cameraRadius = 10.0f;
  float cameraSpeed = 0.1f;
  float cameraOffsetX = 0.0f;

  bool rotating = true;
public:
  BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
      800, 600, false), tracer(camera) {
  }

private:
  void handleInput() {

    if (Input::IsKeyPressed(KEY_ESCAPE)) {
      this->stop();
    }

    if (Input::IsKeyPressed(KEY_ENTER) && selectedObject) {
      selectedObject->transform->setPosition(tracer.calculateRay(Input::GetMouseX(), Input::GetMouseY()));
    }
  }

  std::shared_ptr<GameEntity> findSelectedObject() {
    auto ray = tracer.calculateRay(Input::GetMouseX(), Input::GetMouseY());

    for (auto i = scene.rbegin(); i != scene.rend(); i++) {
      const auto &object = *i;
      if (auto bounds = object->get<BoundingComponent>(); bounds != nullptr) {
        if (bounds->isIntersectsWith(ray)) {
          selectedObject = object;
          return selectedObject;
        }
      }
    }

    return nullptr;
  }

  void update(float dt) override {
    this->handleInput();

    auto time = this->timer->getUptime();

    float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius + this->cameraOffsetX;
    float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

    if (this->rotating) {
      // Light
      this->scene.at(0)->transform->setPosition({camX, 10.3f, camZ});
    }

    // Reset selected object
    if (this->selectedObject) {
      this->selectedObject->get<ModelComponent>()->setShader(nullptr);
      this->selectedObject = nullptr;
    }

    // Set highlighting shader if some object was selected
    if (auto selected = findSelectedObject(); selected != nullptr) {
      logger->debug(fmt::format("Selected object: {}", selectedObject->getName()));
      selected->get<ModelComponent>()->setShader(selectedShader);
    }

    this->renderer->render(this->scene, this->camera);
  }

  void initializeResources() override {
    loadShaders();
    initScene();
  }

  void initScene() {
    auto cottageModel = ModelManager::CreateFromFile("models/cottage_obj.obj");
    auto cubeModel = ModelManager::CreateFromFile("models/cube.obj");

    auto cottage = std::make_shared<GameEntity>("Cottage");
    cottage->add(cottageModel);
    cottage->add(
      std::make_shared<BoundingComponent>(
        std::make_shared<Sphere>(cottage->transform, 3.0f)));

    cottage->transform->scale(0.1f);

    auto cube = std::make_shared<GameEntity>("Cube");
    cube->add(cubeModel);
    cube->transform->scale(1.0f);
    cube->transform->rotateX(35.0f);
    cube->transform->setPosition({3.0f, 0.5f, 3.0f});
    cube->add(
      std::make_shared<BoundingComponent>(
        std::make_shared<Sphere>(cube->transform, 3.0f)));

    auto car = std::make_shared<GameEntity>("Car");
    car->add(ModelManager::CreateFromFile("models/Shelby.obj"));
    car->transform->setPosition({0.0f, 0.0f, 2.0f});
    car->transform->scale(0.3f);
    cube->add(
      std::make_shared<BoundingComponent>(
        std::make_shared<Sphere>(car->transform, 2.0f)));

    auto light = std::make_shared<GameEntity>("Sun");
    light->transform->setPosition({10.0f, 200.0f, 0.0f});
    light->add(std::make_shared<LightComponent>(LightType::DIRECTIONAL));
    light->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

    this->scene.emplace_back(light);
    this->scene.emplace_back(cottage);
    this->scene.emplace_back(cube);
    this->scene.emplace_back(car);

    this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
    this->camera->setPosition({0.0f, 1.0f, 5.0f});
    tracer.setCamera(camera);
  }

  void loadShaders() {
    this->selectedShader = util::ShaderManager::CreateApplicationShaderFromFile<SelectedShader>(
      "shaders/selected_vertex.glsl", "shaders/selected_fragment.glsl");
  }
};

int main(int argc, char **argv) {
  try {
    BlackEngineApplication application;
    application.start();
  } catch (const std::exception &e) {
    Logger::Get("Initialization example")->critical("Initialization Example error: ", e.what());
    return 1;
  }

  return 0;
}