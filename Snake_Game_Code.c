#include <stdio.h>      // Handles basic input and output, like displaying text on the screen using printf and printing characters with putchar.
#include <stdlib.h>     // Used here for random number functions: rand() generates random numbers for food placement, and srand() helps set a random starting point each time the game runs.
#include <conio.h>      // Manages console input/output, allowing us to detect keyboard presses instantly with _getch() and check if a key is pressed with _kbhit(), without waiting for Enter.
#include <time.h>       // Allows us to access system time, which we use to set a unique starting point for the random number generator with srand(time(0)) so that the game has different food positions each time.
#include <windows.h>    // This is specific to Windows. We use it to control the console, including functions like Sleep() to slow down the game loop and SetConsoleCursorPosition() to prevent screen flickering.


#define COLS 25  // Width of the game board
#define ROWS 25  // Height of the game board
#define MAX_LENGTH 100  // Maximum length the snake can grow

char board[COLS * ROWS];  // This is our game board
int gameOver = 0;         // Flag to check if the game has ended
int score = 0;            // Score goes up as the snake eats food

// Each part of the snake (head and body parts)
struct SnakePart {
    int x, y;  // The position of each part on the board
};

// The Snake itself, storing its parts and length
struct Snake {
    int length;                // Snake's current length
    struct SnakePart parts[MAX_LENGTH];  // Array to keep track of all parts
} snake;

// Struct to represent the food item on the board
struct Food {
    int x, y;       // Food's position
    int isEaten;    // Keeps track if the food is eaten
} food;

// Initializes the board with boundaries and empty spaces
void initializeBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (x == 0 || y == 0 || x == COLS - 1 || y == ROWS - 1) {
                board[y * COLS + x] = '#';  // Set boundaries as walls
            } else {
                board[y * COLS + x] = ' ';  // Fill the rest with spaces
            }
        }
    }
}

// Places the snake on the board, marking head and body
void placeSnakeOnBoard() {
    for (int i = 0; i < snake.length; i++) {
        int x = snake.parts[i].x;
        int y = snake.parts[i].y;
        if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
            board[y * COLS + x] = (i == 0) ? '@' : '*';  // '@' for head, '*' for body
        }
    }
}

// Places the food on the board (if it hasn’t been eaten yet)
void placeFoodOnBoard() {
    if (!food.isEaten && food.x >= 0 && food.x < COLS && food.y >= 0 && food.y < ROWS) {
        board[food.y * COLS + food.x] = '+';  // Food represented by '+'
    }
}

// Handles the display of the board in the console
void printBoard() {
    // Set cursor to the top to avoid screen flicker
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    
    // Show score on top
    printf("Score: %d\n", score);
    
    // Print each cell of the board
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            putchar(board[y * COLS + x]);
        }
        putchar('\n');  // Move to the next line after each row
    }
}

// Moves the snake by updating each part based on the one in front of it
void updateSnakePosition(int dx, int dy) {
    // Shift each body part to follow the one in front
    for (int i = snake.length - 1; i > 0; i--) {
        snake.parts[i] = snake.parts[i - 1];
    }
    // Move the snake's head
    snake.parts[0].x += dx;
    snake.parts[0].y += dy;
}

// Generates a new food item at a random position after it's eaten
void generateNewFood() {
    food.x = 1 + rand() % (COLS - 2);
    food.y = 1 + rand() % (ROWS - 2);
    food.isEaten = 0;  // Reset the food status to not eaten
}

// Checks for collisions with the wall, itself, or food
void checkCollisions() {
    // Wall collision check
    if (snake.parts[0].x == 0 || snake.parts[0].x == COLS - 1 || 
        snake.parts[0].y == 0 || snake.parts[0].y == ROWS - 1) {
        gameOver = 1;  // Game over if it hits a wall
    }

    // Checks if the snake has eaten the food
    if (snake.parts[0].x == food.x && snake.parts[0].y == food.y && !food.isEaten) {
        score += 100;  // Increase score when food is eaten
        food.isEaten = 1;  // Food is now eaten
        generateNewFood();  // Generate a new food item
        if (snake.length < MAX_LENGTH) {
            snake.length++;  // Make the snake longer
        }
    }

    // Checks for collision with itself
    for (int i = 1; i < snake.length; i++) {
        if (snake.parts[0].x == snake.parts[i].x && snake.parts[0].y == snake.parts[i].y) {
            gameOver = 1;  // Game over if it collides with itself
        }
    }
}

// Reads the player's input to control the snake
void processPlayerInput(int *dx, int *dy) {
    if (_kbhit()) {  // Check if a key has been pressed
        switch (_getch()) {  // Get the pressed key
            case 'w': *dx = 0; *dy = -1; break;  // Move up
            case 's': *dx = 0; *dy = 1; break;   // Move down
            case 'a': *dx = -1; *dy = 0; break;  // Move left
            case 'd': *dx = 1; *dy = 0; break;   // Move right
        }
    }
}

// Main function to run the game loop
int main() {
    srand(time(0));  // Seed for random food placement

    // Initialize the snake's starting position and length
    snake.length = 1;
    snake.parts[0].x = COLS / 2;
    snake.parts[0].y = ROWS / 2;
    
    // Place the first food item on the board
    generateNewFood();

    int dx = 0, dy = 0;  // Initial direction

    // Game loop runs until gameOver flag is set
    while (!gameOver) {
        initializeBoard();      // Set up the board for each frame
        placeSnakeOnBoard();    // Place the snake on the board
        placeFoodOnBoard();     // Place the food on the board
        printBoard();  // Print the board to the screen

        processPlayerInput(&dx, &dy);  // Check for any input from the player

        updateSnakePosition(dx, dy);   // Move the snake in the chosen direction

        checkCollisions();  // Check for any collisions

        // Add a small delay to control the game's speed
        Sleep(80);  // Pause for smoother gameplay
    }

    // Display game over message and wait for any key press to exit
    printf("Game Over! Final score: %d\n", score);
    printf("Press any key to exit...\n");
    getch();  // Wait for the player to press a key before closing

    return 0;
}
