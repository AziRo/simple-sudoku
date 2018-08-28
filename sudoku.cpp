#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <Windows.h>


using namespace std;


#define N 9
#define EMPTY 0
#define PASSED -1


void read(int***& arr)
{
	FILE *file = fopen("input.txt", "r");

	arr = new int** [N];
	
	for(int i = 0; i < N; ++i)
	{
		arr[i] = new int* [N];
		
		for(int j = 0; j < N; ++j)
		{
			arr[i][j] = new int [N+1];
			
			fscanf(file, "%i", &arr[i][j][0]);
			
			for(int k = 1; k <= N; ++k)
			{
				if(!arr[i][j][0]) arr[i][j][k] = k;
				else arr[i][j][k] = EMPTY;
			}
		}	
	}
	
	fclose(file);
}


void print(int*** arr)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i = 0; i < N; ++i)
	{
		if(!(i%3) && i)
		{
			for(int k = 0; k < N * 3 - 4; ++k)
				if(!(k%8) && k) printf("+");
				else printf("-");		
			puts("");
		}
		for(int j = 0; j < N; ++j)
		{
			if(!(j%3)) printf("| ");
			
			if(arr[i][j][1] == PASSED) 
				SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 2));
			else if(!arr[i][j][0]) 
				SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 15));
			else 
				SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
			
			printf("%i ", arr[i][j][0]);
			
			SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 15));
		}
		
		puts("");
	}
}


void printOptions(int* arr)
{
	printf("Options:");
	
	if(arr[1] == PASSED) return;
	
	for(int i = 1; i <= N; ++i)
	{
		if(arr[i] != EMPTY) 
			printf(" %i ", arr[i]);
	}
}


void optionsUpdate(int***& arr)
{
	int offsetRow, offsetColumn;
	int iSquare, jSquare;
	bool check;
	
	for(int i = 0; i < N; ++i)
	{
		offsetRow = i/3 * 3;			
		
		for(int j = 0; j < N; ++j)
		{
			offsetColumn = j/3 * 3;
			
			if(arr[i][j][0] && arr[i][j][1] != PASSED)
			{
				arr[i][j][1] = PASSED;
				for(int k = 0; k < N; ++k)
				{
					iSquare = k / 3 + offsetRow;
					jSquare = k % 3 + offsetColumn;
					
					if(!arr[i][k][0])
					{
						arr[i][k][arr[i][j][0]] = EMPTY;
					}
					if(!arr[k][j][0])
					{
						arr[k][j][arr[i][j][0]] = EMPTY;
					}
					if(!arr[iSquare][jSquare][0])
					{
						arr[iSquare][jSquare][arr[i][j][0]] = EMPTY;
					}
				}
			}
		}
	}
}

void sudoku(int***& arr)
{
	
	bool flag;
	do
	{
		flag = false;
		
		optionsUpdate(arr);
		
		for(int i = 0; i < N; ++i)
		{
			for(int j = 0; j < N; ++j)
			{
				int numbOptions = 0;
				if(!arr[i][j][0]){
					
					for(int k = 1; k <= N; ++k)
						if(arr[i][j][k]) ++numbOptions;
					
					if(numbOptions == 1)
					{
						flag = true;
						for(int k = 1; k <= N; ++k)
						{
							if(arr[i][j][k])
							{
								arr[i][j][0] = arr[i][j][k];
								arr[i][j][k] = EMPTY;
								puts("");
								print(arr);
								//system("pause");
								break;
							}
						}	
					}
				}
			}
		}
	}while(flag);
}


int main()
{
	int*** arr;
	
	read(arr);
	print(arr);
	
	sudoku(arr);
	puts("");
	print(arr);	
}
