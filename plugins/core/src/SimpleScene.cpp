//
// Created by popof on 07.05.2018.
//

#include "SimpleScene.h"

namespace black::scene {
    SimpleScene *black::scene::SimpleScene::copy() const {
        return new SimpleScene();
    }
}
