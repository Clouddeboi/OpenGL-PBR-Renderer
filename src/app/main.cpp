#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <format>
#include <iostream>

static_assert(sizeof(void*) == 8, "This project requires a 64-bit (x64) build.");

// Proves GLAD was generated with the OpenGL 4.6 API (see vcpkg.json features).
#ifndef GL_VERSION_4_6
#error "GLAD was generated without OpenGL 4.6 support."
#endif

int main()
{
    std::cout << "OpenGL-PBR-Renderer\n";

    // Verifies that C++20 is really active: <format> is a C++20 library
    // feature, and __cplusplus is accurate thanks to /Zc:__cplusplus.
    std::cout << std::format("__cplusplus = {}\n", __cplusplus);
    std::cout << std::format("Pointer size = {} bits\n", sizeof(void*) * 8);

    // glfwGetVersionString() works without glfwInit(), so this only proves
    // that the GLFW headers compile and the library links.
    std::cout << std::format("GLFW: {}\n", glfwGetVersionString());

    // Taking the address of a GLAD function forces the linker to resolve it,
    // proving GLAD is linked. Nothing is called: there is no GL context yet.
    [[maybe_unused]] const auto loadGL = &gladLoadGL;

#ifdef NDEBUG
    std::cout << "Configuration: Release\n";
#else
    std::cout << "Configuration: Debug\n";
#endif

    return 0;
}
