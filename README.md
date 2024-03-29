# so_long

# <img src="./img/game1.png" alt="So_long" width="500">

### Table of Contents

* [Introduction](#introduction)
* [How it Works](#how-it-works)
* [Extras](#extras)
* [Gameplay](#gameplay)
* [Maps](#maps)
* [Installation](#installation)
* [Summary](#summary)

## Introduction
In this project, we'll code a simple 2D game to get familiar with the mlx library and UI in general. In my case, it will be Rabbit.

### Game Rules
The game we choose must follow a set of rules. The executable ``so_long`` will receive a map as the only argument, and this map will have a ``.ber`` filetype.

The file also must follow these rules:
- Only ``P`` *(player)*, ``1`` *(wall)*, ``0`` *(empty)*, ``C`` *(collectible)*, and ``E`` *(exit)* will be accepted characters in our map (except if you add enemies as bonus)
- The map must be rectangular, i.e. all rows must have the same length
- There must be at least one exit, one player, and one collectible on the map
- The map must be closed, i.e. surrounded by walls

If any of these checks fail, the game must end with ``Error\n`` followed by a custom message.

The goal is for the player(s) to collect all the collectibles on the map before going to an exit in the least possible number of steps

## How it Works
For the graphics part of the project we used a library called [MLX42](https://github.com/codam-coding-college/MLX42). It's fairly basic and somewhat limited, but was still fun to use in the project.

<img src="./img/Playing.gif" alt="Instruction" width="500">

### Part 1: reading the map

In this part of the code I checked that the given map was properly opened, that it had a ``.ber`` filetype, and then continued by reading the file one line at a time with [get_next_line](https://github.com/LeonorTu/cursus-projects/tree/main/get_next_line).
Once that was done I filled a struct ``t_game`` with some basic attributes like number of players, exits, collectibles, the width and height of the map, etc. During the reading process I also created a string containing the entire map, whcih was later useful when creating a matrix with ``ft_split`` with ``\n`` as the separator.



### Part 2: starting the game

For this part I took the ``t_game`` and my map matrix to build my main ``t_game`` struct. This struct includes more detailed information about my game state, such a list of pacmans, a list of ghosts, the number of loop repetitions (frames), and other info. From here I initialized a window with the mlx function and started drawing the static elements of the map (walls, spaces and collectibles) on the window. The mlx library, as other graphic libraries, has an infinite loop where the game events happen. From here I check the state of the game to re-print certain elements of the map or to manage special events, such as when Pacman dies or when ghosts are in panic mode.
The ``mlx`` library has hooks, which essentially link certain events on the computer (keypresses, mouse clicks, etc) with functions we implement. In my case I 'hooked' the end of the game function to pressing the ``x`` button to close the window. Also, I used a key hook to link keypresses with pacman's movements.


### Part 3: game mechanics

When the ``ESC``/``Q`` key is pressed, the game ends. If the arrow keys or the ``W``. ``A``, ``S``, ``D`` (or ``↑``, ``←``, ``↓``, ``→``) keys are pressed, every pacman on the map changes its direction and tries to move in that direction. Also, every so often all pacmans will all try to move in the same direction they're headed. This way the arrow/WASD keys just change pacmans' directions to make them move forward till they hit a wall.
Ghosts behave similarly (they're the first bonus: enemies), but instead of responding the keypress, they use a basic algorithm to find the closest pacman and try to catch it. Whenever a pacman is caught by a ghost, the attribute ``pac_dying`` is set to 1 in the ``t_game`` struct and all pacmans die with a short animation.
Ghosts load in seven different colors, and each new ghost will have a different color. To do this, I had to load every sprite of every color with the mlx library and assign a new color to every new ghost with ``ghost_number % number_of_colors``, thus rotating through the list of colors when there are more ghosts than available colors.

Lastly, if a pacman reaches an exit and there are no collectibles left, it will be deleted from the list of players. If all pacmans reach the exit, the game ends and the final score is displayed.


### Part 4: animations

There are several animations throughout the game (it's the other bonus in the project), from pacman's gobbling animation or ghosts' panic mode to pacman's death animation. They are all animated in a similar way: with linked lists. Every node in the list corresponds to an image of the animation. Every so often a function is called which will move to the next image, and if the last one is found, the node resets to the top of the linked list.

Pacman and ghosts move on the map matrix, which is much smaller than the mlx window. For this reason and to make movement smooth it is interesting to keep a position in the matrix (``pos``) and a position on the window (``win_pos``) for every pacman/ghost, and update the position on the window one pixel at a time until ``pos * sprite_size == win_pos``.


## Extras

The pacman game I designed has a few extras we weren't asked to implement, but I thought would make the overall game experience better. Here's a list of the most relevant additions:

- Add custom (simple) chasing algorithm using euclidean distances.
- Ability to restart the game by pressing the ``R`` key
- Ability to exit the game by pressing the ``Q`` key
- Ghosts enter panic mode when there's less than a third of the pacdots remaining. During this time the players will be faster and ghosts will flash for the sake of distraction
- The score is displayed in the classic pacman fonts, instead of the (ugly) builtin fonts from ``mlx_string_put()``
- Arrow keys also move the player
- Add decorating pacman logo centered at the bottom
- Add support for both ``linux`` and ``MacOS``
- Implement several players in a single map
- Ability to save a direction for when it's available
- Added 30 test maps (most of them playable)
- Restrict ending or resetting the game while pacman is dying

## Gameplay

There are a total of 30 maps available. See [MAPS.md](./tests/MAPS.md)

Here are a few sample gameplays from my favorite maps:

## Maps
There are many maps to try your skill/luck. See [Maps](./maps)

## Installation

### Cloning the repositories
```shell
git clone https://github.com/LeonorTu/so_long so_long
cd so_long
make
```

### Downoading and building the MLX42 library

```
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
```

### Usage

```
make                        compiles so_long executable
```
Note: we were not allowed to use multiple threads, thus it is pretty hard to time the speeds of the game. I found that using valgrind on ``linux`` helps slow the game down so it is more similar to the performance in MacOS. Depending on your computer's performance the speed of the game may vary. I hope to learn ways to improve that for future projects. For ``linux``, try always using valgrind as follows: ``valgrind ./so_long <map.ber>``

## Summary
This is a really fun project.
