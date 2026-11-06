#include <format>
#include <iostream>

static_assert(sizeof(void*) == 8, "This project requires a 64-bit (x64) build.");

int main()
{
    std::cout << "OpenGL-PBR-Renderer\n";

    // Verifies that C++20 is really active: <format> is a C++20 library
    // feature, and __cplusplus is accurate thanks to /Zc:__cplusplus.
    std::cout << std::format("__cplusplus = {}\n", __cplusplus);
    std::cout << std::format("Pointer size = {} bits\n", sizeof(void*) * 8);

#ifdef NDEBUG
    std::cout << "Configuration: Release\n";
#else
    std::cout << "Configuration: Debug\n";
#endif

    return 0;
}
