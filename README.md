# Snake-Game-Project
Snake Game in C Language.

Our project is a classic Snake Game that offers users the ability to read game instructions, view the top 10 high scorers, and enjoy smooth, engaging gameplay. It’s designed to ensure a seamless and enjoyable experience for players.
Snake is a straightforward game with a simple structure that aligns well with the capabilities of C, making it ideal for beginners or those practicing game development. The Snake Game primarily relies on logical concepts like movement, collision detection, and score calculation, which can be effectively implemented using C's structured programming approach.

DESIGN AND IMPLEMENTATION
1.  Main Menu:
  •	Display options to the player:
    a)	Start Game
    b)	View Top 10 Leaderboard
    c)	View Instructions
    d)	Quit Game
  •	Use arrow keys or other inputs to navigate options.
  •	On selection:
   o Start Game calls the Game Loop.
   o Leaderboard displays the top scores from a file.
   o Instructions explain the game rules and controls.
   o Quit exits the program.
2.  Game Initialization:
   • Reset the snake position, length, score, and game state variables.
   • Randomly generate the initial position of the food.
   • Clear the screen to prepare for gameplay.
5.  Game Loop (Play):
 • Continuously update the game state until the game is over:
    o Draw Game: Display the walls, snake, food, and score on the console.
    o Input Handling: Capture real-time player input for movement (W/A/S/D).
    o Game Logic:
        Move the snake based on input.
        Check for collisions with walls, the snake's tail, or food.
        Update score and snake length if food is eaten.
        End the game if a collision occurs.
    o Add a small delay (using Sleep) to control the game's speed.
7. Scoring and High Scores:
  •	Maintain a leaderboard of the top 10 scores.
  •	After game over:
    o	Prompt the player to enter their name.
    o	Check if the score qualifies for the top 10.
    o	If so, update the leaderboard with the player's score.
  •	Save the updated leaderboard to a file for future sessions.
8.  Game Over and Reset:
  •	Display the "Game Over" screen with the player's final score.
  •	Allow the player to return to the main menu or exit.
9.  File Management for High Scores:
  •	Load High Scores:
    o	On program start, read scores from a file into memory.
  •	Save High Scores:
    o	After each game, write updated scores back to the file.

    ![image](https://github.com/user-attachments/assets/a98a8002-0957-42b1-b5b3-9af96821f37d)
    ![image](https://github.com/user-attachments/assets/6a8dfa2e-918e-4634-9377-c612fef0aed4)
    ![image](https://github.com/user-attachments/assets/70b67b2a-0223-422f-9a5f-4dc3f608dcd1)
    ![image](https://github.com/user-attachments/assets/3e31eccb-cd3c-4b72-8804-aced668acebb)
    ![image](https://github.com/user-attachments/assets/71ffe73e-f49c-40e8-b034-a92a08b465cb)

REFERENCES:
    •	W3schools
    ![url](https://www.w3schools.com/)
    ![url](https://www.geeksforgeeks.org/) 
    ![url](https://youtu.be/t3y2b2_moY8?si=S2XU8SReBuR3KGTL)
