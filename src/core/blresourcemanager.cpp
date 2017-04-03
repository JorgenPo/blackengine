#include "blresourcemanager.h"
#include "src/utils/bllogger.h"

namespace black {

ResourceManager::
ResourceManager(std::string resPath)
    : m_resources(), m_resourcesPath(resPath)
{

}

ResourceManager::~ResourceManager()
{
    for ( auto &resource : m_resources ) {
        Logger::getInstance() << "unloading resource " << resource.first << '\n';
        unload(resource.first);
    }
}

void ResourceManager::unload(guid_t guid)
{
    m_resources.at(guid).reset();
    m_resources.erase(guid);
}

ResourceLoadException::
ResourceLoadException(ResourceManager::guid_t guid,
              std::__cxx11::string message)
    : m_guid(guid), m_message(message)
{

}

std::__cxx11::string ResourceLoadException::message() const throw()
{
    return std::string("Failed to load resource '" + m_guid + "': " + m_message);
}

}
