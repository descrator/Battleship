## Battleship Player vs Player
A simple command-line local hotseat multiplayer Battleship game designed for two players. Players take turns secretly placing their ships on a 10x10 grid and then engage in a turn-based tactical battle to guess and bomb the enemy's fleet. Screen-clearing mechanics hide the board between turns so players can share the same keyboard without revealing their positions.

### Features
* **Hotseat Multiplayer**: Automatic screen-clearing hides ship configurations between turns.
* **Ship Fleets**: Each player commands 4 ships of varying lengths (2, 3, 4, and 5 tiles).
* **Dynamic Board Updates**: The board tracks Misses (`_`), Hits (`O`), and fully Sunk ships (which reveal the ship's length number once destroyed).
* **Input Invalidity Handling**: Prevents overlapping ships, out-of-bounds placements, and re-attacking the same coordinates.

### Compilation and Execution
Download the `battleship.c` file from the folder corresponding to your operating system, compile using `gcc` or any standard compiler, and finally run the file.

### How to Play
1. **Setup Phase**: Player 1 enters their ships while Player 2 looks away, and then Player 2 enters their ships while Player 1 looks away.
2. **Coordinates Format**: When prompted for a position, enter a two-digit number corresponding to the `XY` coordinates (e.g, `34` meaning X=3, Y=4).
3. **Orientation**: Choose `H` for Horizontal (ship builds to the right) and `V` for vertical (ship builds downwards).
4. **Battle Phase**: Players take turns entering coordinates to attack.
   `X` = Unexplored Waters
   `_` = Missed Attack
   `O` = Successful Hit
   `2`, `3`, `4`, `5` = A completely sunk ship of that length
5. The game ends when one player completely sinks all 4 of the enemy's ships
Each player should look away while the other player is entering the configuration of his ship.
The game is quite simple; each player enters the position and orientation of their ships on a 10x10 grid, and then tries to guess where the enemy's ships are, and bomb them. 

### Upcoming Features:
A single-player algorithm-based opponent that uses randomness, probability, and statistics to hunt down the player's ships.
