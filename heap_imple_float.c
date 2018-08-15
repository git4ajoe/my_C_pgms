/* 
   Name        : Fractions.c
   Creator     : Arun 
   Date        : 06/08/2018
   heap implementation example
*/

#include<stdio.h>
#include<stdlib.h>

struct triple 
{
	int a;
	int b;
	double f;
};

void build_heap(struct triple *heap,int n);
void swap(struct triple *heap,int v1,int v2);
void minheapify(struct triple *heap,int parent,int n);
int delete_min(struct triple *heap,int n);
int insert_element(struct triple *heap,int n,struct triple new);
int gcd(int a, int b);
void initialize_array(struct triple *heap,int n);
void printfractions(struct triple *heap,int n);


void main()
{
	int n;
	printf("Enter the N value\n");
	scanf("%d",&n);

	struct triple *heap =(struct triple *)malloc((n+1)*sizeof(struct triple));
	
	initialize_array(heap,n);
	build_heap(heap,n);
	
	printfractions(heap,n);			
}


void swap(struct triple *heap,int v1,int v2)
{	
	//routine for swapping elements with in the heap.
	//input : the index values.
	
	
	struct triple temp;
	temp = heap[v1];
	heap[v1]=heap[v2];
	heap[v2]=temp;
}


void build_heap(struct triple *heap,int n)
{
	//at leaf level they are already heap. start from the right bottom parent, then go up recursively.
	
	int i;	
	for(i=n/2;i>=1;i--)
	{
		minheapify(heap,i,n);
	}	

}

void minheapify(struct triple *heap,int parent,int n)
{
	
	int lchild,rchild,min;

	//following the index 1 way.
	lchild=2*parent;
	rchild=2*parent + 1;

	if(lchild > n)
		return;
	else
	{
		min=parent;
	
		if(heap[lchild].f < heap[min].f)
			min=lchild;

		if(rchild <= n && heap[rchild].f < heap[min].f)
			min=rchild;
		
		if(min!=parent)
		{
			swap(heap,parent,min);
			//doing recursively down the tree.	
			minheapify(heap,min,n);		
		}
	}
}



//returning length to keep it updated in the calling function.
//this function deletes the minimum element(root) and reorder the heap.
int delete_min(struct triple *heap,int n)
{
	swap(heap,1,n);
	n--;
	minheapify(heap,1,n);
	return n;
}


//inserting a new element to an existing heap.
int insert_element(struct triple *heap,int n,struct triple new)
{
	int temp;
	n++;
	heap[n]=new;
	temp=n;
			
	//if child is lesser than parent then swap. do this till root.
	while(temp>1 && heap[temp].f < heap[temp/2].f)
	{
		swap(heap,temp,temp/2);
		temp=temp/2;
	}
	return n;
}

//function to check if the gcd is 1. if gcd==1 return 1 else 0.
int gcd(int a, int b)
{
	int i;
	for(i=2; i<=a && i<=b; i++)
	{
		if(a%i ==0 && b%i==0)
			return 0;
	}
	return 1;
}


//this function puts the basic fractions with a=0 and a=1 in the array to initialize it. 

void initialize_array(struct triple *heap,int n)
{
	int i;
	
	heap[1].a=0;
	heap[1].b=1;
	heap[1].f=0;

	for(i=2;i<=n;i++)
	{
		heap[i].a=1;
		heap[i].b=i;
		heap[i].f=(1*1.0)/(i*1.0);
		//printf("valuee %d  =%f\n",i,heap[i].f);
	}
	
}

/*
printfractions function finds the suitable a/b values; once it gets a possible a/b value
considering the gcd(a,b) and a<b condition, this function delete the root of heap, prints
it and then insert the new a/b value. 
once all a/b values get exhuasted delete the rest of the elements from the heap.
*/
void printfractions(struct triple *heap,int n)
{
	int a,b,counter=1;
	struct triple new;
	
	for(a=2;a<n;a++)
	{
		for(b=n;b>=2;b--)
		{
			if(a<b && gcd(a,b))
			{
				printf("Fraction no   %2d  :   %2d / %2d  =  %.15lf \n",counter,heap[1].a,heap[1].b,heap[1].f);
				counter++;
				n=delete_min(heap,n);

				new.a=a;
				new.b=b;
				new.f=(a*1.0)/(b*1.0);
				n=insert_element(heap,n,new);
			}
			else ;
		}
	}

	//print the remaining value in the queue.
	while(n!=0)
	{
		printf("Fraction no   %2d  :   %2d / %2d  =  %.15lf \n",counter,heap[1].a,heap[1].b,heap[1].f);
		counter++;
		n=delete_min(heap,n);		
	}
	
}


