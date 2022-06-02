#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include "utilities.h"
#define ALLOWED_TIME 300

//Here we're creating an Array of size 27 for keeping the record of each thread
int isValid[no_of_threads] = {0};
int sudokuBoard[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int main()
{
	int sl, ch1, ch2, ch3, r_num, c_num, val=0, result=0;
	clock_t start_time = 0;
	char temp, value[5];
	
	//Welcome screen
	title();
	//printf("\e[2J");
	restart:
	
	main_menu();
	printf("Enter your choice: ");
	scanf("%d",&sl);
	switch(sl)
	{
		case 1:
			demo();
			printf("\nPress any key to return...\n");
			getch();
			goto restart;
			break;
		case 2:
			printf("\nYour Time has started Now, you have total of 5 mins.\n");
			start_time = time(NULL);
			printf("\nEnter values for Sudoku Puzzle row by row");
			for(int i = 0; i < 9; i++)
			{
				printf("\nEnter for Row %d: ",i+1);
				for(int j = 0; j < 9; j++)
				{
					 temp = getche();
					 printf(" ");
					 value[0] = temp;
					 value[1] = '\0';
					 //printf("atoi value%d",atoi(value));
					 if(atoi(value) < 1 || atoi(value) > 9)
					 {
					 	printf("\nInvalid value \'%c\'\nRe-enter...!",temp);
					 	i--;
					 	break;
					 }
					 sudokuBoard[i][j]=(int)temp-48;


					 //scanf("%d",&sudokuBoard[i][j]);
				}
			}
			printf("\n\n\tValues entered successfully...\n");
			resubm:
			
			subm_menu();
			printf("Enter your choice: ");
			//scanf("%d",&ch1);
			temp = getche();
			printf(" ");
			value[0] = temp;
			value[1] = '\0';
			
			if(atoi(value) < 1 || atoi(value) > 9)
			{
				printf("\nInvalid value \'%c\'\nRe-enter...!\n",temp);
				goto resubm;
			}
			ch1 = (int)temp-48;
			switch(ch1)
			{
				case 1:
					goto submit;
					break;
				case 2:
					printSudokuBoard();
					goto resubm;
					break;
				case 3:
					re_edit:
					
					edit_menu();
					//Edit values code here
					printf("Enter your choice: ");
					scanf("%d",&ch2);
					switch(ch2)
					{
						case 1:
							//Edit Row values here
							printf("Enter Row Number: ");
							scanf("%d",&ch3);
							printf("Enter Values: ");
							for(int i = 0; i < 9; i++)
							{
								scanf("%d",&sudokuBoard[ch3-1][i]);
							}
							printf("\nValues Entered press any key to return...\n");
							getch();
							goto re_edit;
							break;
						case 2:
							//Edit Column values here
							printf("Enter Column Number: ");
							scanf("%d",&ch3);
							printf("Enter Values: ");
							for(int i = 0; i < 9; i++)
							{
								scanf("%d ",&sudokuBoard[i][ch3-1]);
							}
							printf("\nValues Entered press any key to return...\n");
							getch();
							goto re_edit;
							break;
						case 3:
							//Edit Matrix values here
							printf("Enter Matrix Number: ");
							scanf("%d",&ch3);
							printf("Enter Values: ");
							switch(ch3)
							{
								case 1:
									for(int i = 0; i < 3; i++)
										for(int j = 0; j < 3; j++)
											scanf("%d", &sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 2:
									for(int i = 0; i < 3; i++)
										for(int j = 3; j < 6; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 3:
									for(int i = 0; i < 3; i++)
										for(int j = 6; j < 9; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 4:
									for(int i = 3; i < 6; i++)
										for(int j = 0; j < 3; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 5:
									for(int i = 3; i < 6; i++)
										for(int j = 3; j < 6; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 6:
									for(int i = 3; i < 6; i++)
										for(int j = 6; j < 9; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 7:
									for(int i = 6; i < 9; i++)
										for(int j = 0; j < 3; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 8:
									for(int i = 6; i < 9; i++)
										for(int j = 3; j < 6; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								case 9:
									for(int i = 6; i < 9; i++)
										for(int j = 6; j < 9; j++)
											scanf("%d",&sudokuBoard[i][j]);
									printf("\nValues Entered press any key to return...\n");
									getch();
									goto re_edit;
									break;
								default:
									printf("\nInvalid input...\n");
									goto re_edit;
									break;
							}
							break;
						case 4:
							printf("\nEnter row number: ");
							scanf("%d",&r_num);
							printf("\nEnter Column number: ");
							scanf("%d",&c_num);
							printf("\nEnter Value: ");
							scanf("%d",&val);
							sudokuBoard[r_num-1][c_num-1] = val;
							printf("\nValue Entered press any key to return...\n");
							getch();
							goto re_edit;
							break;
						case 5:
							printSudokuBoard();
							goto re_edit;
							break;
						case 6:
							goto submit;
							break;
						default:
							printf("\nInvalid input\n");
							goto re_edit;
							break;
					}
					break;
				default:
					printf("\nInvaid input... \n");
					goto resubm;					
			}		
			break;
		case 3:
			goto endprog;
			break;
		default:
			printf("\nInvalid Input...\n");
			goto restart;
			break;
	}
	submit:
	printf("Testing values and counting time...\n");
	clock_t end_time = 0;
	end_time = time(NULL);
	unsigned int diff = end_time - start_time;
	if(diff >= ALLOWED_TIME)
	{
		printf("\e[%d;%dmYou're out of time\nTry Better next Time...\e[0m\n",4, 31);
		goto endprog;
	}
	pthread_t tid[no_of_threads];
	int th_ind = 0;
	//Here we're creating 9 threads for 9 rows, 9 threads for 9 columns, and 9 threads 
	//for 9 3x3 matrices or sub-board you can say.
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			//for columns
			if(i == 0)
			{
				indexes *colData = (indexes *) malloc(sizeof(indexes));
				colData->row = i;
				colData->column = j;
				pthread_create(&tid[th_ind++], NULL, columnValidity, colData);
			}
			//for rows
			if(j == 0)
			{
				indexes *rowData = (indexes *) malloc(sizeof(indexes));
				rowData->row = i;
				rowData->column = j;
				pthread_create(&tid[th_ind++], NULL, rowValidity, rowData);
			}
			//for matrices
			if(i % 3 == 0 && j % 3 == 0)
			{
				indexes *matrixData = (indexes *) malloc(sizeof(indexes));
				matrixData->row = i;
				matrixData->column = j;
				pthread_create(&tid[th_ind++], NULL, matrixValidity, matrixData);
			}
		}
	}	
	
	//Now waiting for all threads to finish its working
	for(int i = 0; i < no_of_threads; i++)
	{
		pthread_join(tid[i], NULL);
	}
	for(int i = 0; i < 27; i++)
	{
		if(isValid[i] != 1)
			result = 1;
	}
	printf("You have taken \e[%d;%dm %dMins. %d Seconds\e[0m to Solve the Puzzle\n", 4, 32, diff/60, diff%60);
	if(result == 0)
		printf("\n\e[%d;%dmYour Submitted Solution is Absolutly Correct...\e[0m\n",7,32);
	else
	{
		printf("\n\e[%d;%dmYour Submitted Solution is not Correct...\e[0m\n",7,31);
		printf("Errors are in: \n");
		for(int i = 0; i < 27; i++)
		{
			if(isValid[i] == 0 && i < 9)
				printf("%d Matrix, ",i+1);
			else if(isValid[i] == 0 && i >= 9 && i < 18)
				printf("%d Row, ",i-8);
			else if(isValid[i] == 0 && i >= 18 && i < 27)
				printf("%d Column.",i-17);
		}
	}
	printf("\n");
	endprog:
	printf("Press any Key to close the Application...!\n");
	getch();
	return 0;
}

