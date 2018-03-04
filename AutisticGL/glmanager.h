#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <SFML/Graphics.hpp>
#include "object.h"
#include "camera.h"
#include "skybox.h"

namespace agl {

    class GLManager
    {
    public:
        GLManager(agl::Camera & camera);
        ~GLManager();

        void create_window(sf::RenderWindow & win);
        void init(float aspect_ratio);
        void reder_obj(agl::Object & obj);
        void render_skybox();
    private:
        agl::Camera & camera;
        glm::mat4 projection_matrix;
    };

}

#endif // GLMANAGER_H
