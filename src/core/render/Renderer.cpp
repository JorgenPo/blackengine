//
// Created by popof on 19.04.2018.
//

#include "Renderer.h"

namespace black::render {
    black::render::Renderer::Renderer() : renderTargets() {
    }

    void Renderer::addRenderTarget(std::shared_ptr<RenderTarget> target) {
        this->renderTargets.push_back(target);
    }

    void Renderer::removeRenderTarget(std::string name) {
        for (auto &renderTarget : this->renderTargets) {
            if (renderTarget->getName() == name) {
                this->renderTargets.remove(renderTarget);
            }
        }
    }

    RenderTargetList &Renderer::getRenderTargets() {
        return this->renderTargets;
    }
}


