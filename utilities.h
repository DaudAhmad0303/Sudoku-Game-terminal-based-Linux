#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include <termios.h>
#define no_of_threads 27
void *printSudokuBoard();
void *matrixValidity(void * param);
void *rowValidity(void * param);
void *columnValidity(void * param);
typedef struct {
	int row;
	int column;
}indexes;

void *title();
void *demo();
void *main_menu();
void *subm_menu();
void *edit_menu();
int isValid[no_of_threads];
int sudokuBoard[9][9];
char getch();
char getche();
