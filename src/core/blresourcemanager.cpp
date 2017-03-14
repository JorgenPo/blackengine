#include "blresourcemanager.h"

namespace black {

ResourceManager::
ResourceManager(std::string resPath)
    : m_resources(), m_resourcesPath(resPath)
{

}

ResourceManager::~ResourceManager()
{
    for ( auto &resource : m_resources ) {
        unload(resource.first);
    }
}

void ResourceManager::unload(guid_t guid)
{
    m_resources.at(guid).reset();
    m_resources.erase(guid);
}

}
