#include <stdio.h>
#include <stdlib.h>        // For rand and srand
#include <time.h>          // Used for time-related functions, like seeding the random number generator with srand(time(0))
#include <conio.h>         // For _kbhit() (to check if a key is pressed) and _getch() (to get the key pressed without waiting)
#include <windows.h>       // For SetConsoleCursorPosition(), for managing the console output position.

// Predefined game board
char board[25][50] =
{   
    "pppppppppppppppppppppppppppppppppppppppppppppppp",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "q                                               q",
    "pppppppppppppppppppppppppppppppppppppppppppppppp"
};

// Snake structure
typedef struct {
    int x[100];               // X-coordinates of the snake body
    int y[100];               // Y-coordinates of the snake body
    int length;               // Length of the snake tracks how many segments the snake has
    char direction;           // Current direction ('w', 'a', 's', 'd') also stores the direction in which the snake is moving 
} Snake;

// Food structure
typedef struct {
    int x;                // X-coordinate of the food
    int y;                // Y-coordinate of the food
} Food;

// Global variables
int gameOver = 0;
int gameStarted = 0;      // A flag to check if the game has started (used to wait for the first key press)
int score = 0;

// Function prototypes
void initializeGame(Snake *snake, Food *food);
void printBoard();
void updateDirection(Snake *snake);
void moveSnake(Snake *snake, Food *food);
void generateFood(Food *food);
void setCursorPosition(int x, int y);
void playEatSound();                       
void playGameOverSound();                 

// Function to position the console cursor (This function moves the cursor to (x, y) in the console)
void setCursorPosition(int x, int y) {
    COORD coord;                     
    coord.X = x;                     
    coord.Y = y;                     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Sound when the snake eats food
void playEatSound() {
    Beep(523, 200); // C note: 523 Hz, 200 ms
}

// Sound effect when the game ends
void playGameOverSound() {
    Beep(440, 300); // A note: 440 Hz, 300 ms
    Beep(349, 300); // F note: 349 Hz, 300 ms
    Beep(330, 300); // E note: 330 Hz, 300 ms
}

// Initialize the game
void initializeGame(Snake *snake, Food *food) {
    gameOver = 0;
    gameStarted = 0;
    score = 0;

    // Initialize snake
    snake->length = 1;
    snake->x[0] = 25;                                  
    snake->y[0] = 12;                                  
    snake->direction = ' ';

    board[snake->y[0]][snake->x[0]] = '@';             

    generateFood(food);                                
}

// Generate food in an empty spot
void generateFood(Food *food) {
    do {
        food->x = rand() % 48 + 1;                     
        food->y = rand() % 23 + 1;                     
    } while (board[food->y][food->x] != ' ');          

    board[food->y][food->x] = '+';                     
}

// Print the entire board
void printBoard() {
    setCursorPosition(0, 0);
    for (int i = 0; i < 25; i++) {
        printf("%s\n", board[i]);
    }
    printf("Score: %d\n", score);
}

// Update direction on user input
void updateDirection(Snake *snake) {
    if (_kbhit()) {                           
        char key = _getch();                  

        if (!gameStarted) {
            gameStarted = 1;
        }

        if ((key == 'w' && snake->direction != 's') ||
            (key == 's' && snake->direction != 'w') ||
            (key == 'a' && snake->direction != 'd') ||
            (key == 'd' && snake->direction != 'a')) {
            snake->direction = key;
        }
    }
}

// Move the snake based on its current direction
void moveSnake(Snake *snake, Food *food) {
    if (!gameStarted) return;

    // Clear the tail from the board
    board[snake->y[snake->length - 1]][snake->x[snake->length - 1]] = ' ';

    // Shift the body backward (start from tail)
    for (int i = snake->length - 1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    // Update head position based on direction
    if (snake->direction == 'w') snake->y[0]--;              
    if (snake->direction == 's') snake->y[0]++;              
    if (snake->direction == 'a') snake->x[0]--;              
    if (snake->direction == 'd') snake->x[0]++;              

    // Check for collision
    if (board[snake->y[0]][snake->x[0]] == 'p' ||            
        board[snake->y[0]][snake->x[0]] == 'q' || 
        board[snake->y[0]][snake->x[0]] == 'o') {            
        gameOver = 1;
        playGameOverSound();                                 
        return;
    }

    // Check if the snake eats the food
    if (snake->x[0] == food->x && snake->y[0] == food->y) {
        score += 10;
        snake->length++;
        generateFood(food);
        playEatSound();                                      
    }

    // Update the snake on the board
    board[snake->y[0]][snake->x[0]] = '@';
    for (int i = 1; i < snake->length; i++) {
        board[snake->y[i]][snake->x[i]] = 'o';
    }
}

// Main function
int main() {
    srand(time(0));

    Snake snake;
    Food food;

    initializeGame(&snake, &food);        
    printBoard();                         

    while (!gameOver) {
        updateDirection(&snake);              
        moveSnake(&snake, &food);             

        setCursorPosition(0, 0);              
        printBoard();                         

        Sleep(150);                           
    }

    setCursorPosition(0, 26);
    printf("\nOhOhh Game Over!!\n Final Score: %d\n", score);
    return 0;
}
