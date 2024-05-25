## Air Hockey Game - README
### Introduction

This project is an Air Hockey game using the ncurses library. The game supports two players, customizable settings, and includes various functionalities such as moving players, scoring, and different difficulty levels.

When you start the game, the welcome screen will be displayed, providing an overview of the scoring system. Press t to start the game.
You will be prompted to enter the slider size, the width of the goal area, and the number of games per level you want to play.

### Controls
#### - Player 1 (Bottom Slider):
Arrow keys to move: Left, Right, Up, Down

#### - Player 2 (Top Slider):
- w/W: Up
- a/A: Left
- s/S: Down
- d/D: Right

### In-Game Commands
- Press P/p to pause and resume the game.
- Press Q/q to quit the game.

### Scoring
- The puck must fully enter the goal area to count as a goal.
- Goals and scores are displayed at the top of the screen.

### Game End
- Each level will end after two minutes so the game can last 6 minutes total
- You can press q at any time to go to the quit confirmation screen
- The Game Over screen displays the points scored by both players, the winner, and the time taken.

### Win-Lose Scenario
- A player wins a level (set) if they win the majority of games in that set.
- The overall winner is the player who wins the majority of levels.

### Best Scores
- The top 10 best scores are saved in ./saves/save_best_10.game.
- The scores are saved after the user quits from the game over screen

### Difficulty Levels
- The ball starts at a default low speed and increases in speed with each level.
- On level 3 (the hardest level) there will be two obstacles on the course



