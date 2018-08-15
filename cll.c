#include<stdio.h>
#include<stdlib.h>


void insert_cll(int temp);
void display_cll();
void modify_cll(int k);

struct node
{
	int value;
	struct node *next;
};


struct node *front,*rear=NULL;


void main()
{
	int n,i,temp,k;
	printf("Enter number of elements in the list\n");
	scanf("%d",&n);
	

	for(i=0;i<n;i++)
	{
		scanf("%d",&temp);
		insert_cll(temp);
	}

	printf("Enter value of k\n");
	scanf("%d",&k);

	printf("The cll is\n");
	display_cll();
	printf("\nThe k value is ---%d\n",k);

	printf("-----------------------------------\n");
	printf("modified linked list is\n");

	modify_cll(k);
	display_cll();

}

void insert_cll(int temp)
{
	struct node *new=(struct node*)malloc(sizeof(struct node));
	new->value=temp;
	new->next=NULL;

	if(!rear)
		front=rear=new;
	else
	{
		rear->next=new;
		rear=new;
	}
	new->next=front;	
}

void display_cll()
{
	struct node *temp=front;
		
	if(!front)
		printf("no nodes");
	else
	{
		while(temp!=rear)
		{
			printf("%d ,",temp->value);
			temp=temp->next;
		}
		printf("%d ,",temp->value);
		printf("\n");
	}
}


void modify_cll(int k)
{
	struct node *temp,*current;
	int count=0,max=0,flag=0,i=0;


	//save first k elements in the array for future reference as they will be replaced.

	int *firstk=(int *)malloc(k*sizeof(int));
	temp=front;

	while(count!=k)
	{
		firstk[count]=temp->value;
		count++;
		temp=temp->next;
	}
	

	count=0;
	current=front;

	
	do
	{
		temp=current;
		//printf("currentpointer at %d\n",current->value);
		//temp pointer checking the next k elements to find max. 
		while(count!=k)
		{
			temp=temp->next;
			count++;
			//printf("TEMPpointer at %d\n",temp->value);

			if(temp==front)
			{
				flag=1;
				//printf("crossed\n");
			}

			//if crossed, compare with the old values, not the replaced values.
			if(flag==1)
			{
				
				if(firstk[i] > max)
					max=firstk[i];
				i++;	
			}
			//normal case.
			else
			{
				
				if(temp->value > max)
					max=temp->value;
			}

		}
		
		current->value=max;
		current=current->next;
		count=0;
		max=0;
		i=0;
		flag=0;	
		//display_cll();	
	}while(current!=front);
}






