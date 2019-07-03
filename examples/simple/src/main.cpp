#include <application/GameApplication.h>

#include <Engine.h>
#include <GameEntity.h>
#include <Camera.h>

#include <components/TransformComponent.h>

#include <util/ModelManager.h>
#include <util/Input.h>

#include <iostream>
#include <memory>

using namespace black;

class BlackEngineApplication : public GameApplication {
  std::shared_ptr<GameEntity> gameObject;
  std::shared_ptr<Camera> camera;

  float cameraRadius;
  float cameraSpeed;

public:
  BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
      800, 600, false), cameraRadius(10.0f), cameraSpeed(0.1f) {
  }

private:
  void handleInput() {
    if (Input::IsKeyPressed(Key::KEY_S)) {
      this->cameraRadius += this->cameraSpeed;
    }
    if (Input::IsKeyPressed(Key::KEY_W)) {
      this->cameraRadius -= this->cameraSpeed;
    }
  }

  void update(float dt) override {
    this->handleInput();

    auto time = this->timer->getUptime();

    float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius;
    float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

    this->camera->setPosition({camX, 1.3f, camZ});

    this->renderer->render(this->gameObject, this->camera);
  }

  void initializeResources() override {
    auto modelComponent = ModelManager::CreateFromFile("models/cottage_obj.obj");

    auto frogImage = std::make_shared<Image>("models/cottage_diffuse.jpg", true);
    auto frogTexture = Engine::GetCurrentRenderSystem()->createTexture(
        frogImage, true, TextureFiltering::NEAREST, TextureWrapping::CLAMP_TO_EDGE);

    auto material = std::make_shared<Material>(std::move(frogTexture));

    for (auto &&part : modelComponent->getParts()) {
      part.material = material;
    }

    this->gameObject = std::make_shared<GameEntity>("Frog");
    this->gameObject->add(modelComponent);
    this->gameObject->transform->scale(0.1f);

    this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
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