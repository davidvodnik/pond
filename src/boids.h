#include <glm/glm.hpp>
#include <vector>

class Boids {
public:
    Boids();

    void update(float deltaTime, bool touch, glm::vec3 pos);

    [[nodiscard]] std::vector<glm::vec3> const &get_boids() const {
        return positions;
    }

private:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> velocities;
    std::vector<glm::vec3> forces;
};
