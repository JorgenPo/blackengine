#include "blresourcemanager.h"

namespace black {

ResourceManager* ResourceManager::m_instance = nullptr;

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

ResourceManager *ResourceManager::getInstance()
{
    if ( m_instance == nullptr ) {
        m_instance = new ResourceManager("");
    }

    return m_instance;
}

void ResourceManager::setResourcePath(string path)
{
    m_instance->m_resourcesPath = path;
}

void ResourceManager::unload(guid_t guid)
{
    m_resources.at(guid).reset();
    m_resources.erase(guid);
}

}
