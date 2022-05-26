#include<stdio.h>
#include <string.h>
#include <stdlib.h>

struct node 
{
	int value;
	struct node *left;
	struct node *right;
};

struct node *create_node(struct node *left,int value,struct node *right);
void print_tree(struct node *p);
struct node *read_tree(void);
int read_number(void);
char buff[100000];
char *nextch;





int main()
{	struct node *n1,*n2,*n3,*n4 ;

	scanf("%99s",buff);
	nextch=buff;
	
	struct node *b;
	b=read_tree();

	print_tree(b);

	return 0;
}



struct node *create_node(struct node *left,int value,struct node *right)
{
	struct node *aa;

	aa=(struct node*)malloc(sizeof(struct node));

	aa->left=left;
	aa->value=value;
	aa->right=right;

	return aa;
}



void print_tree(struct node *p)
{

	if(p==0)		printf("-");

	else
	{
		printf("<");
		print_tree(p->left);
		printf(",");
		printf("%d",p->value);
		printf(",");
		print_tree(p->right);
		printf(">");
	}

}

struct node *read_tree(void)
{
	if(*nextch=='-')
	{
		nextch++;
		return 0;
	}
	
	if(*nextch!='<')
	{
		printf("ERROR:間違ったものが入力されています。");
	 	return 0;
	}
	else nextch++;;	

	struct node *p1;
	p1=read_tree();

	if(*nextch!=',')
	{
		printf("ERROR:間違ったものが入力されています。")	;
		return 0;
	}
	else nextch++;

	int p2;
	p2=read_number();

	if(*nextch!=',')
	{
		printf("ERROR:間違ったものが入力されています。")	;
		return 0;
	}
	else nextch++;

	struct node *p3;
	p3=read_tree();

	if(*nextch!='>')
	{
		printf("ERROR:間違ったものが入力されています。")	;
		return 0;
	}
	else nextch++;

	return create_node(p1,p2,p3);
}




int read_number(void)
{
	int sum=0;

	while (('0' <= *nextch) && (*nextch <= '9'))
	{
		sum = sum*10 + (*nextch-'0');
		nextch++;
	}

	return sum;
}










