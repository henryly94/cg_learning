#include "camera.h"

namespace cg_learning {

namespace {

glm::vec3 GetFrontByYawAndPitch(float yaw, float pitch) {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    return front;
}

} // namespace

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
    : position(position), 
      up(worldUp), 
      yaw(yaw),
      pitch(pitch),
      front(GetFrontByYawAndPitch(yaw, pitch)) {}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::updatePosition(Camera::move_direction dir, float deltaTime) {
    switch (dir) {
        case FRONT:
            position += speed * front * deltaTime;
            break;
        case BACK:
            position -= speed * front * deltaTime;
            break;
        case LEFT:
            position += glm::normalize(glm::cross(up, front)) * speed * deltaTime;
            break;
        case RIGHT:
            position += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
            break;
        default:
            break;
    }
}

void Camera::updateFront(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

}; // namespace cg_learning
