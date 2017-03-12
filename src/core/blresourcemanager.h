#ifndef BLRESOURCEMANAGER_H
#define BLRESOURCEMANAGER_H

#include "blresource.h"

#include <map>
#include <string>
#include <memory>

namespace black {

/**
 * @brief The ResourceManager class
 *  Handles all ingame resources such as
 * textures, meshes, models, sounds and so on.
 *
 * Relies on the Service Manager pattern because of
 * private constructor.
 *
 * Stores resources by its relative to the resource
 * directory path called guid.
 *
 * @author george popoff <popoff96@live.com>
 * @date 12.03.2017
 * @version 1.0 Working version
 *
 */
class ResourceManager
{
    using guid_t = std::string;

public:
    static ResourceManager* m_instance;

    static ResourceManager* getInstance();

    static void setResourcePath(string path);

    /**
     * @brief Loads resource with given file path.
     *
     * @param path resource file path
     */
    template<class T> void load(std::string path);

    /**
     * @brief Returns a resource with given file path.
     *  If resource hadn't been loaded yet - loads it.
     *
     * @param guid resource guid to get
     */
    template<class T> T* get(guid_t guid);

    /**
     * @brief Unloading resource by given guid.
     *
     * @param guid resource guid to unload
     */
    void unload(guid_t guid);

    //TODO: friend class ServiceManager;

    // Constructor can be accessed by ServiceManager only
private:
    ResourceManager(std::string resPath);
    ~ResourceManager();

private:
    std::map< guid_t, std::shared_ptr<Resource> > m_resources;

    std::string m_resourcesPath;
};


// TEMPLATE FUNCTIONS

template<class T>
void ResourceManager::load(std::string path)
{
    auto res = std::make_shared<T>(m_resourcesPath + path);
    m_resources[path] = res;
}

template<class T>
T* ResourceManager::get(guid_t guid)
{
    try {
        m_resources.at(guid);
    } catch (std::out_of_range e) {
        load<T>(m_resourcesPath + guid);
    }

    return dynamic_cast<T*>(m_resources[guid].get());
}

}
#endif // BLRESOURCEMANAGER_H
