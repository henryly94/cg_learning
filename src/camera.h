#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cg_learning {

class Camera {
public:

    enum move_direction {
        FRONT,
        BACK,
        LEFT,
        RIGHT
    };

    explicit Camera(glm::vec3 position, glm::vec3 wolrdUp, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    void updatePosition(move_direction dir, float deltaTime);

    void updateFront(float xoffset, float yoffset);

    float speed = 5.0f;
    float sensitivity = 0.1f;
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    
    float yaw;
    float pitch;
    
};

} // namespace cg_learning

#endif // CAMERA_H_
