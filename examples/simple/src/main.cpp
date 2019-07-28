#include "SelectedShader.h"

#include <application/GameApplication.h>
#include <tracer/RayTracer.h>

#include <iostream>
#include <memory>
#include <terrain/Terrain.h>
#include <terrain/TerrainBuilder.h>


using namespace black;

class BlackEngineApplication : public GameApplication {
  std::shared_ptr<AbstractScene> scene;
  std::shared_ptr<GameObject> hoveredObject;
  std::shared_ptr<GameObject> selectedObject;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Terrain> terrain;
  std::shared_ptr<GameObject> light;
  std::shared_ptr<ApplicationShader> hoveredShader;
  std::shared_ptr<ApplicationShader> selectedShader;
  RayTracer tracer;

  float cameraRadius = 10.0f;
  float cameraSpeed = 0.1f;
  float cameraOffsetX = 0.0f;

  bool rotating = true;
public:
  BlackEngineApplication() :
  GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
    800, 600, false), tracer(camera), scene(new SimpleScene("Test")) {
  }

private:
  void handleInput() {

    if (Input::IsKeyPressed(KEY_LEFT)) {
      this->camera->strafeLeft(0.05f);
    }
    if (Input::IsKeyPressed(KEY_RIGHT)) {
      this->camera->strafeRight(0.05f);
    }
    if (Input::IsKeyPressed(KEY_UP)) {
      this->camera->moveForward(0.1f);
    }
    if (Input::IsKeyPressed(KEY_DOWN)) {
      this->camera->moveBackward(0.1f);
    }

    if (Input::IsKeyPressed(KEY_ESCAPE)) {
      if (this->selectedObject) {
        this->selectedObject->get<ModelComponent>()->setShader(nullptr);
        this->selectedObject = nullptr;
      }

      this->stop();
    }

    if (Input::IsKeyPressed(KEY_ENTER) && hoveredObject) {
      this->selectedObject = this->hoveredObject;
      this->selectedObject->get<ModelComponent>()->setShader(selectedShader);
    }
  }

  std::shared_ptr<GameObject> findSelectedObject(const Ray &ray) {
    for (auto i = scene->getObjects().rbegin(); i != scene->getObjects().rend(); i++) {
      const auto &object = *i;
      if (auto bounds = object->get<BoundingComponent>(); bounds != nullptr) {
        if (bounds->isIntersectsWith(ray)) {
          hoveredObject = object;
          return hoveredObject;
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
      this->light->transform->setPosition({camX, 10.3f, camZ});
    }

    // Reset selected object
    if (this->hoveredObject) {
      this->hoveredObject->get<ModelComponent>()->setShader(nullptr);
      this->hoveredObject = nullptr;
    }

    auto ray = tracer.calculateRay(Input::GetMouseX(), Input::GetMouseY());

    // Set highlighting shader if some object was selected
    if (auto selected = findSelectedObject(ray); selected != nullptr) {
      //logger->debug(fmt::format("Selected object: {}", selectedObject->getName()));
      selected->get<ModelComponent>()->setShader(hoveredShader);
    }

    this->renderer->render(this->scene);
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
    data.lod = 10.0f;

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
    tracer.setCamera(camera);

    scene->setCurrentCamera(camera);
  }

  void loadShaders() {
    this->selectedShader = util::ShaderManager::CreateApplicationShaderFromFile<SelectedShader>(
      "resources/selected_vertex.glsl", "resources/selected_fragment.glsl");
    this->hoveredShader = std::make_shared<SelectedShader>(this->selectedShader);

    this->hoveredShader->setAmbientLight(Color::RED, 0.1f);
    this->selectedShader->setAmbientLight(Color::RED, 0.1f);
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