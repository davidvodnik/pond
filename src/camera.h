#include <glm/glm.hpp>

struct Camera {
    int width;
    int height;
};

glm::mat4 updateCamera(const Camera &camera);
