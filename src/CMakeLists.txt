add_executable(pond pond.cc system.cc program.cc mesh.cc camera.cc boids.cc)
if (EMSCRIPTEN)
target_link_libraries(pond PRIVATE glm::glm)
target_compile_options(pond PRIVATE
        "-sUSE_SDL=2"
        "-O2"
    )
target_link_options(pond PRIVATE
        "-sMAX_WEBGL_VERSION=2"
        "-sMODULARIZE=1"
        "-sEXPORT_NAME='Main'"
        "-sINVOKE_RUN=0"
        "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
        "-sEXPORTED_FUNCTIONS=['_main']"
        "-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap']"
        "-sFORCE_FILESYSTEM=1"
        "-sUSE_SDL=2"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASYNCIFY"
        "-O2"
    )
    add_custom_command(
        TARGET pond POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/index.html
                ${CMAKE_BINARY_DIR}/index.html
        )
else()
target_link_libraries(pond PRIVATE SDL2::SDL2 libglew_static glm::glm)
endif()
