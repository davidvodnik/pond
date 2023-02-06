#include "boids.h"
#include "camera.h"
#include "rendering/renderer.h"

class System {
public:
    System(int width, int height);

    void resize(int width, int height);
    void update(float deltaTime, bool touch);

private:
    Camera camera;
    Renderer renderer;
    Boids boids;
};
