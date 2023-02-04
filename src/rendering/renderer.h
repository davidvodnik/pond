#include "program.h"
#include "mesh.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <vector>

class Renderer {
public:
    Renderer();
    void Render(const std::vector<glm::vec3>& positions, const glm::mat4x4& projectionView);

private:
    Program program{};
    Mesh mesh{};
};
