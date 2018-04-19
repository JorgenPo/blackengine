//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_RENDER_H
#define BLACKENGINE_RENDER_H

#include <memory>
#include <list>
#include "RenderTarget.h"
#include "Object.h"

namespace black::render {
    using RenderTargetList = std::list<std::shared_ptr<RenderTarget>>;

    /**
     * Abstract class for all renderers.
     */
    class Renderer {
        RenderTargetList renderTargets;
    public:
        Renderer();

        virtual std::string getName() = 0;

        void addRenderTarget(std::shared_ptr<RenderTarget> target);
        void removeRenderTarget(std::string name);
        RenderTargetList &getRenderTargets();

        virtual void renderToAllTargets(const ObjectList &objectList) = 0;
        virtual void renderToTarget(std::string targetName) = 0;
    };
}


#endif //BLACKENGINE_RENDER_H
