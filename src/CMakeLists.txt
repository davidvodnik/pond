add_executable(pond pond.cc program.cc mesh.cc)
target_link_libraries(pond PRIVATE SDL2::SDL2 libglew_static)
