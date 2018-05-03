#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "AutisticGL/container.h"
#include "AutisticGL/functions.h"
#include <memory>

class ResourceManager
{
    static  ResourceManager * instance;
    ResourceManager();
public:
    static ResourceManager& get();
    static void release();

    agl::Container contaiter;
    sf::RenderWindow window;

    glm::vec3 view;
    glm::vec3 projection;
};

#endif // RESOURCEMANAGER_H
