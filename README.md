## The Game of Life

This is a simple implementation of Conway's "The Game of Life" in the C programming language.
It is written for installation and execution on mac os operating systems.
It uses Raylib for graphics.

Controls:
- 1 - 9: choose a colour
- r: randomise
- b: blank (clear the screen)
- up/down arrow: speed up/slow down the evolution rate, respectively
- - and = keys: zoom out/in, respectively
- spacebar: pause the simulation
- left mouse click: draw new cells
- alt + enter: fullscreen mode (warning, weird behaviour if you alt-tab to another window.)
- ESC: exit

![the game running](https://github.com/mbeavitt/gofl/blob/main/assets/game_running.png?raw=true)

Currently installation is only supported on apple silicon macs. Prebuilt executables will be added
to the app directory at a later date.

Installation from source:

1)
`git clone https://github.com/mbeavitt/gofl/`

2)
`clang -framework IOKit -framework Cocoa -I./src ./src/libraylib.a main.c -o main`
