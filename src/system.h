#include "boids.h"
#include "camera.h"
#include "rendering/mesh.h"
#include "rendering/program.h"

class System {
public:
    System(int width, int height);

    void resize(int width, int height);
    void update(float deltaTime);

private:
    Camera camera{};
    Mesh mesh{};
    Program program{};
    Boids boids{};
};
