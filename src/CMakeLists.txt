add_executable(pond pond.cc system.cc program.cc mesh.cc camera.cc boids.cc)
target_link_libraries(pond PRIVATE SDL2::SDL2 libglew_static glm::glm)
