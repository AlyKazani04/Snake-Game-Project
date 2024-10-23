#include <stdio.h>

#define rows 20
#define cols 20
#define foodqnty
char board[rows * cols]; //board initialise
int isgameover = 0; //game over flag: off


void fillBoard(){
    int x,y;
    for( y=0; y<rows; y++){
        for( x=0; x<cols; x++){
            if(x==0 || y==0 || x==cols-1 || y==rows-1){
                board[y*cols+x] = '#';
            }
            else{
                board[y*cols+x] = ' ';
            }
        }
    }
}

void PrintBoard(){
	system("cls");
	int x,y;
    printf("Snake Game\n");
    for( y=0; y<rows; y++){
        for( x=0; x<cols; x++){
           putchar(board[y*cols + x]);
        }
        putchar('\n');
    }
}

struct SnakePart{
	int x, y;
};
#define MAX_LENGTH 100
struct Snake {
	int length;
	struct SnakePart body[MAX_LENGTH];
};
struct Snake snake;

void draw_snake(){
	int i;
	for( i = snake.length-1 ; i > 0 ; i--){
		board[snake.body[i].y*cols + snake.body[i].x] = '*';
	}
	board[snake.body[0].y*cols + snake.body[0].x] = '@';

}
struct Food {
	int x , y;
	int consumed;
};	

struct Food food[foodqnty];

void draw_food(){
		
}
void move_snake(int dx , int dy){
	int i;
	for ( i = snake.length-1 ; i > 0 ; i--) {
		snake.body[i] = snake.body[i-1];
	}
	snake.body[0].x += dx;
	snake.body[0].y += dy;
	
	if (snake.body[0].x == 0 || snake.body[0].y == 0 || snake.body[0].x == cols - 1 || snake.body[0].y == rows - 1) {
        isgameover = 1;
    }
}

void keyboard_input(){
	int cha = getch();
	switch (cha) {
		case 'w' : move_snake( 0, -1); break;
		case 'a' : move_snake( -1, 0); break;
		case 's' : move_snake( 0, 1); break;
		case 'd' : move_snake( 1, 0); break;
	}
}

int main(){
	snake.length = 3;
	snake.body[0].x = 5;
	snake.body[0].y = 5;
	snake.body[1].x = 5;
	snake.body[1].y = 6;
	snake.body[2].x = 5;
	snake.body[2].y = 7;
    while(!isgameover){
	    fillBoard();
	    draw_snake();
	    PrintBoard();
	    
	    keyboard_input();
	}
    return 0;
}
