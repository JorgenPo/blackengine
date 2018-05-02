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

            updateRendererView();

            target->setRenderTargetCurrent();
            this->render(objectList);
            target->updateRenderTarget();
        }
    }

    void Renderer::updateRendererView() const {
        if (rendererView != nullptr) {
            rendererView->setAspectRatio(currentRenderTarget->getRenderTargetAspectRatio());
            rendererView->setViewport(
                    {0.0f, currentRenderTarget->getRenderTargetWidth(),
                     0.0f, currentRenderTarget->getRenderTargetHeight()});
        }
    }

    void Renderer::renderToTarget(std::string targetName, const GameEntityList &objectList) {
        for (const auto &target : this->renderTargets) {
            if (target->getRenderTargetName() == targetName) {
                this->currentRenderTarget = target;
                updateRendererView();

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

    const std::shared_ptr<Camera> &Renderer::getRendererView() const {
        return rendererView;
    }

    void Renderer::setRendererView(const std::shared_ptr<Camera> &rendererView) {
        Renderer::rendererView = rendererView;
    }
}


