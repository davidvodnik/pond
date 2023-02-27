#include "camera.h"
#include "GL/glew.h"
#include <glm/gtc/matrix_transform.hpp>

const float near = 1.0f;
const float far = 1000.0f;

glm::mat4 Camera::update() const {
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static float angle = 0.0f;
    float distance = 80;
    float x = sin(angle) * distance;
    float z = cos(angle) * distance;
    angle += 0.01f;

    glm::mat4 view =
        glm::lookAt(glm::vec3(0, 0, distance), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection =
        glm::perspective(45.0f, (float)width / (float)height, near, far);

    return projection * view;
}

glm::vec3 Camera::screenToWorld(glm::mat4 projectionView, glm::vec2 screenPos,
                                float distance) const {
    float pt_x = (screenPos.x / (float)width) * 2.f - 1.f;
    float pt_y = -(screenPos.y / (float)height) * 2.f + 1.f;

    glm::vec4 pointNear =
        glm::inverse(projectionView) * glm::vec4(pt_x, pt_y, -1.0f, 1.0f);
    pointNear.w = 1.0f / pointNear.w;
    pointNear.x *= pointNear.w;
    pointNear.y *= pointNear.w;
    pointNear.z *= pointNear.w;

    return glm::vec3(0, 0, 80) +
           (glm::vec3(pointNear) - glm::vec3(0, 0, 80)) * 80.0f;
}
