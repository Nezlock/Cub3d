*This project has been created as part of the 42 curriculum by ntahri and aboulahd.*

# cub3D

## Description

cub3D is a graphics engine written in C, inspired by Wolfenstein 3D (Id Software, 1992). It renders a first-person perspective view of a maze described in a `.cub` scene file, using the raycasting technique.

For each vertical column of the screen, a ray is cast into a 2D grid. The distance to the nearest wall determines the height of the wall stripe drawn on screen, creating the illusion of 3D. Wall textures vary depending on which cardinal direction the wall faces (North, South, East, West), and the floor and ceiling are filled with configurable solid colors.

The engine handles player movement (forward, backward, strafing) and camera rotation in real time, with wall-sliding collision detection.

### Execution pipeline

```
main()
├─ argument validation (argc, .cub extension)
├─ init_all()              zero-initialize all structures
├─ parser()                read the file into an array of lines
├─ parse_config()          dispatch textures/colors, store the map
├─ check_all()             validate paths, colors, map (flood fill)
├─ init_player()           center player in spawn cell, set dir/plane
├─ init_colors()           convert RGB arrays to 0xRRGGBB integers
├─ init_mlx()              X11 connection, window, off-screen image
├─ init_textures_mlx()     load the 4 XPM files into MLX images
├─ setup_hooks()           register keyboard, close, and render callbacks
└─ mlx_loop()              enter the X11 event loop
	 │
	 └─ each frame: render()
	 ├─ move_player()            apply WASD movement + arrow rotation
	 ├─ raycast()                for each screen column x:
	 │    ├─ init_ray_dir()      compute ray direction from camera plane
	 │    ├─ init_ray_step()     compute deltaDist, sideDist, step
	 │    ├─ perform_dda()       walk the grid until a wall is hit
	 │    ├─ calc_wall_height()  perpendicular distance → wall height
	 │    └─ draw_column()       ceiling + textured wall + floor
	 └─ mlx_put_image_to_window()  blit the completed image to screen
```

The entire frame is drawn into an off-screen image buffer before being displayed in a single call, which avoids tearing. The wall distance used for projection is perpendicular to the camera plane (not Euclidean), which corrects the fisheye distortion at screen edges.

## Instructions

### Prerequisites

The project uses the MiniLibX graphics library (included in the source tree) and requires X11 development headers:

```bash
sudo apt install libx11-dev libxext-dev libbsd-dev
```

### Compilation

At the project root:

```bash
make
```

Available Makefile rules: `all`, `clean`, `fclean`, `re`.

### Execution

```bash
./cub3D <path/to/map.cub>
```

The program takes a single argument: a scene description file with the `.cub` extension. If any misconfiguration is encountered, it exits cleanly and prints `Error` followed by an explicit error message to stderr.

### Controls

| Key | Action |
|-----|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera left / right |
| `ESC` | Quit |
| Window close button | Quit |

### Scene file format

A `.cub` file contains six configuration elements followed by the map (always last). Elements can appear in any order and can be separated by empty lines. Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

	1111111111111111111111111
	1000000000110000000000001
	1011000001110000000000001
	1001000000000000000000001
1111111110110000011100000000000001
1000000000110000011101111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Identifiers `NO`, `SO`, `WE`, `EA` specify paths to XPM wall textures for each cardinal direction. `F` and `C` define the floor and ceiling colors as R,G,B values in the range [0, 255]. The map uses six characters: `1` (wall), `0` (empty space), `N`/`S`/`E`/`W` (player spawn position and orientation), and spaces (outside the playable area). The map must be entirely closed by walls.

## Data structures

All structures are declared in `includes/cub3d.h`. The master struct `t_data` is declared on the stack in `main()` and passed by pointer to almost every function. It aggregates all the sub-structures below, plus the map itself.

### `t_data` — master context

Single source of truth for the entire program. Initialized to zero by `init_all()`, cleaned by `free_all()`.

| Field | Type | Role |
|-------|------|------|
| `map` | `char **` | The parsed map, padded to a uniform rectangle. NULL-terminated. |
| `raw_file` | `char **` | Raw lines of the `.cub` file, allocated by `parser()`. Freed in `main` on success, or by `free_all` on any parsing error. |
| `m_raw` | `int` | Number of rows in `map`. |
| `m_col` | `int` | Width of every row in `map` (constant thanks to padding). Used for DDA bounds checking. |
| `player` | `t_player` | Player position, direction, camera plane. |
| `textures` | `t_textures` | Floor/ceiling colors. |
| `path` | `t_path` | Paths to the 4 texture XPM files. |
| `mlx` | `t_mlx` | MiniLibX connection, window, and frame buffer. |
| `keys` | `t_keys` | Keyboard state (one flag per watched key). |
| `tex[4]` | `t_tex` | The 4 loaded wall textures, indexed by `TEX_NO`/`TEX_SO`/`TEX_EA`/`TEX_WE`. |

### `t_player` — player state

Updated each frame by `move_player()`. Position is continuous (not snapped to the grid), direction and plane are unit-length mathematical vectors.

| Field | Type | Role |
|-------|------|------|
| `pos_x`, `pos_y` | `double` | Continuous position in map coordinates. Spawn = cell coordinates + 0.5 (cell center). |
| `dir_x`, `dir_y` | `double` | Unit vector pointing where the player looks. |
| `plane_x`, `plane_y` | `double` | Camera plane vector, always perpendicular to `dir`. Its length (0.66) defines the FOV (~66°). |
| `spawn_dir` | `char` | The spawn letter (`N`, `S`, `E`, `W`) read from the map, used by `init_player()` to compute `dir`/`plane`. |

### `t_ray` — one ray, one screen column

Local to the `raycast()` loop. A fresh instance is built for each of the 1280 screen columns and thrown away at the end of the column.

| Field | Type | Role |
|-------|------|------|
| `camera_x` | `double` | Column position in camera space, `-1` (left) to `+1` (right). |
| `dir_x`, `dir_y` | `double` | Ray direction = `player.dir + player.plane * camera_x`. |
| `map_x`, `map_y` | `int` | Current grid cell being tested by DDA. |
| `delta_dist_x`, `delta_dist_y` | `double` | Distance the ray travels to cross a full cell along each axis, `|1 / ray_dir|`. |
| `side_dist_x`, `side_dist_y` | `double` | Distance from the player to the next X/Y grid edge. Incremented by the delta at each DDA step. |
| `step_x`, `step_y` | `int` | `+1` or `-1`, the direction the ray advances in the grid. |
| `hit` | `int` | Set to 1 when the DDA lands on a wall. |
| `side` | `int` | `0` if the hit face is vertical (E/W wall), `1` if horizontal (N/S wall). Drives both texture selection and distance calculation. |
| `perp_wall_dist` | `double` | Perpendicular distance from the camera plane to the hit point. Drives wall height. Avoids the fisheye effect. |
| `line_height` | `int` | Wall stripe height in pixels, = `WIN_H / perp_wall_dist`. |
| `draw_start`, `draw_end` | `int` | Vertical bounds of the wall stripe, clamped to `[0, WIN_H-1]`. |
| `tex_x` | `int` | Column index inside the wall texture, computed from the exact hit position. |

### `t_mlx` — MiniLibX handles

Allocated by `init_mlx()`. All destroyed together by `free_mlx()` inside `free_all()`.

| Field | Type | Role |
|-------|------|------|
| `mlx` | `void *` | Connection to the X server, returned by `mlx_init()`. |
| `win` | `void *` | Window handle. |
| `img` | `void *` | Offscreen image buffer used for double buffering. |
| `addr` | `char *` | Raw pointer to the image pixel data, returned by `mlx_get_data_addr()`. |
| `bpp` | `int` | Bits per pixel (typically 32). |
| `line_len` | `int` | Bytes per image row — may be larger than `WIN_W * 4` due to memory padding. Used when computing pixel offsets. |
| `endian` | `int` | Byte order of the image (0 = little-endian on x86). |

### `t_keys` — keyboard state

Six flags, each set to 1 on keypress and back to 0 on keyrelease. Read every frame by `move_player()`. This decouples input timing from movement speed and allows several keys to act simultaneously (move forward while turning, etc.).

| Field | Type | Role |
|-------|------|------|
| `w`, `a`, `s`, `d` | `int` | Forward, strafe left, backward, strafe right. |
| `left`, `right` | `int` | Rotate camera left/right (arrow keys). |

### `t_path` — texture file paths

Populated by `fill_path()` (with leading/trailing whitespace trimmed) during config parsing. Each path is a `ft_strdup` duplicate, freed by `free_all()`.

| Field | Type | Role |
|-------|------|------|
| `north`, `south`, `east`, `west` | `char *` | Path to the XPM file for each cardinal wall direction. |

### `t_textures` — floor and ceiling colors

Populated by `fill_color()`. RGB components are initialized to `-1` as a sentinel — this lets `dispatch()` detect duplicate `F`/`C` lines and `check_color()` detect missing entries.

| Field | Type | Role |
|-------|------|------|
| `floor[3]` | `int` | Raw R, G, B components of the floor color, in `[0, 255]`. |
| `ceiling[3]` | `int` | Raw R, G, B components of the ceiling color. |
| `floor_color` | `int` | Pre-packed `0xRRGGBB` value, computed once by `init_colors()` and written directly via `put_pixel`. |
| `ceiling_color` | `int` | Same, for the ceiling. |

### `t_tex` — a loaded wall texture

One instance per cardinal direction, stored in `data.tex[4]`. Mirrors the layout of an MLX image so that pixels can be sampled with the same offset formula as the frame buffer.

| Field | Type | Role |
|-------|------|------|
| `img` | `void *` | Image handle returned by `mlx_xpm_file_to_image()`. |
| `addr` | `char *` | Raw pixel data pointer. |
| `width`, `height` | `int` | Texture dimensions in pixels, filled by `mlx_xpm_file_to_image()`. |
| `bpp`, `line_len`, `endian` | `int` | Same semantics as the fields of the same name in `t_mlx`. |

## Resources

### References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — The primary reference for the DDA algorithm, perpendicular distance calculation, and texture mapping pipeline.
- [42 MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) — Getting started with the MiniLibX library.
- [3DSage — Raycasting (YouTube)](https://www.youtube.com/watch?v=gYRrGTC7GtA) — Visual explanation of raycasting fundamentals.
- [javidx9 — DDA Algorithm (YouTube)](https://www.youtube.com/watch?v=NbSee-XM7WA) — Step-by-step walkthrough of the DDA line-stepping algorithm.

### AI usage

AI (Claude, by Anthropic) was used as a learning and review companion throughout the project, for the following tasks:

- **Concept explanation**: understanding the raycasting pipeline, the DDA algorithm, perpendicular distance correction (fisheye), and texture mapping math — before writing any code.

AI was **not** used to generate code that was copy-pasted into the project. All code was written manually, with AI serving as a tool for understanding concepts.
