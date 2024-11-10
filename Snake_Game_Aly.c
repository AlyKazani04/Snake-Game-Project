#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define rows 20
#define cols 20
#define MAX_LENGTH 100

char board[rows * cols]; //board initialise
int isgameover = 0; //game over flag: off
int score = 0;

struct SnakePart{
	int x, y;
};

struct Snake{
	int length;
	struct SnakePart body[MAX_LENGTH];
} snake;

struct Food{
	int x , y;
	int consumed;
} food;	

void fill_Board(){
	int x, y;
    for( y = 0; y<rows; y++){
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

void print_Board(){
	COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    
	int x,y;
    printf("Snake Game\n");
    for( y=0; y<rows; y++){
        for( x=0; x<cols; x++){
           putchar(board[y*cols + x]);
        }
        putchar('\n');
    }
    printf("Score: %d\n", score);
}

void draw_Snake(){
	int i, x, y;
	for( i = 0; i < snake.length ; i++){
		x = snake.body[i].x;
		y = snake.body[i].y;
		if(x >= 0 && x < cols && y >= 0 && y < rows){
			board[y * cols + x] = (i==0) ? '@' : '*';
		}
	}
}

void draw_Food(){
	if(!food.consumed && food.x >= 0 && food.x < cols && food.y >= 0 && food.y < rows){
    	board[food.y * cols + food.x] = '+'; 
    }
}

void make_Food(){
	int valid, i;
    do{
        valid = 1;
        food.x = 1 + rand() % (cols - 2);
        food.y = 1 + rand() % (rows - 2);
		for(i = 0; i < snake.length; i++){
			if(snake.body[i].x == food.x && snake.body[i].y == food.y){
				valid = 0;
				break;
			}
		}
	}while(!valid);
	food.consumed = 0;
}

void update_Snake_Pos(int dx , int dy){
	int i;
	for( i = snake.length-1 ; i > 0 ; i--){
		snake.body[i] = snake.body[i-1];
	}
	snake.body[0].x += dx;
	snake.body[0].y += dy;
}

void game_Rules(){
	int i;
	if(snake.body[0].x == 0 || snake.body[0].y == 0 || snake.body[0].x == cols - 1 || snake.body[0].y == rows - 1){
        isgameover = 1;
    }
    
    if(snake.body[0].x == food.x && snake.body[0].y == food.y && !food.consumed){
    	score += 100;
    	food.consumed = 1;
    	make_Food();
    	if(snake.length < MAX_LENGTH){
    		snake.length++;
		}
	}
	for(i = 1; i < snake.length; i++){
		if(snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y){
			isgameover = 1;
		}
	}
}

void input_Processing(int *dx, int *dy){
	char cha;
	if(_kbhit()){
		switch(_getch()){
			case 'w' : *dx = 0; *dy = -1; break;
			case 'a' : *dx = -1; *dy = 0; break;
			case 's' : *dx = 0; *dy = 1; break;
			case 'd' : *dx = 1; *dy = 0; break;
		}	
	}
}

int main(){
	srand(time(0));
	snake.length = 1;
	snake.body[0].x = cols / 2;
	snake.body[0].y = rows / 2;
	
	make_Food();
	int dx = 0, dy = -1;
    while(!isgameover){
	    fill_Board();
	    draw_Snake();
	    draw_Food();
	    print_Board();
	    input_Processing(&dx, &dy);
	    update_Snake_Pos(dx, dy);
	    game_Rules();
	    
	    Sleep(120);
	}
	printf("Game Over!\nFinal Score : %d\n", score);
    return 0;
}
