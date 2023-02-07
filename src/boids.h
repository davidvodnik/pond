#include <glm/glm.hpp>
#include <vector>

class Boids {
public:
    Boids();

    void update(float deltaTime, bool touch, glm::vec3 dir);

    [[nodiscard]] std::vector<glm::vec3> const &get_boids() const;

private:
    std::vector<glm::vec3> boids;
    std::vector<glm::vec3> velocities;
};
