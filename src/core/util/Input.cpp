//
// Created by popof on 19.11.2018.
//

#include "Input.h"
#include <Engine.h>

namespace black {

    bool Input::IsKeyPressed(Key key) {
        return Input::IsKeyPressed(static_cast<int>(key));
    }

    bool Input::IsKeyPressed(int key) {
        auto systemInterface = Engine::GetCurrentRenderSystem()->getSystemInterface();
        if (!systemInterface) {
            false;
        }

        return systemInterface->isKeyPressed(key);
    }
}