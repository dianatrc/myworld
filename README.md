# My World

This projects consists of developing a 3D terrain editor, built from scratch in **C** using the **CSFML** graphics library. The program displays a textured 3D map using an isometric projection, allowing users to modify landforms in real-time.

The application delivers a complete interactive experience featuring:
- dynamic map generation
- camera rotation
- zooming and panning
- altitude modification tools (raise, lower, level)
- interactive toolbars with hover tooltips
- audio feedback
- map saving/loading capabilities in .legend format.

## Technical Requirements and Features Implemented
- **Isometric 3D projection:** Mathematical projection transforming 3D grid coordinates into 2D screen space with adjustable camera angles and zoom levels.
- **Textures and Wireframed Terrain:** Dynamic rendering of tiles using vertex arrays and altitude-based textures (water, grass, dirt, snow).
- **Interactive Editing Tools:** Real-time modification of tile altitudes using raise, lower, and level tools selected via an on-screen toolbar or keyboard shortcuts.
- **Dynamic Map Resizing:** Custom map dimensions configurable at runtime using interactive textboxes.
- **Save and Load System:** Persistence layer supporting map export and import via .legend files.
- **Audio and UI Feedback:** Sound effects for clicks and saves, tooltips on hover, and visual button states.
- **Error Handling:** Compliant with standard conventions, handling file I/O errors and resource allocation failures safely.

## Project Structure
- `include/`
    - `iso_proj.h`        # Isometric projection and drawing prototypes
    - `my_world.h`        # Main header file for structures, enums, and functions
- `src/`
    - `camera.c`          # Camera rotation, zoom, offset, and tile navigation
    - `file.c`            # Map save and load file management
    - `iso_proj.c`        # Isometric projection, line drawing, and textured tile rendering
    - `main.c`            # Main game loop, event handling, and input processing
    - `menu.c`            # Start menu interface and state determination
    - `toolbar_utils.c`   # Tooltip help messages and dynamic textboxes
    - `toolbar.c`         # Toolbar rendering, button colors, and tool logic
    - `tools.c`           # Terrain editing tools (raise, lower, and level) and tile coordinate detection
    - `window.c`          # Window creation, video mode settings, and framerate control
- `utils/`                # Asset files including textures (water, grass, dirt, snow, menu picture), fonts (`arial.ttf`), and audio effects
- `Makefile`              # Compilation rules for building (all), cleaning (clean, fclean) and rebuilding (re) the project.
- `README.md`

## Compilation and Usage
**BUILD**
To compile the `my_world` binary using the provided Makefile, run: `make`.
To clean intermediate or target files:
- `make clean`    # Removes object files.
- `make fclean`   # Removes object files and binaries.
- `make re`       # Clean rebuild.

**USAGE**
Run the application executable: ./my_world

**CONTROLS and SHORTCUTS**
- **Mouse Click:** Select tiles, interact with toolbar buttons, and edit terrain altitude.
- **W, A, S, D:** Rotate camera view around X and Y axes.
- **Arrows Keys/Ctrl + Arrows Keys:** Navigate between tiles or pan the camera viewport.
- **Mouse Scroll Wheel/ `+`, `-`:** Zoom in and out of the map.
- **1, 2, 3:** Shortcut keys to select Raise, Lower, and Level tools.
- **Enter:** Confirm map size changes after typing in textboxes.