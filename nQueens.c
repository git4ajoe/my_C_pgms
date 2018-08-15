#include<stdio.h>
#include<stdlib.h>

//idea of backtracking algorithm understood from geeksforgeeks.

void display_array(int *array,int n);
int place_queens(int *array,int n,int column);
int test_attack(int *array,int n,int row,int column);


void main()
{
	int n,i,j,res;
	
	printf("Enter value of n-->\n");
	scanf("%d",&n);

	int *array =(int *)malloc(n*n*sizeof(int));
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			*(array+i*n+j)=0;



	res=place_queens(array,n,0);

	if(res)
	{
		printf("SUCCESS\n");
		display_array(array,n);
		
	}
	else
	{
		display_array(array,n);
		printf("\nFAILED\n");	
	}
}

void display_array(int *array,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d  ",*(array+i*n+j));
		printf("\n");
	}
}



int place_queens(int *array,int n,int column)
{
	//printf("place_queen(%d)\n",column);

	
	

	//we place column by column;if successfully placed at 0th column then increment
	//and try to place at the next column; if not able to place there then backtrack
	//and try from previous column.


	if(column==n)         //at all columns we placed. 
		return 1;

	int i=0,res=0;
	for(i=0;i<n;i++)
	{
		if(test_attack(array,n,i,column))
		{
			*(array+i*n+column)=1;              //array[i][column]=1;
			
			res=place_queens(array,n,column+1);
			if(res)
				return 1;
			else
				*(array+i*n+column)=0;      //array[i][column]=0;
		}
	}
	
	return 0;		
}



int test_attack(int *array,int n,int row,int column)
{

	int i=0,j=0;
	
//we need to check only the left side of the column we are placing. 
//so first left side row.
	//printf("test_attack(%d,%d)\n",row,column);	
	
	for(i=0;i<column;i++)
		if(*(array+row*n+i)==1)             //if(array[row][i]==1)
			return 0;


//check for diagonals if there are any queens
	i=row;
	j=column;
	while(i>=0 && j>=0)
	{
		i--;
		j--;
		if(*(array+i*n+j)==1)               //if(array[i][j]==1)
			return 0;
	}

	
	i=row;
	j=column;

	while(i<n && j>=0)
	{
		i++;
		j--;
		if(*(array+i*n+j)==1)              //if(array[i][j]==1)
			return 0;
	}

	return 1;

}



