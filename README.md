KanderCraft is a simple Minecraft clone created in C using the Raylib library. The game allows you to explore a voxel-based world, where blocks are rendered with optimizations to ensure smooth gameplay.

## Key Features:
- **Optimization:** Only the outer sides of blocks are rendered, not the internal faces. The game renders only what is visible from the player’s perspective, which helps improve performance.
- **World Generation:** The world is procedurally generated using Perlin noise and stored in a 3D array, containing values 0, 1, 2, and 3, where:
  - `0` = Air
  - `1` = Grass
  - `2` = Dirt
  - `3` = Stone
  


## Controls:

| Action                         | Key          |
|---------------------------------|--------------|
| Move Forward                    | W            |
| Move Left                       | A            |
| Move Backward                   | S            |
| Move Right                      | D            |
| Jump                            | SPACE        |
| Destroy Block (at player’s position) | LEFT Mouse Button |
| Place Block (at player’s position)  | RIGHT Mouse Button |
| Switch Block Type (cycle through block types) | Mouse Wheel |

## Known Issues:
- There are several bugs, such as when the player jumps too high, causing the game to crash due to exceeding the bounds of the array.

## Development Time:
- The game was developed in one day of programming time.
![Snímek obrazovky 2025-02-09 202408](https://github.com/user-attachments/assets/511d0b45-2018-4bec-a001-7fe18b383833)
![Snímek obrazovky 2025-02-09 201931](https://github.com/user-attachments/assets/10432d20-a783-43da-bf47-654547b5ca0f)
![Snímek obrazovky 2025-02-09 202519](https://github.com/user-attachments/assets/eb73270b-50a4-4446-a982-03c0b3af1528)

Jakub Jansa 2025
