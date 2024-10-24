# Cube3D
Cube3D is a [raycasting](https://en.wikipedia.org/wiki/Ray_casting) engine, written in C. It uses similar techniques that were pioneered by Wolfenstein 3D to render a 3D representation of a two-dimensional map.

The engine will render one of four different textures defined in a map file, depending on which way the wall is facing.
![cub3d](https://github.com/user-attachments/assets/fdfd414f-82a2-4cce-837a-2df6c3b27f18)
## Requirements
* Cube3D uses the [MLX42](https://github.com/codam-coding-college/MLX42) graphics library. You may need to adjust the configuration if you are on Windows or Mac OS X for it to compile properly.
* This project was written and tested on Ubuntu Linux, though it should work with other platforms.
* You should run it with one argument, which is a path to a valid map file.
```
$ ./cub3D path/to/map.cub
```
## Map Requirements
Cube3D should work with any map that meets the following requirements:

1. Filename ends with a .cub extension
2. Has four textures defined one per line, with NO SO WE or EA as prefixes (see example)
3. Has F (floor) and C (ceiling) colors defined in RGB format
4. Has walls defined as 1 and open spaces defined as 0
5. Is entirely enclosed by walls
6. Has exactly one player starting location defined as N, E, S or W to define the player's starting orientation
```
NO textures/CRATE_1A.PNG
SO textures/BRICK_1B.PNG
WE textures/BRICK_2A.PNG
EA textures/DOOR_1A.PNG

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000000100000000001
1011110111110101111101111
1000010000010100000100001
1111010111010111110101111
1001010001010000010100001
1011011101111111010111111
100000010000W000010000001
1111011111110111111111011
1000000000010100000000011
1011110111010101111101111
1000010101000001000000001
1111010101111111111101011
1000000000000000000000001
1111111111111111111111111
```
## Features
* Collision management prevents player from walking through walls
* Minimap in upper left corner that shows the player's position and field of view, toggleable by 'm'
![cub3d2](https://github.com/user-attachments/assets/29b9833b-db12-4229-b950-61ed6b1a4038)
* Player can move forward, backward, and strafe with 'WASD'
* Player can rotate the field of view with the left and right arrow keys
## What We Learned
* How to apply triginometric calculations to render 3D graphics using the C math library
* How to scale textures appropriately for walls at all different angles
* How to parse complex maps to ensure invalid maps are rejected 
