# Building OpenGL-PBR-Renderer

Supported platform: **Windows 11, x64, Visual Studio 2022**. Tested with MSVC 19.44 (Visual Studio 2022 17.14) and CMake 4.x. CMake 3.28 or newer is required.

## 1. Prerequisites

| Tool | Notes |
|---|---|
| Visual Studio 2022 | Install the **Desktop development with C++** workload. Make sure *MSVC v143*, a *Windows SDK* and *C++ CMake tools for Windows* are included. |
| Git | `winget install Git.Git` |
| CMake 3.28+ | `winget install Kitware.CMake` (open a **new** terminal afterwards so `PATH` updates) |
| Ninja | `winget install Ninja-build.Ninja` |
| vcpkg | See the next section |

## 2. Install vcpkg

Clone vcpkg to a short path. A **full clone** is required, because dependency versions are pinned to a vcpkg commit and need its history.

```bat
git clone https://github.com/microsoft/vcpkg C:\dev\vcpkg
C:\dev\vcpkg\bootstrap-vcpkg.bat -disableMetrics
setx VCPKG_ROOT "C:\dev\vcpkg"
```

`setx` only affects terminals opened afterwards. Visual Studio must also be restarted to see it.

## 3. Get the code

```bat
git clone https://github.com/<Clouddeboi>/OpenGL-PBR-Renderer.git
cd OpenGL-PBR-Renderer
```

## 4. Open an x64 build environment

The project only builds for 64-bit. A plain terminal has no compiler on its `PATH`, and some "Developer" shortcuts default to **x86**, which fails the build by design.

Use the **x64 Native Tools Command Prompt for VS 2022** (Start menu), or run this in a plain `cmd` window:

```bat
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
```

(Replace `Community` with `Professional` or `Enterprise` if applicable.)

Verify:

```bat
cl
echo %VCPKG_ROOT%
```

The `cl` banner must end in `for x64`, and `VCPKG_ROOT` must point to your vcpkg clone. If `VCPKG_ROOT` points inside `Program Files\Microsoft Visual Studio`, override it for this window:

```bat
set VCPKG_ROOT=C:\dev\vcpkg
```

## 5. Configure, build and run

From the repository root, in the x64 prompt:

```bat
cmake --preset windows-debug
cmake --build --preset windows-debug
build\windows-debug\bin\pbr_renderer.exe
```

Expected output:

```
OpenGL-PBR-Renderer
__cplusplus = 202002
Pointer size = 64 bits
Configuration: Debug
```

The first configure downloads and compiles the dependencies through vcpkg. It needs an internet connection and can take several minutes. Later configures reuse vcpkg's binary cache and are fast.

For a Release build, use the `windows-release` preset. The output goes to `build\windows-release`.

## 6. Visual Studio

1. Choose **File → Open → Folder…** and select the repository root. **Open the folder, not individual files**: a file opened on its own has no CMake context, and IntelliSense will show false errors on C++20 code.
2. Wait for *CMake generation finished* in the Output window.
3. Select **Windows x64 Debug** (or Release) from the configuration dropdown.
4. Choose `pbr_renderer.exe` as the startup item and press **Ctrl+F5**.

If the configuration looks stale, use **Project → Delete Cache and Reconfigure**.

## Troubleshooting

| Symptom | Cause and fix |
|---|---|
| `cmake` or `ninja` not recognised | The terminal was opened before the install. Open a new one. |
| `cl` not recognised | You're not in a developer prompt. Follow section 4. |
| `A 64-bit (x64) toolchain is required` or `static_assert failed` | The environment is x86. Open an x64 prompt, delete the `build` folder, and configure again. |
| Compiler path contains `Hostx86` | Same as above. CMake caches the compiler, so the `build` folder must be deleted. |
| PowerShell: *running scripts is disabled* | Use `cmd` and `vcvars64.bat`, or run `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass` first. |
| vcpkg baseline or git errors | `VCPKG_ROOT` probably points to Visual Studio's bundled vcpkg, or your clone is shallow. Use a full clone, and set `VCPKG_ROOT` explicitly. |
| Red squiggles on `std::format` or `static_assert` | The file was opened outside a CMake folder. See section 6. |
| vcpkg fails while building a package | Check your internet connection, then read the log file path that vcpkg prints (under `buildtrees/<package>/`). |

## Dependency versions

Library versions are pinned by the `builtin-baseline` in `vcpkg.json`. Updating dependencies means changing that baseline in its own commit.
