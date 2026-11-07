# OpenGL-PBR-Renderer

A real-time physically based renderer written from scratch in modern C++ (C++20) and OpenGL 4.6 Core.

The project is a deliberate exercise in graphics programming and software engineering: a small, professionally structured rendering engine with a clean architecture, documented techniques, and a commit history that reads like a maintained project.

> **Status: early development.** The build system and project scaffolding are in place. Nothing renders yet. This README is updated as features land.

## Goals

- Implement physically based rendering with the Cook-Torrance BRDF (GGX, Smith geometry, Schlick Fresnel), with correct colour-space and HDR handling.
- Keep OpenGL isolated behind a small resource layer, so another backend (such as Vulkan) is a realistic future extension.
- Separate CPU-side data (scenes, assets) from GPU resources.
- Measure performance throughout development, and publish only measured numbers.
- Document the mathematics and design decisions alongside the code.

## Planned features

Nothing below is implemented yet.

- **Rendering:** forward pipeline, metallic-roughness PBR, HDR, tone mapping, gamma correction
- **Lighting:** directional, point and spot lights, image-based lighting (irradiance, prefiltered specular, BRDF LUT)
- **Materials:** albedo, normal, metallic, roughness and ambient occlusion maps, with correct sRGB/linear handling
- **Assets:** glTF 2.0 model loading, texture management
- **Shadows:** directional and point-light shadow mapping (cascaded shadow maps as a stretch goal)
- **Tooling:** free-fly camera, Dear ImGui panels, debug views (wireframe, normals, albedo, metallic, roughness, depth, lights), CPU and GPU frame timing, Tracy profiling

## Technology

C++20, OpenGL 4.6 Core, GLFW, GLAD, GLM, Dear ImGui, Assimp, stb_image, Catch2, CMake, vcpkg, RenderDoc, Tracy.

Currently in use: CMake, vcpkg, MSVC, GLFW and GLAD. The rest are added as the commits that need them land.

## Building

Windows 11 and Visual Studio 2022 are required. See [BUILD.md](BUILD.md) for the full instructions. In short:

```bat
cmake --preset windows-debug
cmake --build --preset windows-debug
```

(run from an x64 developer prompt, with `VCPKG_ROOT` set).

## Development approach

Work proceeds in small, independently buildable commits using [Conventional Commits](https://www.conventionalcommits.org/). Each commit should build and be testable on its own.

## Licence

Released under the [MIT License](LICENSE).
