#include "camera.h"

agl::Camera::Camera()
    : position(0.0f), upvector(0.0f,1.0f,0.0f)
{
    vertical_angle =0.0f;
    horizontal_angle = 0.0f;
    direction = glm::vec3(glm::cos(vertical_angle)*glm::sin(horizontal_angle),
                                   glm::sin(vertical_angle),
                                   glm::cos(vertical_angle)*glm::cos(horizontal_angle));
}

void agl::Camera::move(glm::vec3 offset)
{
    position += offset;
}

void agl::Camera::moveAlongDirection(glm::vec3 offset)
{
    const glm::vec4 right(
                glm::sin(horizontal_angle - glm::radians(90.0f)),
                0.0f,
                glm::cos(horizontal_angle - glm::radians(90.0f)),
                1.0f);

    const glm::vec4 up(glm::cross(glm::vec3(right.x, right.y, right.z),
                                         glm::vec3(direction.x, direction.y, direction.z)), 1.0f);


    position = position + (glm::normalize(direction) * offset.y);
    position = position + (glm::normalize(glm::vec3(right)) * offset.x);
    position = position + (glm::normalize(glm::vec3(up)) * offset.z);

}

void agl::Camera::rotate(float v, float h)
{
    vertical_angle += v;
    horizontal_angle += h;
    direction = glm::vec3(glm::cos(vertical_angle)*glm::sin(horizontal_angle),
                                   glm::sin(vertical_angle),
                                   glm::cos(vertical_angle)*glm::cos(horizontal_angle));

}

glm::mat4 agl::Camera::getMatrix()
{
    return(glm::lookAt(
               position, //camera positionopengl
               position + direction, //point looking at
               upvector
               ));
}

glm::mat4 agl::Camera::getRotationMatrix()
{
    return(glm::lookAt(
               glm::vec3(0.0f), //camera positionopengl
               direction, //point looking at
               upvector
               ));
}

glm::vec3 agl::Camera::getDirection()
{
    return direction;
}

glm::vec3 agl::Camera::getPosition()
{
    return position;
}
