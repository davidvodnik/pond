#include <glm/glm.hpp>

struct Camera {
    int width;
    int height;

    [[nodiscard]] glm::mat4 update() const;
    [[nodiscard]] glm::vec3 screenToWorld(glm::mat4 projectionView,
                                          glm::vec2 screenPos,
                                          float distance) const;
};
