#include "camera.h"
#include "mesh.h"
#include "program.h"

class System {
public:
    System(int width, int height);

    void update();

private:
    Camera camera{};
    Mesh mesh{};
    Program program{};
};