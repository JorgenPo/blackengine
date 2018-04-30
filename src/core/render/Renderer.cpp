//
// Created by popof on 19.04.2018.
//

#include <core/Core.h>
#include "Renderer.h"

namespace black::render {
    black::render::Renderer::Renderer() : renderTargets(), clearColor(Color::WHITE) {
    }

    void Renderer::addRenderTarget(std::shared_ptr<RenderTarget> target) {
        this->renderTargets.push_back(target);
    }

    void Renderer::removeRenderTarget(std::string name) {
        for (auto &renderTarget : this->renderTargets) {
            if (renderTarget->getRenderTargetName() == name) {
                this->renderTargets.remove(renderTarget);
            }
        }
    }

    RenderTargetList &Renderer::getRenderTargets() {
        return this->renderTargets;
    }

    void Renderer::renderToAllTargets(const GameEntityList &objectList) {
        for (const auto &target : this->renderTargets) {
            this->currentRenderTarget = target;
            target->setRenderTargetCurrent();
            this->render(objectList);
            target->updateRenderTarget();
        }
    }

    void Renderer::renderToTarget(std::string targetName, const GameEntityList &objectList) {
        for (const auto &target : this->renderTargets) {
            if (target->getRenderTargetName() == targetName) {
                target->setRenderTargetCurrent();
                this->render(objectList);
                target->updateRenderTarget();
            }
        }
    }

    void Renderer::render(const GameEntityList &objectList) {
        throw NotImplementedException("Renderer::render");
    }

    const Color &Renderer::getClearColor() const {
        return clearColor;
    }

    void Renderer::setClearColor(const Color &clearColor) {
        Renderer::clearColor = clearColor;
    }

    float Renderer::getDeltaTime() const {
        return this->deltaTime;
    }
}


