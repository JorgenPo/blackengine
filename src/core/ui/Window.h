/**
*  BlackEngine - all rights are reserved.
*  3D Game Engine
*  Created by Breezesoftware 
**/

#ifndef BLACKENGINE2018_WINDOW_H
#define BLACKENGINE2018_WINDOW_H

#include <core/Exception.h>
#include <utility>
#include <core/render/RenderTarget.h>

namespace black::ui {

    class WindowInitializationException : public Exception {
    public:
        explicit WindowInitializationException(const std::string &message) : Exception(message) {}
    };

    /**
     * An abstraction for window
     */
    class Window : public render::RenderTarget {
    public:
        /**
         * Window display mode
         */
        enum class Mode {
            NORMAL,
            FULL_SCREEN,
            MINIMAL
        };

    protected:
        std::string title;
        int width;
        int height;
        Mode mode;
        bool isShown;
        bool isMaximized;
        bool isMinimized;

    public:
        Window() : title(), width(), height(), mode(Mode::NORMAL),
                  isShown(false), isMaximized(false), isMinimized(false) {
        }

        /**
         * Initialize window
         *
         * @throws WindowInitializationException When failed to initialize window. Message contain a reason.
         */
        virtual void initialize() {};

        /**
         * Run window message loop
         */
        virtual int run() = 0;

        /**
         * Hides the window
         */
        virtual void hide() {
            this->isShown = false;
        }

        /**
         * Shows the window
         */
        virtual void show() {
            this->isShown = true;
        }

        /* Getters and setters */
        const std::string &getTitle() const {
            return title;
        }

        void setTitle(const std::string &title) {
            Window::title = title;
        }

        int getWidth() const {
            return width;
        }

        void setWidth(int width) {
            Window::width = width;
        }

        int getHeight() const {
            return height;
        }

        void setHeight(int height) {
            Window::height = height;
        }

        Mode getMode() const {
            return mode;
        }

        void setMode(Mode mode) {
            Window::mode = mode;
        }

        bool isIsShown() const {
            return isShown;
        }

        void setIsShown(bool isShown) {
            Window::isShown = isShown;
        }

        bool isIsMaximized() const {
            return isMaximized;
        }

        void setIsMaximized(bool isMaximized) {
            Window::isMaximized = isMaximized;
        }

        bool isIsMinimized() const {
            return isMinimized;
        }

        void setIsMinimized(bool isMinimized) {
            Window::isMinimized = isMinimized;
        }
    };

}
#endif //BLACKENGINE2018_WINDOW_H
