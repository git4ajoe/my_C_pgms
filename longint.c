#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int value;
	struct node *next;
};



struct node * make_ll(char *s); 
void display_ll(struct node *ll);
struct node * addnos(struct node *ll1,struct node *ll2);
struct node * multiply_ll(struct node *ll1,struct node *ll2,int str1len,int str2len);


void main()
{
	int str1len,str2len;
	char s1[100],s2[100];
	struct node *ll1,*ll2,*longest,*added,*mulres;
	
	
	printf("Enter a large number..\n");
	scanf("%s",s1);

	ll1=make_ll(s1);
	
	printf("Enter a large number..\n");
	scanf("%s",s2);

	ll2=make_ll(s2);

	display_ll(ll1);
	display_ll(ll2);



//function call to add two long numbers
	
	added=addnos(ll1,ll2);
	printf("-----------------------sum of two lls\n");
	display_ll(added);

//function to multiply the two long numbers
	str1len=strlen(s1);
	str2len=strlen(s2);
	
	mulres=multiply_ll(ll1,ll2,str1len,str2len);
	printf("-----------------------product of lls\n");
	display_ll(mulres);
}

struct node * make_ll(char *s)
{
	int *ll;
	int len,i;
	struct node *front=NULL,*rear=NULL;
	
	len=strlen(s);
	
		
	for(i=len-1;i>=0;i--)
	{
		struct node *new=(struct node *)malloc(sizeof(struct node));
		new->value=s[i]-'0';
		new->next=NULL;
		
		if(!rear)
		{
			//printf("first node\n");
			rear=new;
			front=new;
		}
		else
		{
			rear->next=new;
			rear=new;
		}
		//printf("i value %d  %c\n",i,s[i]);
	}
	//printf("front %d\n",front->value);
	return front;	
}


void display_ll(struct node *ll)
{

	while(ll)
	{
		printf("%d  ",ll->value);
		ll=ll->next;
	}
	printf("\n");

}


struct node * addnos(struct node *ll1,struct node *ll2)
{

	struct node *front=NULL,*rear=NULL;
	int carry=0,sum,ll1value,ll2value;

	while(ll1 || ll2)
	{

		//printf("inside loop\n");
		struct node *new=(struct node *)malloc(sizeof(struct node));

		
		if(ll1) 
			ll1value=ll1->value;
		else
			ll1value=0;

		if(ll2)
			ll2value=ll2->value;
		else
			ll2value=0;


		sum=(ll1value+ll2value+carry)%10;
		
		new->value=sum;
		new->next=NULL;
		if(!rear)
			front=rear=new;		
		else
		{
			rear->next=new;
			rear=new;
		}
		carry=(ll1value+ll2value+carry)/10;
		
		if(ll1)
		ll1=ll1->next;
		if(ll2)
		ll2=ll2->next;

		//printf("inside loop sum%d carry %d\n",sum,carry);

	}
	
//if there is carry out of MSB, Then new node for that.
	if(carry >0)
	{
		struct node *new=(struct node *)malloc(sizeof(struct node));
		new->value=carry;
		rear->next=new;
		rear=new;
	}
	
	return front;	
}


struct node * multiply_ll(struct node *ll1, struct node *ll2,int str1len,int str2len)
{
	int i,prod,carry=0;
	struct node *list1,*final,*final1=NULL,*final2=NULL;

	
	//final1 and final2 shows the front and rear of result-ll. creating result ll here.

	for(i=0;i<str1len+str2len;i++)
	{
		struct node *new=(struct node *)malloc(sizeof(struct node));
		new->value=0;
		if(!final2)
			final1=final2=new;
		else
		{
			final2->next=new;
			final2=new;
		}
	}

	list1=ll1;
	final2=final1;
	final=final1;

	//display_ll(final1);


//normal multiplication procedure followed. multiplying one digit of one linked list with all digits of other linked list
//here each digit of second ll is multiplied with every digit of first ll.
//store partial product..
//next round skip one place and add the partial product and finally get the result.
//finding partial products until second ll gets exhausted.

//final1, final2 pointers to resultant list. final2->moving pointer . final1->keep the list

	while(ll2)
	{
		carry=0;
		
		final2=final1;
		ll1=list1;
		
		while(ll1)
		{
			prod=ll1->value * ll2->value + carry;
			
			//printf("multiplying %d and %d \n", ll1->value,ll2->value);
			//partial products need to be added.
			final2->value=final2->value + prod%10;


			//below two lines written so that when we addup partial sum it can become two digits,
			//that carry also generated and added with original carry and keeping it as single digit.
			
			carry=prod/10  + final2->value/10;
			final2->value=final2->value % 10;
			
			ll1=ll1->next;
			final2=final2->next;	
		}
			
		//carry from last mult.
		if (carry>0)
		{
			final2->value=final2->value + carry;
			final2=final2->next;
		}
		//after one partial product,next is writtten on 10th place only.. so skip one place
		
		final1=final1->next;
		ll2=ll2->next;
	}

	

	return final;
}


