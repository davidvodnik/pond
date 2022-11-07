#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Pond", 0, 0, 640, 480, 0);
    auto surface = SDL_GetWindowSurface(window);

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return 0;
            }
        }
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
