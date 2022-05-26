#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node 
{
	int value;
	struct node *left;
	struct node *right;
};
int check_number;
struct node *create_node(struct node *left,int value,struct node *right);
struct node *read_tree(void);
int read_number(void);
char buff[100000];
char *nextch;
int search_bt(struct node *nodep, int key);
void dfs_print1(struct node *p);
void dfs_print3(struct node *p);
void print_node(struct node *f);
void check_node(struct node *f);
void check_bt(struct node *p);
void insert_bt(struct node *nodep,struct node **ptr,int key);
void print_tree(struct node *p);

/*
���̃v���O�����́A����񕪖؂�^���A�����A���̓񕪖؂̐����̏��Ԃ̍\�����Ԉ���Ă�����A"incorrect order"�ƕ\������B
�����A�L���̍\�����Ԉ���Ă�����A"ERROR:�Ԉ�������̂����͂���Ă��܂��B"�ƕ\������B���̂Ƃ��A�ǂ��ɊԈႢ�����邩���m�F���邽�߁A�Ԉ���Ă��镔���̋L�����\������B
��������Ƃ����񕪖؂��^����ꂽ��Amain�����Ƃ��ė^����������}�������A�V�����񕪖؂�\������B

�e�X�g���@
"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂�^��"8"�������ɗ^�����Ƃ��A"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�ƕ\�����ꂽ���Ƃ�ڎ��m�F�����B
"<-,20,->"�Ɠ��͂�^���A"2"�������ɗ^�����Ƃ��A"<<-,2,->,20,->"�ƕ\�����ꂽ���Ƃ�ڎ��m�F�����B
"<-,20,-"�A"ERROR:�Ԉ�������̂����͂���Ă��܂��B(>)"�ƕ\�����ꂽ���Ƃ�ڎ��m�F�����B
"<<-,30,->,20,->"�Ɠ��͂�^�����Ƃ��A"incorrect order"�ƕ\�����ꂽ�B
*/

int main()
{
	struct node *n1,*n2,*n3,*n4	,*b;

	scanf("%99s",buff);
	nextch=buff;
	
	b=read_tree();

	check_bt(b);

	insert_bt(b,&b,8);

	print_tree(b);
	
	return 0;
}

//create_node�́A�����̖؂̍\���̂̃|�C���^�ƁA�ߓ_�̐����ƁA�E���̖؂̍\���̂̃|�C���^�������Ɏ��A�V���ɍ�����\����node�ւ̃|�C���^��Ԃ����߂̊֐��B

struct node *create_node(struct node *left,int value,struct node *right)
{
	struct node *aa;

	aa=(struct node*)malloc(sizeof(struct node));

	aa->left=left;
	aa->value=value;
	aa->right=right;

	return aa;
}

/*
search_bt�́A����\���̂̃|�C���^�ƁA���鐮�����󂯎��A�񕪒T���؂ɁA���̐��������邩��T�����߂̊֐��B�������ꍇ�͂��̕����܂ł�\�����A�Ȃ������ꍇ�A�܂��A�[�̕�����T�����ꍇ�́A�Ō�܂ŕ\������B

�e�X�g���@
�����Ɏ�鐮����30�ɂ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂����Ƃ��A20,30�̏����ŕ\�����ꂽ�B
����́A�񕪒T���؂��A20����X�^�[�g���A���ɁA20���傫�������Ȃ̂ŁA�E�ɐi�߁A30��\������B����ŁA30�����������̂ŁA�\�����I������B
�����Ɏ�鐮����1�ɂ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂����Ƃ��A20,10,5�̏��Ԃŕ\�����ꂽ�B
����́A�񕪒T���؂��A20����X�^�[�g���A���ɁA20��菬���������Ȃ̂ŁA���ɐi�߁A10��\������B���ɁA10��菬���������Ȃ̂ŁA���ɐi�߁A5��\������B5�ōŌ�Ȃ̂ŕ\�����I������B
�����Ɏ�鐮����36�ɂ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂����Ƃ��A20,30,35�̏��Ԃŕ\�����ꂽ�B
����́A�񕪒T���؂��A20����X�^�[�g���A���ɁA20���傫�������Ȃ̂ŁA�E�ɐi�߁A300��\������B���ɁA30���傫�Ȑ����Ȃ̂ŁA�E�ɐi�߁A35��\������B35�ōŌ�Ȃ̂ŕ\�����I������B
*/

int search_bt(struct node *nodep, int key)
{
	if (nodep==0)		return 0;
	printf("%d\n",nodep->value);

	if (key==nodep->value) return 1;
	else if (key < nodep->value) 
	{
		return search_bt(nodep->left,key);
	} 
	else 
	{
		return search_bt(nodep->right,key);
	}
}

/*
read_tree�́Anextch�̎w���Ă��镶���񂩂�؂̗v�f��1���ǂݍ��݁A���̂˂ɂȂ�\����node�ւ̃|�C���^��Ԃ����߂̊֐��B

�e�X�g���@
"<-,10,-"�Ɠ��͂����Ƃ��A"ERROR:�Ԉ�������̂����͂���Ă��܂��B(>)"�ƕ\�����ꂽ�̂ŁA">"�̕����ŃG���[���N���������Ƃ������Ă���B
�܂��A�G���[�̃e�L�X�g���A��ڂ�'>'�̂Ƃ��낾��"ERROR:�e�X�g�p2"�ƕς���"<-,10-��"�Ɠ��͂����Ƃ��A"ERROR:�e�X�g�p2"�ƕ\�����ꂽ�̂ŁA��ڂ�","�̕����ŃG���[���N���������Ƃ������Ă���B
"-"�Ɠ��͂����Ƃ��A�G���[���b�Z�[�W���\������Ȃ������̂Ő������B
*/

struct node *read_tree(void)
{
	if(*nextch=='-')
	{
		nextch++;
		return 0;
	}
	
	if(*nextch!='<')
	{
		printf("ERROR:�Ԉ�������̂����͂���Ă��܂��B(<)\n");
	 	return 0;
	}
	else nextch++;;	

	struct node *p1;
	p1=read_tree();

	if(*nextch!=',')
	{
		printf("ERROR:�Ԉ�������̂����͂���Ă��܂��B(,)\n")	;
		return 0;
	}
	else nextch++;

	int p2;
	p2=read_number();

	if(*nextch!=',')
	{
		printf("ERROR:�Ԉ�������̂����͂���Ă��܂��B(,)\n")	;
		return 0;
	}
	else nextch++;

	struct node *p3;
	p3=read_tree();

	if(*nextch!='>')
	{
		printf("ERROR:�Ԉ�������̂����͂���Ă��܂��B(>)\n")	;
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

void check_bt(struct node *p)
{
	if(p==0) return;

	else
	{
		check_bt(p->left);
		check_node(p);
		check_bt(p->right);
	}
}
/*
check_node�́A�ċA�֐����g�����A�[���D��T�����A�ʂ肪�����ɕ���ł��邩���m�F���邽�߂̊֐��B�m�F�̎d���Ƃ��ẮA��O��check_node�ŕ\�������l��荡�̒l�̕����傫�����𒲂ׂ�B�����A��O��check_node�ŕ\�������l��荡�̒l�̕��������������Ƃ��A"incorrect order"�Ƃ����G���[���b�Z�[�W��\������B

�e�X�g���@
<<-,15,->,20,<-,7,->>�Ɠ��͂�^�����Ƃ��A"incorrect order"�ƕ\�����ꂽ���Ƃ�ڎ��m�F�����B
<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>�Ɠ��͂�^�����Ƃ��A�G���[���o�Ȃ��������Ƃ�ڎ��m�F�����B
<<<-,5,->,10,<-,40,->>,20,<-,30,<-,35,->>>�Ɠ��͂�^�����Ƃ��A"incorrect order"�ƕ\�����ꂽ���Ƃ�ڎ��m�F�����B
*/

void check_node(struct node *f)
{
	if(f->value < check_number) printf("incorrect order\n");

	check_number = f->value;
}

/*
print_tree�́A����\���̂̃|�C���^�������Ɏ��A���̓񕪖؂�\�����邽�߂̊֐��B

�e�X�g���@
�����Ƃ���3�����̍\����
n1=create_node(0,10,0);
n2=create_node(0,30,0);
n3=create_node(n1,20,n2);
���󂯎�����Ƃ��A"<<-,10,->,20,<-,30,->>"�ƕ\�����ꂽ�B����́A�񕪖؂Ƃ��Đ������Ƃ�����B

�܂��A�����Ƃ���4�����̍\����
	n1=create_node(0,25,0);
	n2=create_node(0,10,0);
	n3=create_node(n1,30,0);
	n4=create_node(n2,20,n3);
���󂯎�����Ƃ��A"<<-,10,->,20,<<-,25,->,30,->>"�ƕ\�����ꂽ�B����́A�񕪖؂Ƃ��Đ������Ƃ�����B
*/

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

/*
insert_bt�́A�\���̂̃|�C���^�ƁA�\���̂̃|�C���^���w���|�C���^�ƁA���鐮���������Ɏ��A���̐�����񕪒T���؂ɑ}�����邽�߂̍ċA�֐��B

�e�X�g���@
�����Ƃ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂��A"36"��^�����Ƃ��A"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,<-,36,->>>>"�Əo�͂��ꂽ���Ƃ�ڎ��m�F�����B
�����Ƃ��āA"<<<-,5,->,10,<-,15,->>,20,>>"�Ɠ��͂��A"36"��^�����Ƃ��A"<<<-,5,->,10,<-,15,->>,20,<-,36,->>"�Əo�͂��ꂽ���Ƃ�ڎ��m�F�����B
�����Ƃ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂��A"0"��^�����Ƃ��A"<<<<-,0,->,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Əo�͂��ꂽ���Ƃ�ڎ��m�F�����B
�����Ƃ��āA"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"�Ɠ��͂��A"7"��^�����Ƃ��A"<<<-,5,<-,7,->>,10,<-,15,->>,20,<-,30,<-,35,->>>"�Əo�͂��ꂽ���Ƃ�ڎ��m�F�����B
�����Ƃ��āA"-"�Ɠ��͂��A"36"��^�����Ƃ��A"<-,36,->"�Əo�͂��ꂽ���Ƃ�ڎ��m�F�����B
*/

void insert_bt(struct node *nodep,struct node **ptr,int key)
{
	if(nodep==0)
	{
		 *ptr=create_node(0,key,0);
	}

	else if(nodep->value==key) return;

	else if (key < nodep->value) 
	{
		ptr=&nodep->left;
		insert_bt(nodep->left,ptr,key);
	} 
	else 
	{
		ptr=&nodep->right;
		insert_bt(nodep->right,ptr,key);
	}

	return;
}





