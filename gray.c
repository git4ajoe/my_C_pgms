#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void grayN(int n);
void print_initial(int *garray,int n);
void reflect_gray(int *garray,int n,int loop);
void prefix_gray(int *garray,int n,int loop);
void print_gray(int *garray,int n,int m);


void main()

{
	int n;
	printf("gray code of length n(>0)--Enter n value-->\n");
	scanf("%d",&n);

	grayN(n);
}

//function for computing n-bit gray code

void grayN(int n)
{

	int m,i=2,k;
	if (n<=0) return;
	m=pow(2,n);

//create dynamic 2d array for storing gray code
	
	int* garray =(int*) malloc(n*m*sizeof(int));

//putting the one length gray code in the array at LSB
	
	print_initial(garray,n);

//Continuing gray code generation in loop till required n

	while (i<=n)
		{
			
			reflect_gray(garray,n,i);
			prefix_gray(garray,n,i);
			i++;
					
		}

	print_gray(garray,n,m);

}



void print_initial(int *garray,int n)
{
	int i=0;
	printf("\nin initial fn\n");	
//	reaching the lsb

	while(i<n-1)
		i++;


	*(garray+0*n+i)=0;  //	garray[0][i]=0;
	*(garray+1*n+i)=1;  //	garray[1][i]=1;

	
}



void reflect_gray(int *garray,int n,int loop)
{
	int a,b,i,j,counter=0,m;

	printf("\nreflect(%d,%d)\n",n,loop);

	m=pow(2,loop);
	b=pow(2,loop-1);
	a=n-1;
	
	
	for(i=0;i<b;i++)
	{
		counter=0;
		j=a;
		while(counter<(loop-1))
		{
			*(garray+(m-1-i)*n+j) = *(garray+i*n+j); //garray[m-1-i][j]=garray[i][j];
			counter++;
			j--;

			printf("\ninside reflectloop %d--row %d\n",counter,i);
		}
	}
}


void prefix_gray(int *garray,int n,int loop)
{
	int i,b,m;

	printf("\nprefix(%d,%d)\n",n,loop);

	m=pow(2,loop-1); //halfway
	b=pow(2,loop);   //2^n for current loop
	
	for(i=0;i<m;i++)
		*(garray+i*n+(n-loop))=0;  //garray[i][n-loop]=0;

	for(i=m;i<b;i++)
		*(garray+i*n+(n-loop))=1;  //garray[i][n-loop]=0;
}


void print_gray(int *garray,int n,int m)
{
	int i,j;
	printf("\nin print fn\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",*(garray+i*n+j));  //garray[i][j]
		}
		printf("\n");
	}	
}












