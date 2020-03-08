# Using the developer console and debug menu
To open the developer console, press `~`, and to open the debug menu, press `F1`.

## Debug menu
The debug menu is simple. It has a render frame counter and FPS counter.

## Developer console
The developer console consists of a command log and command prompt with a `Send` button. It accepts Lua as input. Simply type Lua into the prompt and press `Send` or enter. This will execute the command and print the command output onto the log.
### Useful commands:
* `PrintConsole(CURRENT_MODE)` - Print current gamemode.
* `CURRENT_MODE = GAME_MODES.<gamemode>` - Set gamemode.
* `OpenDebugInfo()` - Alternative way to open debug menu.
* `FractalEditor()` - Open fractal editor.
