## The Game of Life

This is a simple implementation of Conway's "The Game of Life" in the C programming language.
It is written for installation and execution on mac os operating systems.
It uses Raylib for graphics.

Controls:
- 1 - 9: choose a colour
- r: randomise
- b: blank (clear the screen)
- up/down arrow: speed up/slow down the evolution rate, respectively
- spacebar: pause the simulation
- left mouse click: draw new cells
- alt + enter: fullscreen mode (warning, weird behaviour if you alt-tab to another window.)

![the game running](https://github.com/mbeavitt/gofl/blob/main/assets/game_running.png?raw=true)

If you're using a mac, you can just run the app in the _MAC directory.

Installation from source:

1)
`git clone https://github.com/mbeavitt/gofl/`

2)
`clang -framework IOKit -framework Cocoa libraylib.a main.c -o main`
