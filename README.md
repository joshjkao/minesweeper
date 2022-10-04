This project is a c++ implementation of minesweeper, a game about using logic to clear a minefield. 
The end goal of this program is to allow the testing and comparing of different solving algorithms:

1. Player game: This is a proof of concept used to ensure the game logic works properly. The program currently can only be interacted with through command line inputs, so playing the game yourself on a large board can be quite cumbersome.

2. Basic Solver: This is the first iteration of the solving algorithm. This version only considers one tile at a time; it uses tile game state, the number of flags already around a tile, and the number of undiscovered neighbors to decide to either flag or dig all neighbors. When no new instructions can be made from the current information, the test is considered inconclusive and terminated.

3. Planned support: More information can be gathered by considering multiple squares at once, and the simplest way to implement this through code is with a system of linear equations. I'm in the process of developing exploring this idea further, starting by writing a simple matrix equation solver. In the future, I plan on implementing this as a second derived class. I will then be able to run both algorithms in succession, keeping track of which is faster and which can solve harder boards. 
