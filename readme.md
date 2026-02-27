# 🛡️ kTanks

A high-performance, 2D top-down tank shooter built from the ground up using **C++** and **OpenGL**.

The goal of this project is to master low-level game engine architecture, memory management, and real-time rendering without the use of heavy commercial engines.

---

## 🚀 Technical Stack

* **Language:** C++23
* **Graphics API:** OpenGL 3.3 (Core Profile)
* **Windowing & Input:** SDL3
* **OpenGL Loader:** GLAD
* **Math Library:** GLM (OpenGL Mathematics)
* **Logging Library:** spdlog
* **Image Loader:** libspng
* **Font Tessellate library:** Freetype2
* **Assets:** Kenney.nl

## 🎮 Features

* **Entity Component System (ECS) Logic:** Efficient management of tanks, bullets, and walls.
* **AABB Collision Detection:** Custom-coded physics for shells and environmental obstacles.
* **Sprite Rendering:** Optimized 2D batch rendering for tank chassis and turrets.
* **Dynamic UI:** Health bars and ammo counters using specialized UI textures.

## 🛠️ Build Instructions

This project uses **CMake** for build management. Ensure you have a C++23 compatible compiler (MSVC, GCC, or Clang) and CMake 4.1+ installed.

### 1. Prerequisites

You will need the following libraries installed or available in your include path:

* **SDL3** (Windowing and Input)
* **OpenGL** (OpenGL implementation libs for your GPU)
* **GLM** (OpenGL Mathematics)
* **spdlog** (Logging library)
* **Freetype2** (Font loading library)

### 2. Compilation

Run the following commands from the root directory:

```bash
# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile the project
# On Windows (Visual Studio):
cmake --build . --config Release

# On Linux/macOS:
make
```

### 3. Execution

After a successful build, the executable `kTanks` will be located in the `build/` (or `build/Release/`) folder.

```bash
./kTanks
```

---

## 📂 Project Structure

To keep the repository clean, the project follows this standard layout:

```text
├── assets/             # Sprites & UI
├── src/                # Source files (.cpp, .c, .h)
├── libs/               # Libraries sources
├── CMakeLists.txt      # Build configuration
├── license.md          # License text
└── readme.md           # This file
```

## 🎨 Asset Credits

This project utilizes high-quality open-source assets by **Kenney** and **Steve Matteson**. These assets allow the focus to remain on the technical implementation of the engine.

| Asset Pack                                                                  | Category        | License                |
|-----------------------------------------------------------------------------|-----------------|------------------------|
| [Top-Down Tanks Redux](https://kenney.nl/assets/top-down-tanks-redux)       | Sprites / Tanks | CC0 (Public Domain)    |
| [Pixel Platformer Blocks](https://kenney.nl/assets/pixel-platformer-blocks) | Sprites         | CC0 (Public Domain)    |
| [UI Pack](https://kenney.nl/assets/ui-pack)                                 | Interface / HUD | CC0 (Public Domain)    |
| [Open Sans](https://fonts.google.com/specimen/Open+Sans)                    | Font            | SIL Open Font License  |


## ⚖️ License & Credits

**Author:** Maks Makuta  
**Year:** 2026  
**Code:** MIT License  
**Assets:** CC0 by Kenney.nl
