/*
	Name 	: b3.c
	Creator : Arun(18CS60R73).
	Date    : 15-08-2018
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ll 0
#define lr 1
#define rl 2
#define rr 3

struct node
{
	struct node *left;
	int value;
	struct node *right;	
};

struct node * createnode(int value);
struct node* insert_bst(struct node *root,int value);
void inorder(struct node *root);
void preorder(struct node *root);
int find_nooflevels(struct node *root);
int nodecount(struct node *root);
int level(struct node *root,struct node *current);
int sumlevel(struct node *root,struct node *current);
void count2chains(struct node *root,int *chains);
void llrotation(struct node *root,struct node *u,struct node *v);
void lrrotation(struct node *root,struct node *u,struct node *v);
void rrrotation(struct node *root,struct node *u,struct node *v);
void rlrotation(struct node *root,struct node *u,struct node *v);
void swap(struct node *node1,struct node *node2);

/*
	function to create a tree node and return.
*/
struct node * createnode(int value)
{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	new->value=value;
	new->left=NULL;
	new->right=NULL;

	return new;
}

/*
	function to insert nodes to a BST.
*/
struct node* insert_bst(struct node *root,int value)
{
	if(!root)
	{
		return createnode(value);

	}

	if(value < root->value)
	{
		root->left = insert_bst(root->left,value);	
	}
	else if(value > root->value)
	{
		root->right = insert_bst(root->right,value);
	}
	
	return root;
}

/*
	inorder traversal
*/
void inorder(struct node *root)
{
	if(root)
	{
		inorder(root->left);
		printf("%d  ",root->value);
		inorder(root->right);
	}
}

/*
	preorder traversal
*/

void preorder(struct node *root)
{
	if(root)
	{
		printf("%d  ",root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

/*
	function that finds the number of levels in the tree recursively.
*/

int find_nooflevels(struct node *root)
{
	int l,r;
	if(!root)
		return 0;
	
	l=find_nooflevels(root->left);
	r=find_nooflevels(root->right);
	
	if(l>=r)
		return l+1;
	else
		return r+1;	
}

/*
	return node count.
*/
int nodecount(struct node *root)
{
	if(!root)
		return 0;
	return 1+nodecount(root->left)+nodecount(root->right);	
}

/*
	input argument two node pointers.
	returns the distance between two nodes.
	when root given as one argument finds the level(root at 0)
*/
int level(struct node *root,struct node *current)
{
	int l=0;
	
	if(!current)
		return 0;

	if(root->value==current->value)
	{
		return 0;
	}
	if(root->value > current->value)
	{
		l = 1+level(root->left,current);
	}
	else
	{
		l = 1+level(root->right,current);
	}

	return l;
}

/*
	finds sum of levels of all nodes.
*/
int sumlevel(struct node *root,struct node *current)
{
	int sl1=0,sl2=0;

	if(!root)
		return 0;
	if(!current)
		return 0;

	//printf("sumlevel calls(%d,%d)\n",root->value,current->value);
			
	return level(root,current) + sumlevel(root,current->left) + sumlevel(root,current->right);		
}

/*
	finds number of 2-chains and update the count in the input array.
*/
void count2chains(struct node *root,int *chain)
{
	struct node *ptrl,*ptrr;
	
	if(!root)
		return;
	
	if(root->left && !root->right)
	{
		ptrl=root->left;
		if(ptrl->left && !ptrl->right)
		{
			chain[ll]=chain[ll]+1;
		}
		if(ptrl->right && !ptrl->left)
		{
			chain[lr]=chain[lr]+1;
		}
	}
	
	if(root->right && !root->left)
	{
		ptrr=root->right;
		if(ptrr->left && !ptrr->right)
		{
			chain[rl]=chain[rl]+1;
		}
		if(ptrr->right && !ptrr->left)
		{
			chain[rr]=chain[rr]+1;
		}
	}
	count2chains(root->left,chain);
	count2chains(root->right,chain);			
}

/*
	remove 2-chains by recursively calling rotation functions.
*/
void rm2chains(struct node *root)
{
	struct node *ptrl,*ptrr;

	if(!root)
		return;
	
	if(root->left && !root->right)
	{
		ptrl=root->left;
		if(ptrl->left && !ptrl->right)
		{
			llrotation(root,ptrl,ptrl->left);
		}
		if(ptrl->right && !ptrl->left)
		{
			lrrotation(root,ptrl,ptrl->right);
		}
	}
	
	if(root->right && !root->left)
	{
		ptrr=root->right;
		if(ptrr->left && !ptrr->right)
		{
			rlrotation(root,ptrr,ptrr->left);
		}
		if(ptrr->right && !ptrr->left)
		{
			rrrotation(root,ptrr,ptrr->right);
		}
	}
	rm2chains(root->left);
	rm2chains(root->right);
}

void llrotation(struct node *root,struct node *u,struct node *v)
{
	swap(root,u);
	root->left=u->left;
	root->right=u;
	u->left=NULL;
}

void lrrotation(struct node *root,struct node *u,struct node *v)
{
	swap(root,v);
	root->right=v;
	u->right=v->left;
	v->left=v->right;
	v->right=NULL;	
}

void rrrotation(struct node *root,struct node *u,struct node *v)
{
	swap(root,u);
	root->right=u->right;
	root->left=u;
	u->right=NULL;
}

void rlrotation(struct node *root,struct node *u,struct node *v)
{
	swap(root,v);
	root->left=v;
	u->left=v->right;
	v->right=v->left;
	v->left=NULL;
}

void swap(struct node *node1,struct node *node2)
{
	int temp;
	temp=node1->value;
	node1->value=node2->value;
	node2->value=temp;
}


void main()
{

	int n,i,value;
	int chains[4]={0};
	struct node *root=NULL;
	
	
	printf("Enter no of nins       :\t");
	scanf("%d",&n);
	
	printf("Enter keys             :\t");
	for(i=0;i<n;i++)
	{
		scanf("%d",&value);
		root=insert_bst(root,value);
		
	}
	printf("\n");
	
	printf("Initial tree\n");
	printf("Preorder               :\t");
	preorder(root);
	printf("\n");
	printf("Inorder                :\t");
	inorder(root);
	printf("\n");

	printf("Height of the tree  =  %d\n", find_nooflevels(root)-1);
	printf("Average level       =  %f\n", sumlevel(root,root) / ( nodecount(root) * 1.0 ));
	printf("Number of nodes     =  %d\n", nodecount(root));
	printf("\n");
	
	count2chains(root,chains);
	printf("counts of 2 chains\n");
	printf("LL:  %d, ",chains[ll]);
	printf("LR:  %d, ",chains[lr]);
	printf("RL:  %d, ",chains[rl]);
	printf("RR:  %d, ",chains[rr]);
	printf("Total:  %d\n",chains[ll]+chains[lr]+chains[rl]+chains[rr]);	
	printf("\n");

	printf("Removing 2-chains\n");
	printf("\n");
	rm2chains(root);

	printf("New tree\n");
	printf("Preorder               :\t");
	preorder(root);
	printf("\n");
	printf("Inorder                :\t");
	inorder(root);
	printf("\n");

	printf("Height of the tree  =  %d\n", find_nooflevels(root)-1);
	printf("Average level       =  %f\n", sumlevel(root,root) / ( nodecount(root) * 1.0 ));				
	printf("\n");

	chains[ll]=0; 
	chains[lr]=0; 
	chains[rr]=0; 
	chains[rl]=0;

	count2chains(root,chains);
	printf("counts of 2 chains\n");
	printf("LL:  %d, ",chains[ll]);
	printf("LR:  %d, ",chains[lr]);
	printf("RL:  %d, ",chains[rl]);
	printf("RR:  %d, ",chains[rr]);
	printf("Total:  %d\n",chains[ll]+chains[lr]+chains[rl]+chains[rr]);	
		
}
