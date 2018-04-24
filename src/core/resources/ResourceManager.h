//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_RESOURCEMANAGER_H
#define BLACKENGINE_RESOURCEMANAGER_H

#include <list>
#include <string>
#include <map>
#include <memory>
#include <core/FileUtils.h>
#include <core/Logger.h>
#include "Resource.h"

namespace black::resources {

    class ResourceLoadingException : public Exception {
        std::string resource;
    public:
        explicit ResourceLoadingException(const std::string &resource, const std::string &message) : Exception() {
            std::stringstream ss;
            ss << "Error while creating a resource '" << resource << "': " << message;
            this->message = ss.str();
        }

        const std::string &getResource() const {
            return resource;
        }
    };

    class ResourceNotFoundException : public ResourceLoadingException {
        std::list<std::string> searchPaths;

    public:
        explicit ResourceNotFoundException(const std::string &resource, const std::list<std::string> &searchPaths)
                : ResourceLoadingException(resource, "Resource not found"), searchPaths(searchPaths) {
        }

        std::string getSearchPaths() const {
            std::stringstream ss;
            ss << "[";

            auto iter = this->searchPaths.begin();
            do {
                if (iter != this->searchPaths.begin()) {
                    ss << ", ";
                }

                ss << "'" << *(iter++) << "'";
            } while (iter != this->searchPaths.end());

            ss << "]";

            return ss.str();
        }
    };

    /**
     * Manages resources
     */
    class ResourceManager {
    private:
        std::list<std::string> resourceFolders;
        std::map<std::string, std::shared_ptr<Resource>> loadedResources;

    public:
        ResourceManager() {
            // Current directory by default
            resourceFolders.emplace_back("");
        }

        ~ResourceManager() {

        }

        /**
         * Add a single folder to search path
         *
         * @param path Path to the folder
         */
        void addResourceFolder(std::string path) {
            if (!FileUtils::hasTrailingSlash(path)) {
                path.push_back('/');
            }

            this->resourceFolders.emplace_back(path);
        }

        /**
         * Add a list of folder path to search path
         *
         * @param paths List of folders paths
         */
        void addResourceFolders(const std::list<std::string> &paths) {
            for (const auto &path : paths) {
                this->addResourceFolder(std::string(path));
            }
        }

        /**
         * Loads a resource from file. File extension must be included
         * in filename.
         *
         * @tparam ResourceClass Class of resource to be returned
         * @param file File with resource data
         * @return Pointer to the resource
         */
        template<typename ResourceClass>
        std::shared_ptr<ResourceClass> load(std::string file) {
            auto log = Logger::getChannelLogger("ResourceManager");

            log->info("Loading '%v' resource...\n", file);
            log->debug("Search directories: \n");
            for (const auto &directory : this->resourceFolders) {
                log->debug("\"%v\"", directory);
            }

            // If resource was loaded then return it
            if (this->loadedResources.find(file) != this->loadedResources.end()) {
                log->info("Resource '%v' returned from cache\n", file);
                return std::dynamic_pointer_cast<ResourceClass>(this->loadedResources[file]);
            }

            // Resource subclasses must provide a fromFile(std::string) static method
            // If they are not, then compile error will arise
            std::shared_ptr<ResourceClass> resource;
            for (const auto &folder : this->resourceFolders) {
                try {
                    log->debug("Trying to find '%v' resource in '%v' folder...\n", file, folder);
                    resource = ResourceClass::fromFile(folder + file);
                    log->debug("Resource '%v' found in '%v' directory\n", file, folder);
                    break;
                } catch (const FileNotFoundException &e) {
                    log->debug("Resource '%v' not found in '%v' folder\n", file, folder);
                    // Okay, try to load in different location
                } catch (const Exception &e) {
                    throw ResourceLoadingException(file, e.getMessage());
                }
            }

            // File was not found
            if (resource == nullptr) {
                log->info("Resource '%v' not found!\n", file);
                throw ResourceNotFoundException(file, this->resourceFolders);
            }

            log->info("Resource '%v' was loaded!\n", file);
            this->loadedResources[file] = resource;

            return resource;
        }
    };
}


#endif //BLACKENGINE_RESOURCEMANAGER_H
