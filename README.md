*This project has been created as part of the 42 curriculum by ntahri and aboulahd.*

# cub3D

## Description

cub3D is a graphics engine written in C, inspired by Wolfenstein 3D (Id Software, 1992). It renders a first-person perspective view of a maze described in a `.cub` scene file, using the raycasting technique.

For each vertical column of the screen, a ray is cast into a 2D grid. The distance to the nearest wall determines the height of the wall stripe drawn on screen, creating the illusion of 3D. Wall textures vary depending on which cardinal direction the wall faces (North, South, East, West), and the floor and ceiling are filled with configurable solid colors.

The engine handles player movement (forward, backward, strafing) and camera rotation in real time, with wall-sliding collision detection.

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

## Resources

### References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — The primary reference for the DDA algorithm, perpendicular distance calculation, and texture mapping pipeline.
- [42 MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) — Getting started with the MiniLibX library.
- [3DSage — Raycasting (YouTube)](https://www.youtube.com/watch?v=gYRrGTC7GtA) — Visual explanation of raycasting fundamentals.
- [javidx9 — DDA Algorithm (YouTube)](https://www.youtube.com/watch?v=NbSee-XM7WA) — Step-by-step walkthrough of the DDA line-stepping algorithm.

### AI usage

AI (Claude, by Anthropic) was used as a learning and review companion throughout the project, for the following tasks:

- **Concept explanation**: understanding the raycasting pipeline, the DDA algorithm, perpendicular distance correction (fisheye), and texture mapping math — before writing any code.

AI was **not** used to generate code that was copy-pasted into the project. All code was written manually, with AI serving as a tool for understanding concepts, catching mistakes, and preparing for the oral defense.
