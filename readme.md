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

This project utilizes high-quality open-source assets by **Kenney**. These assets allow the focus to remain on the technical implementation of the engine.

| Asset Pack                                                            | Category        | License             |
|-----------------------------------------------------------------------|-----------------|---------------------|
| [Top-Down Tanks Redux](https://kenney.nl/assets/top-down-tanks-redux) | Sprites / Tanks | CC0 (Public Domain) |
| [UI Pack](https://kenney.nl/assets/ui-pack)                           | Interface / HUD | CC0 (Public Domain) |

## 🗺️ Project Roadmap

### 📦 Phase 1: Engine Foundation

* [x] **Window Context:** Initialize SDL3, GLAD, and the OpenGL 3.3 viewport.
* [x] **Shader Wrapper:** Create a C++ class to compile, checks and manage Vertex/Fragment shaders in runtime.
* [x] **Resource Loader:** Implement resource loader class that manages all low-level stuff to make code clean.
* [x] **Camera 2D:** Set up an Orthographic projection matrix via GLM.

### 🎨 Phase 2: Rendering & Entities

* [x] **Sprite Renderer:** Build a generic system to draw textures with rotation and scaling.
* [ ] **Tank Chassis:** Render and move the base tank using WASD/Arrow keys.
* [ ] **Turret Logic:** Implement independent turret rotation that tracks the mouse cursor.
* [ ] **Layering:** Ensure proper draw order (Tracks < Chassis < Turret).

### 🕹️ Phase 3: Gameplay Systems

* [ ] **Projectile Manager:** Create a system to handle bullet spawning and life-cycles.
* [ ] **Collision Engine:** Implement AABB (Axis-Aligned Bounding Box) for walls and tanks.
* [ ] **Level Loading:** Create a simple parser to load level layouts from a file.
* [ ] **Basic AI:** Implement stationary enemy turrets that fire at the player.

### 💎 Phase 4: UI & Polishing

* [ ] **HUD:** Integrate Kenney’s UI Pack for health bars and ammo counters.
* [ ] **Game State:** Implement Main Menu, Playing, and Game Over states.
* [ ] **SFX:** Add basic audio for movement and explosions.
* [ ] **Release Build:** Optimize CMake for distribution.

---

### 📈 Current Milestone

**Status:** `Phase 2: Rendering & Entities`  
**Progress:** `[▓▓▓░░░░░░░] 30%`

<!-- ▓░ -->

## ⚖️ License & Credits

**Author:** Maks Makuta  
**Year:** 2026  
**Code:** MIT License  
**Assets:** CC0 by Kenney.nl
