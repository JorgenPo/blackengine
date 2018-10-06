//
// Created by popof on 02.10.2018.
//

#ifndef BLACKENGINE_ABSTRACTAPPLICATION_H
#define BLACKENGINE_ABSTRACTAPPLICATION_H

#include <CommonHeaders.h>

namespace black {

    class BLACK_EXPORTED ApplicationInitializationException : public Exception {
    public:
        explicit ApplicationInitializationException(const std::string &message);
    };

    /**
     * Abstract engine application.
     * Concrete subclasses must define some special application loop and window counts.
     */
    class BLACK_EXPORTED AbstractApplication {
    protected:
        std::string name;
        std::shared_ptr<Logger> logger;
        int windowWidth;
        int windowHeight;
        bool isFullScreen;

    public:
        explicit AbstractApplication(const std::string &name, int windowWidth, int windowHeight, bool isFullScreen);
        virtual ~AbstractApplication();

        const std::string &getName() const;

        /**
         * Init an engine and run application.
         */
        void start();

    protected:
        /**
        * Update game logic and scene
        */
        virtual void update() = 0;

    private:
        /**
         * Init all resources
         */
        virtual void initializeResources() = 0;

        /**
         * Start an application
         */
        virtual void run() = 0;
    };
}


#endif //BLACKENGINE_ABSTRACTAPPLICATION_H
