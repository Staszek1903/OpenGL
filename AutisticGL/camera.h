#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace agl {

    class Camera
    {
    public:
        Camera();

        void move(glm::vec3 offset);
        void moveAlongDirection(glm::vec3 offset);
        void rotate(float v, float h);
        glm::mat4 getMatrix();
        glm::mat4 getRotationMatrix();
        glm::vec3 getDirection();
        glm::vec3 getPosition();

    protected:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 upvector;
        float vertical_angle, horizontal_angle;
    };

}

#endif // CAMERA_H
