#include "boids.h"
#include "camera.h"
#include "rendering/renderer.h"

class System {
public:
    System(int width, int height);

    void resize(glm::ivec2 screenSize);
    void update(float deltaTime, bool touch, int x, int y);

private:
    Camera camera;
    Renderer renderer;
    Boids boids;
};
