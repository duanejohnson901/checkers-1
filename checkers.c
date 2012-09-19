//Michael Ehlert
//CS 133U
//Class Project
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
void PrintBoard(int Myboard[8][8]);
int CheckMove(int Myboard[8][8], int x1, int y1, int x2, int y2, int player);

//argc is the number of strings in the argv
//argv is an array of strings that are typed from the cmd prompt or passed to
//you program some other way
//env is the environment strings
//I got this information obtained from programmersheaven.com
int main(int argc,char*argv[], char*env[])
{
    	static int Myboard[8][8] = {{0,1,0,1,0,1,0,1},
                                	{1,0,1,0,1,0,1,0},
                                	{0,1,0,1,0,1,0,1},
                                	{0,0,0,0,0,0,0,0},
                                	{0,0,0,0,0,0,0,0},
                                	{2,0,2,0,2,0,2,0},
                                	{0,2,0,2,0,2,0,2},
                                	{2,0,2,0,2,0,2,0}};
    	int validMove;
    	int x1,y1;
    	int x2,y2;
    	int player = 1;
    	int player1 = 12, player2 = 12;
    	printf("Checkers, World!\n");
    	do {
            	PrintBoard(Myboard);
            	printf("Player %d:\n", player);
            	printf("Enter location From X\n");
            	scanf("%d",&x1);
            	printf("Enter location From Y\n");
            	scanf("%d",&y1);
            	printf("Enter location To X\n");
            	scanf("%d",&x2);
            	printf("Enter location To Y\n");
            	scanf("%d",&y2);

//before moving the piece, you have to check to see if it is a valid move
//if move is valid toggles to other players move
            	validMove = CheckMove(Myboard, x1, y1, x2, y2, player);
            	if (validMove) {
                    	if (validMove == 2) {
                            	Myboard[y1][x1] = 0;
                            	Myboard[(y1+y2)/2][(x1+x2)/2] = 0;
                            	Myboard[y2][x2] = player;
                            	if (player == 1)
                                    	player2--;
                            	else
                                    	player1--;
                    	} else {
                            	Myboard[y1][x1] = 0;
                            	Myboard[y2][x2] = player;
                    	}
                    	player = (player % 2) + 1;
            	} else {
                    	printf("Invalid Move\n");
            	}
    	} while ((player1) > 0 && (player2 > 0));
}

void PrintBoard(int Myboard[8][8])
{
    	int i=0, j=0;
    	for(i = 0; i <= 7; i++)
    	{
            	printf("%d\t", i);
            	for(j = 0; j <= 7; j = j + 1)
                    	printf("%d\t", Myboard[i][j]);
            	printf("\n\n");
    	}
    	printf("\n\t0\t1\t2\t3\t4\t5\t6\t7\n");
}

int CheckMove(int Myboard[8][8], int x1, int y1, int x2, int y2, int player)
{
    	int isjump = 0, xj = 0, yj = 0;

//first, check to see if the piece stays on the board!
    	if ((x1 < 0) || (x2 < 0) || (y1 < 0 ) || (y2 < 0) ||
            	(x1 > 7) || (x2 > 7) || (y1 > 7 ) || (y2 > 7)) {
            	return 0;
    	}

//Check to see that the move is a valid diagonal move
    	if ((abs(x1-x2) != 1) || (abs(y1-y2) != 1)) {

//Next check to see if the move is an attempted jump
            	if ((abs(x1-x2) == 2) && (abs(y1-y2) && 2)) {
                    	isjump = 1;// do jump checking things here
            	} else {
                    	printf("Not a valid diagonal move.\n");
                    	return 0;
            	}
    	}

//check to see if the piece being moved is the player's piece, add an OR statement to see if the piece is a king in the future
    	if (Myboard[y1][x1] != player) {
            	printf("Not your piece.\n");
            	return 0;
    	}

//Check to see if the destination square is unoccupied
    	if (Myboard[y2][x2] != 0) {
            	printf("Destination square occupied!\n");
            	return 0;
    	}

//Check to see if the move is valid for the player
    	if ( ( ((y1-y2) > 0 ) && (player == 1) ) || ( ((y1-y2) < 0 ) && (player == 2) ) ) {

//future place to see if the square is a king
            	printf("Player cannot move in that direction!\n");
            	return 0;
    	}

//Checking if a jump is legal
    	if (isjump) {

//find the middle coordinate
            	xj = (x1 + x2) / 2;
            	yj = (y1 + y2) / 2;
            	if ( (Myboard[yj][xj] == player) && (Myboard[yj][xj] == 0) ) {
                    	printf("The space you are jumping is not occupied by the opposing player.\n");
                    	return 0;
            	} else {
                    	return 2;
            	}
    	}
    	return 1;
}
