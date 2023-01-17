#include "camera.h"
#include "GL/glew.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 updateCamera(const Camera &camera) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static float angle = 0.0f;
    float x = sin(angle);
    float z = cos(angle);
    angle += 0.01f;

    glm::mat4 view =
        glm::lookAt(glm::vec3(x, 1.0f, z), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(
        40.0f, (float)camera.width / (float)camera.height, 0.1f, 1000.0f);

    return projection * view;
}
