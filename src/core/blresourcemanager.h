#ifndef BLRESOURCEMANAGER_H
#define BLRESOURCEMANAGER_H

#include "blresource.h"

#include <map>
#include <string>
#include <memory>
#include <QFileInfo>

#include "blconstants.h"
#include <blfileexceptions.h>
#include <bllogger.h>

namespace black {

/* Exceptions forward. See bellow. */
class ResourceLoadException;

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
 * @version 1.1.5 02.04.2017
 *
 * @version 1.0 12.03.2017
 *  Working version
 * @version 1.1 19.03.2017
 *  Full support of smart pointers.
 *  Support of full pathes as well as relative.
 *
 */
class ResourceManager
{
public:
    using guid_t = std::string;

public:
    static ResourceManager& getInstance() {
        static ResourceManager instance(Constants::RES_PATH);
        return instance;
    }

    /**
     * @brief Loads resource with given file path.
     *
     * @param path resource file path
     */
    template<class T> string load(std::string path, bool relative = true);

    /**
     * @brief Returns a resource with given file path.
     *  If resource hadn't been loaded yet - loads it.
     *
     * @param guid resource guid to get
     */
    template<class T> std::shared_ptr<T> get(guid_t guid, bool relative = true);

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
string ResourceManager::load(std::string path, bool relative)
{
    auto res = std::make_shared<T>();

    guid_t guid = path;

    // Allow relative and non-relative path
    // cause when loading nested resources there are
    // problems with relative path
    if ( relative ) {
        path = m_resourcesPath + path;
    }

    // Cut absolute path
    size_t resourcePos = path.find("resources");
    if ( resourcePos != std::string::npos ) {
        path = path.substr(resourcePos);
        guid = path.substr(10); // minus resources/ string
    }

    try {
        if ( path.empty() ) {
            throw NoSuchFileException(" ");
        }

        res->load(path);
    } catch(AbstractException &e) {
        try {
            // Force loading
            this->get<T>(res->folderName() + "/" + res->defaultName());
            return res->folderName() + "/" + res->defaultName();
        } catch(...) {
            throw ResourceLoadException(guid, e.message());
        }
    }

    m_resources[path] = res;

    return guid;
}

template<class T>
std::shared_ptr<T> ResourceManager::get(guid_t guid, bool relative)
{
    // If relative - guid += resource path
    if ( relative ) {
        guid = m_resourcesPath + guid;
    }

    try {
        if ( guid.empty() ) {
            // Loading default resource
            guid = m_resourcesPath + load<T>(guid, false);
        }

        m_resources.at(guid);
    } catch (...) {
        try {
            guid = m_resourcesPath + load<T>(guid, false); // Full path already
        } catch(ResourceLoadException &e) {
            // Haven't an idea what to do...
            Logger::getInstance("error") << "CAN'T LOAD RESOURCE " << guid << "! AND NO DEFAULT PROVIDEN!" << std::endl;
            throw e;
        }
    }

    return std::dynamic_pointer_cast<T>(m_resources[guid]);
}

class ResourceLoadException : AbstractException {

public:
    ResourceLoadException(ResourceManager::guid_t guid, std::string message);

    // AbstractException interface
    std::__cxx11::string message() const throw() override;

private:
    std::string m_guid;
    std::string m_message;
};
}
#endif // BLRESOURCEMANAGER_H
