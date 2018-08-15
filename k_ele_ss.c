#include<stdio.h>
#include<stdlib.h>

//logic of finding subsets understood from geeksforgeeks

void display_array(int* array,int n);
void ksubset(int *array,int n,int k);
void print_subsets(int *array,int *subset,int n,int k,int aindex,int sindex);

void main()
{
	int n,k,i;
	printf("Enter values of n and k-->\n");
	scanf("%d%d",&n,&k);


	int* array=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		array[i]=i+1;
	//creating array and putting elements 1...n

	display_array(array,n);

	ksubset(array,n,k);

}



void display_array(int* array,int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d  ",array[i]);
	printf("\n");
}


void ksubset(int *array,int n,int k)
{
	
	int aindex,sindex=0;

//subset array for holding a subset.

	int* subset=(int*)malloc(k*sizeof(int));


	printf("\n------List of subsets------\n");
	print_subsets(array,subset,n,k,aindex,sindex);		
}


void print_subsets(int *array,int *subset,int n,int k,int aindex,int sindex)
{

	int i,j=0;
	
	//printf("fn calls(%d,%d)\n",aindex,sindex);
	
	if (aindex>n)
		return;
	//reached the end of the array.
		
	if (sindex==k)
	{
		for(i=0;i<k;i++)
			printf("%d ",subset[i]);
		printf("\n");
		return;
	}//once subset array is full print the subset.

	
	//for each element there are two possibilities to be part of subset of 
	//not to be. 

	//element included in subset.
	subset[sindex]=array[aindex];
	print_subsets(array,subset,n,k,aindex+1,sindex+1);

	//skipping the current element for a new subset
	print_subsets(array,subset,n,k,aindex+1,sindex);
	
}







