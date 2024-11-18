#include <stdio.h> //used this to print stuff
#include <stdlib.h> //used to get character from input by getch()
#include <conio.h> //used kbhit() to control snake movement(Important)
#include <ctype.h> //used to make sure the character is lowercase 
#include <windows.h> //sleep() used to allow user to be able to react to snake movement

#define HEIGHT 20
#define WIDTH 60

int snaketailx[100], snaketaily[100]; //snake cords array
int snaketaillen; //stores snake length
// Score and flags
int gameover, key, score;
//coords of snakehead and food
int x, y, foodx, foody;
//plays a sound when game ends
void gameoversound() {
    Beep(440, 300); // A note: 440 Hz, 300 ms
    Beep(349, 300); // F note: 349 Hz, 300 ms
    Beep(330, 300); // E note: 330 Hz, 300 ms
}
//plays a sound when snake eats food
void eatsound() {
    Beep(523, 200); // C note: 523 Hz, 200 ms
}
//intializes coords snake and food
void init() {
	// Flag to signal the gameover
	gameover = 0;
	// Initial coordinates of the snake
	x = WIDTH / 2;
	y = HEIGHT / 2;
	//initial coords of food
	foodx = rand() % WIDTH;
	foody = rand() % HEIGHT;
	while (foodx == 0)
		foodx = rand() % WIDTH;
	while (foody == 0)
		foody = rand() % HEIGHT;
	//score initialized
	score = 0;
}
//draw the bounds, snake and food
void draw() {
	int i, j, k;
	system("cls"); //clearscreen function
	//top wall
	for (i = 0; i < WIDTH + 2; i++)
		printf("#");
	printf("\n");
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j <= WIDTH; j++) {
			//sidewall
			if (j == 0 || j == WIDTH) {
				printf("#");
			}
			//snakehead
			if (i == y && j == x) {
				printf("@");
			}
			//snake food
			else if (i == foody && j == foodx) {
				printf("*");
			} else {
				//last tail part removal
				int tailcheck = 0;
				for (k = 0; k < snaketaillen; k++) {
					if (snaketailx[k] == j && snaketaily[k] == i) {
						printf("o");
						tailcheck = 1;
					}
				}
				if (!tailcheck) {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	//bottom wall
	for (i = 0; i < WIDTH + 2; i++) {
		printf("#");
	}
	printf("\n");
	//print score and instructions
	printf("score = %d\n", score);
	printf("Press W, A, S, D to move.\n");
	printf("Press X to quit the game.");
}
//input function
void input() {
	//direction stored in key
	if (kbhit()) {
		switch (tolower(getch())) {
		case 'a':
			if (key != 2)
				key = 1;
			break;
		case 'd':
			if (key != 1)
				key = 2;
			break;
		case 'w':
			if (key != 4)
				key = 3;
			break;
		case 's':
			if (key != 3)
				key = 4;
			break;
		case 'x':
			gameover = 1;
			gameoversound();
			break;
		}
	}
}
//rule checks(collision and eating) and score
void rules() {
	int i;
	//updating the coords for movement
	int prevx = snaketailx[0];
	int prevy = snaketaily[0];
	int tempx, tempy;
	snaketailx[0] = x;
	snaketaily[0] = y;
	for (i = 1; i < snaketaillen; i++) {
		tempx = snaketailx[i];
		tempy = snaketaily[i];
		snaketailx[i] = prevx;
		snaketaily[i] = prevy;
		prevx = tempx;
		prevy = tempy;
	}
	//direction change
	switch (key) {
	case 1:
		x--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y--;
		break;
	case 4:
		y++;
		break;
	default:
		break;
	}
	//wall hit check
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		gameover = 1;
		gameoversound();
	}
	//collision check
	for (i = 0; i < snaketaillen; i++) {
		if (snaketailx[i] == x && snaketaily[i] == y) {
			gameover = 1;
			gameoversound();
		}
	}
	//update food when consumed
	if (x == foodx && y == foody) {
		foodx = rand() % WIDTH;
		foody = rand() % HEIGHT;
		while (foodx == 0)
			foodx = rand() % WIDTH;
		while (foody == 0)
			foody = rand() % HEIGHT;
		score += 10;
		snaketaillen++;
		eatsound();
	}
}
void main() {
	init();//start variables
	//loop
	while (!gameover) {
		draw();
		input();
		rules();
		Sleep(80); //waits 100ms to give user time to react
	}
}
