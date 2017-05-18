#ifndef BLCONSTANTS_H
#define BLCONSTANTS_H

namespace black {

/**
 * Static class for containing constants
 *
 * @brief The Constants class
 *
 * @version 1.0 First version
 *
 * @author george popoff <popoff96@live.com>
 * @date 17.03.2017
 */
class Constants
{
public:
    /* Application state */
    static constexpr int APPLICATION_DEVELOP = 0;
    static constexpr int APPLICATION_RELEASE = 1;
    static constexpr int APPLICATION_TESTING = 2;

    static constexpr int APPLICATION_MODE = APPLICATION_DEVELOP;

    /* Application config */
    static constexpr int OPENGL_MAJOR_VERSION = 3;
    static constexpr int OPENGL_MINOR_VERSION = 3;

    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    static constexpr float ASPECT_RATIO = WIDTH / static_cast<float>(HEIGHT);

    static constexpr int FPS = 60;

    static constexpr auto RES_PATH = "resources/";

    static constexpr int VERTEX_ATTR_POSITION = 0;
    static constexpr int VERTEX_ATTR_TEXCOORDS = 1;
    static constexpr int VERTEX_ATTR_NORMAL = 2;
    static constexpr int VERTEX_ATTR_COLOR = 3;

    /* Default reosurces names */
    static constexpr auto DEFAULT_PROGRAM = "shaders/default";
};

}

#endif // BLCONSTANTS_H
