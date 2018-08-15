/* 
   Name        : b2.c
   Creator     : Arun 
   Date        : 11/08/2018
   Description : Assignment three
		 creating a structurally identical bst from a given binary tree without using additional space. 	
*/


#include<stdio.h>
#include<stdlib.h>

#define N 15

struct node
{
	struct node *left;
	int value;
	struct node *right;	
};

struct node * construct_tree();
void enq(struct node* *queue,struct node *ptr,int *front,int *rear);
struct node* deq(struct node* *queue,int *front,int *rear);
void inorder(struct node *root);
void build_heap(struct node *root);
void heapify(struct node *root);
void heaptobst(struct node *rt,struct node *e);
void heapify_modified(struct node *root,int del_threshold);


void inorder(struct node *root)
{
	if(root)
	{
		inorder(root->left);
		printf("%d  ",root->value);
		inorder(root->right);
	}
}

void preorder(struct node *root)
{
	if(root)
	{
		printf("%d  ",root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void enq(struct node* *queue,struct node *ptr,int *front,int *rear)
{
	if(*front==-1 && *rear==-1)
	{
		queue[0]=ptr;
		*front=0;
		*rear=0;
		//printf("Enqueud  (%d,%d)\n",*front,*rear);
		return;
	}
	if((*rear+1)%N==*front)
	{
		printf("Queue is full\n");
	}
	else
	{
		*rear=(*rear+1)%N;
		queue[*rear]=ptr;
	}
	//printf("Enqueud  (%d,%d)\n",*front,*rear);
	return;
}

struct node* deq(struct node* *queue,int *front,int *rear)
{
	
	struct node *temp;	
	if(*front==-1)
	{
		printf("Queue is Empty\n");
		return NULL;
	}
	else
	{
	temp=queue[*front];
		
		if(*front==*rear)
		{
			*front=-1;
			*rear=-1;
		}
		else
			*front=(*front+1)%N;
	}
	//printf("dequeud  (%d,%d)\n",*front,*rear);
	return temp;
}

struct node * construct_tree()
{
	//queue for creating the arbitarary binary tree from user input.
	
	int a=-1,b=-1,count,ivalue,ileft,iright;
	int *front,*rear;
	struct node * queue[N];
	front=&a;
	rear=&b;
	
	
	//create root; and enque it in the empty queue.
	struct node *root,*temp;
	root=(struct node *)malloc(sizeof(struct node));
	enq(queue,root,front,rear);
	

	//while queue is not empty,pop the queue.
	//accept the value from user and push the 
	//pointers according to the data given by 
	//user.
	while(*front!=-1)
	{
		temp=deq(queue,front,rear);
		
		//accept userinput.
		scanf("%d%d%d",&ivalue,&ileft,&iright);
		temp->value=ivalue;
		
		if(ileft==1)
		{
			temp->left=(struct node *)malloc(sizeof(struct node));
			enq(queue,temp->left,front,rear);
		}
		else
			temp->left=NULL;
	
		if(iright==1)
		{
			temp->right=(struct node *)malloc(sizeof(struct node));
			enq(queue,temp->right,front,rear);
		}
		else
			temp->right=NULL;	
		
	}	

	return root;		
			
}

//build heap function
void build_heap(struct node *root)
{
	if(root==NULL)
		return;


	build_heap(root->left);
	build_heap(root->right);
	heapify(root);
}



void heapify(struct node *root)
{
	//normal heapify function.
	struct node *max;
	int temp;

	if(root->left==NULL && root->right==NULL)
		return;
	
	else
	{
		max=root;
		if(root->left!=NULL)
			if(root->value < root->left->value)
				max = root->left;
		if(root->right!=NULL)
			if(max->value < root->right->value)
				max = root->right;
		
		if(root!=max)
		{
			temp=root->value;
			root->value=max->value;
			max->value=temp;
			heapify(max);	
		}
		
	}	

}


//convert the heap to Binary search Tree.
//we have two arguments, root and currently exloring node(e-node).

void heaptobst(struct node *rt,struct node *e)
{
	//following the reverse order. 
	
	int temp,del_threshold=0;	
	if(e==NULL)	return;
		
	heaptobst(rt,e->right);
	
	if(e==rt)
	{
		del_threshold=	rt->value;		
		if(e->left==NULL)
		{
			return;
		}
		else
		{
			//printf("Error place 2\n");
			rt=e->left;				
		}
				
	}
	else
	{
		temp=e->value;
		e->value=rt->value;
		rt->value=temp;

		del_threshold=e->value;
		//recursively heapify downwards the tree.
		heapify_modified(rt,del_threshold);
	}

	heaptobst(rt,e->left);					
}


void heapify_modified(struct node *root,int del_threshold)
{

	struct node *max,*rst_trverse;
	int temp;
	//if leaf node no need to heapify further.
	if(root->left==NULL && root->right==NULL)
		return;
	
	else
	{
		max=root;
		if(root->left!=NULL)
			if(root->value < root->left->value)
			{
				max = root->left;
			}
		if(root->right!=NULL)
		{
			if(root->right->value >= del_threshold)
			{
			//right node is deleted already;the check lst of right node for undeleted nodes;
			//checking by going left deeper until we find undeleted node. 
			//if not found all nodes in rst is deleted.
				rst_trverse = root->right;
				while(rst_trverse->left!=NULL)
				{	
					rst_trverse=rst_trverse->left;
					if(rst_trverse->value < del_threshold)
						break;
				}
				
				
			}
			else
				rst_trverse=root->right;
			
			if(max->value < rst_trverse->value && rst_trverse->value < del_threshold)
				max=rst_trverse;
		}
			
		if(root!=max)
		{
			temp=root->value;
			root->value=max->value;
			max->value=temp;
			heapify_modified(max,del_threshold);	
		}

	}	
	
}


void main()
{
	struct node *root;

	root=construct_tree();

	printf("Initial binary tree     \n");
	printf("preorder           :");
	preorder(root);
	printf("\n");
	
	printf("inorder            :");
	inorder(root);
	printf("\n");

	build_heap(root);

	printf("After conversion to heap     \n");
	printf("preorder           :");
	preorder(root);
	printf("\n");
	
	printf("inorder            :");
	inorder(root);
	printf("\n");	
	
	heaptobst(root,root);
	
	printf("After conversion to BST   \n");
	printf("preorder           :");
	preorder(root);
	printf("\n");
	
	printf("inorder            :");
	inorder(root);
	printf("\n");	
	
}

