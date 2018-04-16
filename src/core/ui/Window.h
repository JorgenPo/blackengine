/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#ifndef BLACKENGINE2018_WINDOW_H
#define BLACKENGINE2018_WINDOW_H

namespace black::ui {

/**
 * An abstraction for window
 */
    class Window {

        /**
         * Window display mode
         */
        enum class Mode {
            NORMAL,
            FULL_SCREEN,
            MINIMAL
        };

    public:
        /**
         * Hides the window
         */
        virtual void show() = 0;

        /**
         * Shows the window
         */
        virtual void hide() = 0;
    };

}
#endif //BLACKENGINE2018_WINDOW_H
