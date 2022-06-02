#include "utilities.h"

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
char getche(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c", buf);
    return buf;
 }
void *printSudokuBoard()
{
	printf("\n\n\t\t\e[%d;%dmSudoku Board\n",1,31);
	for(int i = 0; i < 9; i++)
	{
		if(i % 3 == 0)
			printf("\n\t-------------------------------\n\t");	
		else
			printf("\n\n\t");
		for(int j = 0; j < 9; j++)
		{
			if((j) % 3 == 0)
				printf("|");
			printf(" %d ",sudokuBoard[i][j]);
		}
		printf("|");
	}
	printf("\n\t-------------------------------\e[0m\n");
}

void *matrixValidity(void * param)
{
	//for the validity of 3 x 3 matrix 
	indexes *params = (indexes *) param;
	int r = params->row;
	int c = params->column;
	
	int checkArray[9] = {0};
	for(int i = r; i < r + 3; i++)
	{
		for(int j = c; j < c + 3; j++)
		{
			int value = sudokuBoard[i][j];
			if(value < 1 || value > 9 || checkArray[value - 1] == 1)
			{
				pthread_exit(NULL);
			}
			else
			{
				//Maintaining record for each value occured only once in the whole Row
				checkArray[value - 1] = 1;
			}		
		}
	}
	//Maintaining record for each 3 x 3 matrix in the isValid array
	isValid[r + c/3] = 1;
	pthread_exit(NULL);
}
void *rowValidity(void * param)
{
	//for the validity of row 
	indexes *params = (indexes *) param;
	int r = params->row;
	int c = params->column;
	
	int checkArray[9] = {0};
	for(int i = 0; i < 9; i++)
	{
		int value = sudokuBoard[r][i];
		if(value < 1 || value > 9 || checkArray[value - 1] == 1)
		{
			pthread_exit(NULL);
		}
		else
		{
			//Maintaining record for each value occured only once in the whole Row
			checkArray[value - 1] = 1;
		}
	}
	//Maintaining record for each Row in the isValid array
	isValid[9 + r] = 1;
	pthread_exit(NULL);
}
void *columnValidity(void * param)
{
	//for the validity of column
	indexes *params = (indexes *) param;
	int r = params->row;
	int c = params->column;
	
	int checkArray[9] = {0};
	for(int i = 0; i < 9; i++)
	{
		int value = sudokuBoard[i][c];
		if(value < 1 || value > 9 || checkArray[value - 1] == 1)
		{
			pthread_exit(NULL);
		}
		else
		{
			//Maintaining record for each value occured only once in the whole column
			checkArray[value - 1] = 1;
		}
	}
	//Maintaining record for each column in the isValid array
	isValid[18 + c] = 1;
	pthread_exit(NULL);
}

void *title()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\e[%d;%dm---------------------------------------------------------\n",5,32);
	printf("\t\t\t\t|\t\t\t\t\t\t\t|\n");
	printf("\t\t\t\t|\t\tWelcome to the Sudoku Puzzle\t\t|\n");
	printf("\t\t\t\t|\t\t\t\t\t\t\t|\n");
	printf("\t\t\t\t---------------------------------------------------------\e[0m\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Press Enter Key to continue...!");
	getchar();
}
void *main_menu()
{
	printf("\n\tChoose from Menu");
	printf("\nPress 1: Want a demo");
	printf("\nPress 2: Play now");
	printf("\nPress 3: Exit the Game\n");
}
void *subm_menu()
{
	printf("\n\tChoose from Menu");
	printf("\nPress 1: Submite your puzzle");
	printf("\nPress 2: View your Sudoku Puzzle values");
	printf("\nPress 3: Edit your puzzle\n");
}
void *edit_menu()
{
	printf("\n\tChoose from Menu");
	printf("\nPress 1: Edit Row");
	printf("\nPress 2: Edit Column");
	printf("\nPress 3: Edit Matrix");
	printf("\nPress 4: Edit single value");
	printf("\nPress 5: View your Sudoku Puzzle values");
	printf("\nPress 6: Submite your puzzle\n");
}
void *demo()
{
	int demoBoard[9][9] = {
		{1, 2, 3, 6, 7, 8, 9, 4, 5},
		{5, 8, 4, 2, 3, 9, 7, 6, 1},
		{9, 6, 7, 1, 4, 5, 3, 2, 8},
		{3, 7, 2, 4, 6, 1, 5, 8, 9},
		{6, 9, 1, 5, 8, 3, 2, 7, 4},
		{4, 5, 8, 7, 9, 2, 6, 1, 3},
		{8, 3, 6, 9, 2, 4, 1, 5, 7},
		{2, 1, 9, 8, 5, 7, 4, 3, 6},
		{7, 4, 5, 3, 1, 6, 8, 9, 2}
	};
	printf("\n\e[%d;%dm\t\t\t\t\t\tDemo\n",1, 36);
	printf("Game Rules: \n");
	printf("Rule 1: Each column may contain digits 1 through 9\n");
	printf("Rule 2: Each row may contain digits 1 through 9\n");
	printf("Rule 3: Each 3 x 3 matrix may contain digits 1 through 9\n");
	printf("Note: No value can be repeated in each case specified above\n");
	printf("Here is an example of solved Sudoku Puzzle\n");
	for(int i = 0; i < 9; i++)
	{
		if(i % 3 == 0)
			printf("\n\t-------------------------------\n\t");	
		else
			printf("\n\n\t");
		for(int j = 0; j < 9; j++)
		{
			if((j) % 3 == 0)
				printf("|");
			printf(" %d ",demoBoard[i][j]);
		}
		printf("|");
	}
	printf("\n\t-------------------------------\n");
	printf("Note: You've to enter Row by Row for the first time in this Game\n");
	printf("After that you may edit your values in these orders: \n");
	printf("=>  Row by Row");	
	printf("\t\t=>  Column by Column");
	printf("\t\t=>  In the form of 3 x 3 matrix");
	printf("\t\t=>  A single indexed value\e[0m");
	
	
}

