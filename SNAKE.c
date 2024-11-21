#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 60
#define FILENAME "Highscores.txt"
#define TOP10 10

// Snake and game-related variables
int snaketailx[100], snaketaily[100];
int snaketaillen, gameover, key, score, quit, count;
int x, y, foodx, foody;

typedef struct {
    char name[50];
    int score;
} Highscore;

Highscore scores[TOP10];

// Function declarations
void initGame();
void drawGame();
void handleInput();
void updateGameLogic();
void showGameOver();
void playEatSound();
void playGameOverSound();
void loadHighscores();
void saveHighscores();
void updateHighscores(char name[], int score);
void displayMenu(int selection);
int mainMenu();
void displayInstructions();
void displayTop10();

// Main function
int main() {
    loadHighscores();
    while (mainMenu() == 1) {
        initGame();
        while (!gameover) {
            drawGame();
            handleInput();
            updateGameLogic();
            Sleep(70);
        }
        if (!quit) {
            showGameOver();
        }
    }
    return 0;
}

// Initialize game variables
void initGame() {
    snaketaillen = 0;
    key = 0;
    gameover = 0;
    quit = 0;
    score = 0;

    // Set snake's starting position
    x = WIDTH / 2;
    y = HEIGHT / 2;

    // Generate food position
    do {
        foodx = rand() % WIDTH;
        foody = rand() % HEIGHT;
    } while (foodx == x && foody == y);
}

// Draw the game field, snake, and food
void drawGame() {
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH) {
                printf("|"); // Side walls
            } else if (i == y && j == x) {
                printf("@"); // Snake's head
            } else if (i == foody && j == foodx) {
                printf("*"); // Food
            } else {
                int printed = 0;
                for (int k = 0; k < snaketaillen; k++) {
                    if (snaketailx[k] == j && snaketaily[k] == i) {
                        printf("o"); // Snake's tail
                        printed = 1;
                        break;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    // Score and controls
    printf("Score: %d\n", score);
    printf("Controls: W/A/S/D to move, X to quit.\n");
}

// Handle user input for snake movement
void handleInput() {
    if (_kbhit()) {
        switch (tolower(_getch())) {
            case 'w': if (key != 4) key = 3; break;
            case 'a': if (key != 2) key = 1; break;
            case 's': if (key != 3) key = 4; break;
            case 'd': if (key != 1) key = 2; break;
            case 'x': gameover = 1; quit = 1; playGameOverSound(); break;
        }
    }
}

// Update game logic (snake movement, collisions, scoring)
void updateGameLogic() {
    int prevx = snaketailx[0], prevy = snaketaily[0], tempX, tempY;
    snaketailx[0] = x;
    snaketaily[0] = y;

    for (int i = 1; i < snaketaillen; i++) {
        tempX = snaketailx[i];
        tempY = snaketaily[i];
        snaketailx[i] = prevx;
        snaketaily[i] = prevy;
        prevx = tempX;
        prevy = tempY;
    }

    switch (key) {
        case 1: x--; break; // Left
        case 2: x++; break; // Right
        case 3: y--; break; // Up
        case 4: y++; break; // Down
    }

    // Check for collisions
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        gameover = 1;
        playGameOverSound();
    }
    for (int i = 0; i < snaketaillen; i++) {
        if (snaketailx[i] == x && snaketaily[i] == y) {
            gameover = 1;
            playGameOverSound();
        }
    }

    // Check if the snake eats food
    if (x == foodx && y == foody) {
        score += 10;
        snaketaillen++;
        playEatSound();

        // Spawn new food
        do {
            foodx = rand() % WIDTH;
            foody = rand() % HEIGHT;
        } while (foodx == x && foody == y);
    }
}

// Show game over screen and update highscores
void showGameOver() {
    char name[50];
    printf("\n*** GAME OVER ***\n");
    printf("Your score: %d\n", score);
    printf("Enter your name: ");
    scanf("%49s", name);

    updateHighscores(name, score);
    saveHighscores();
    printf("\nPress any key to return to the menu...");
    getch();
}

// Play sound when snake eats food
void playEatSound() {
    Beep(750, 200);
}

// Play sound when game is over
void playGameOverSound() {
    Beep(440, 300);
    Beep(349, 300);
    Beep(330, 300);
}

// Load highscores from file
void loadHighscores() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        count = 0;
        return;
    }
    count = 0;
    while (fscanf(file, "%49s %d", scores[count].name, &scores[count].score) == 2 && count < TOP10) {
        count++;
    }
    fclose(file);
}

// Save highscores to file
void saveHighscores() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) return;
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
    }
    fclose(file);
}

// Update highscores list
void updateHighscores(char name[], int score) {
    Highscore newscore;
    strncpy(newscore.name, name, sizeof(newscore.name));
    newscore.score = score;

    int i;
    for (i = count; i > 0 && scores[i - 1].score < score; i--) {
        if (i < TOP10) scores[i] = scores[i - 1];
    }
    if (i < TOP10) {
        scores[i] = newscore;
        if (count < TOP10) count++;
    }
}

// Display main menu
int mainMenu() {
    int choice = 1;
    char key;

    displayMenu(choice);
    while (1) {
        key = getch();
        if (key == 80) { // Down arrow
            choice = (choice % 4) + 1;
        } else if (key == 72) { // Up arrow
            choice = (choice == 1) ? 4 : (choice - 1);
        } else if (key == 13) { // Enter
            if (choice == 1) return 1;
            if (choice == 2) displayTop10();
            if (choice == 3) displayInstructions();
            if (choice == 4) return 0;
        }
        displayMenu(choice);
    }
}

// Display menu options
void displayMenu(int selection) {
    system("cls");
    printf("\t\tSNAKE GAME\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("%s START GAME\n", (selection == 1) ? ">" : " ");
    printf("%s TOP 10 LEADERBOARD\n", (selection == 2) ? ">" : " ");
    printf("%s INSTRUCTIONS\n", (selection == 3) ? ">" : " ");
    printf("%s QUIT GAME\n", (selection == 4) ? ">" : " ");
    printf("\nUP and DOWN arrows to scroll. Press ENTER to select.\n");
}

// Display instructions
void displayInstructions() {
    system("cls");
    printf("=-=-=-=-=-=-=-=-=- INSTRUCTIONS -=-=-=-=-=-=-=-=-=\n");
    printf("1. Use W, A, S, D keys to control the snake.\n");
    printf("2. Eat '*' to grow and increase your score.\n");
    printf("3. Avoid walls and the snake's own tail.\n");
    printf("4. Game ends if you collide with the wall or yourself.\n");
    printf("Press any key to return to the menu...");
    getch();
}

// Display top 10 highscores
void displayTop10() {
    system("cls");
    printf("=-=-=-=-=-=-=-= TOP 10 LEADERBOARD =-=-=-=-=-=-=-=\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }
    if (count == 0) printf("No scores available yet.\n");
    printf("Press any key to return to the menu...");
    getch();
}
