//
// Created by popof on 07.05.2018.
//

#ifndef BLACKENGINE_SIMPLESCENE_H
#define BLACKENGINE_SIMPLESCENE_H

#include <core/scene/Scene.h>

namespace black::scene {
    /**
     * Simple scene Implementation
     */
    class SimpleScene : public Scene {
    public:
        SimpleScene *copy() const override;
    };
}


#endif //BLACKENGINE_SIMPLESCENE_H
