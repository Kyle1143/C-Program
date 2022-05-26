
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_HASH 256 //MAX_HASH��256�ƒ�`
#define STACK 100


struct item //�\����item�͕����̃|�C���^�Əo���񐔂𐔂���count�ƍ\����item���w���|�C���^next�������o�[�Ɏ���
{
	int count;
	char *word;
	struct item *next;
};

struct item *hashtable[MAX_HASH];
int sp;
char stack[STACK];
int count;

 //�֐��̃v���g�^�C�v�錾(�̂̉��K�ō�����֐�)
int hash(char *string);
struct item *create_item(char *key,struct item *p);
char *create_string(char *buff1);
struct item *search_item(char *key, struct item *p);
void chainhash(char *key1);
struct item *delete_item(char *key, struct item *p);
char pop();
int push(char c);

//���������V�����֐�
int repeat(struct item* q);
char * reverse(char *word);
void reverse_cmp(struct item*q,int a);
/*
���̃v���O�����́A���炩�̃e�L�X�g�t�@�C����ǂݍ��݁A���̒�����A�n�b�V���l�̓��������𐮗����A��������u�|��v��T���o���A�����\�����A�܂��A�u�|��v�̐��������A�\�����邽�߂̂��́B
���ubob�v�Ȃǂ̉񕶂��u�|��v�̒�`�ɓ��Ă͂܂�̂ŁA�u�|��v�Ƃ��ăJ�E���g���邱�Ƃɂ���B
�e�X�g���@

�܂��A���̃v���O�����Ɠ����t�H���_���ɁAtest.text1�Ƃ����A�Ή�����|���3�Z�b�g�p�ӂ����e�L�X�g�t�@�C�����쐬����B
���̒��g�͈ȉ��ł���B
	deeps speed loop pool pans snap
���̃t�@�C����ǂݍ��ݎ��s����ƁA
palindorome deeps
palindorome speed
palindorome pans
palindorome snap
palindorome loop
palindorome pool
�|���6����������܂���.
�ƕ\�����ꂽ�B����́A���������s�ł��Ă���Ƃ�����B
�܂��A���̃v���O�����Ɠ����t�H���_���ɁAtest.text2�Ƃ����A�Ή�����|��2�Z�b�g�ƁA�֌W�̂Ȃ�������3�p�ӂ����e�L�X�g�t�@�C�����쐬����B
���̒��g�͈ȉ��ł���B
	no on revel lever dog cat key
���̃t�@�C����ǂݍ��ݎ��s����ƁA
palindorome revel
palindorome lever
palindorome no
palindorome on
�|���4����������܂����B
�ƕ\�����ꂽ�B����́A���������s�ł��Ă���Ƃ�����B
�܂��A���̃v���O�����Ɠ����t�H���_���ɁAtest.text3�Ƃ����A�񕶂̕���2�ƁA�֌W�̂Ȃ�������3�p�ӂ����e�L�X�g�t�@�C�����쐬����B
���̒��g�͈ȉ��ł���B
	 bob madam test that this
���̃t�@�C����ǂݍ��ݎ��s����ƁA
palindorome madam
palindorome bob
�|���2����������܂����B
�ƕ\�����ꂽ�B����́A���������s�ł��Ă���Ƃ�����B
�܂��A���̃v���O�����Ɠ����t�H���_���ɁAtest.text4�Ƃ����A�X�y�[�X�݂̂�p�ӂ����e�L�X�g�t�@�C�����쐬����B
���̃t�@�C����ǂݍ��ݎ��s����ƁA
�|���0����������܂����B
�ƕ\�����ꂽ�B����́A���������s�ł��Ă���Ƃ�����B
�܂��A���݂��Ȃ��Aerror.txt�Ƃ����t�@�C����ǂݍ��܂���ƁA
can not open 
�ƕ\�����ꂽ�B����́A���������s�ł��Ă���Ƃ�����B
*/
int main()
{
	int i,*p,k,kh,hantei;
	char buff[100],*test; //buff�͓ǂݍ��񂾕�����,del�͍폜������������
	struct item *test1,*test2,*test3; //�e�X�g�p
	char *testn;
	FILE * istream; //�X�g���[�����J��
	istream = fopen("dict.txt","r"); //tom.txt���J��
	if(istream == 0) //�t�@�C�����J���Ȃ�������
	{
		printf("can not open\n"); //���b�Z�[�W��\�����ďI��
		return 1;
	}
	for(i=0;i<50000;i++) //��������
	{
		if(fscanf(istream, "%s", buff)==EOF) break; //�����񂪂Ȃ��Ƃ��͔�����
		chainhash(buff); //hash�\�ɕ������o�^
	}
	fclose(istream); //�t�@�C�������
	printf("\n");
	for(i=0;i<MAX_HASH;i++)
	{
		hantei=repeat(hashtable[i]);
		if(hantei!=0)
		{
			/*print_list(hashtable[i]);
			printf("%d\n",hantei);*/
			reverse_cmp(hashtable[i],hantei);
		}
	}
	printf("�|���%d����������܂���.\n",count);
	return 0;
}


//create_string�́A���镶����������Ɏ��Astrlen�Œ����𑪂����V���ȃ�������p�ӂ��A�����ɕ�������R�s�[���邽�߂̊֐��B
char *create_string(char *buff1)
{
	char *p;
	p = (char *)malloc(sizeof(buff1)); 
	strcpy(p,buff1); 
	return p;
}


//create_item�́A������key�̃|�C���^�ƍ\����p�̃|�C���^�������Ɏ��Ap�̃��X�g�����ɐL�΂����߂̊֐��B
struct item *create_item(char *key,struct item *p)
{
	struct item *list;
	list = (struct item *)malloc(sizeof(struct item));
	list -> count = 1;
	list -> word = create_string(key);
	list -> next = p;
	return list;
}


//search_item�́A���镶����ƍ\���̂������Ɏ��A���̍\���̂̃��X�g�̒��ɓ����Ă��邩�𒲂ׁA�����Ă����炻�̍\���̂�Ԃ��A�����Ă��Ȃ�������0��Ԃ����߂̊֐��B
struct item *search_item(char *key, struct item *p)
{
	while(p != 0)
	{
		if(strcmp(p->word,key)==0) return p;
		p = p ->next;
	}
	return 0; 
}

//chainhash�́A������������Ɏ��A�܂��A�L�[�̃n�b�V���l���v�Z����B���̌�A�n�b�V���l�ɑΉ����郊�X�g�𐧍삵�A���̒��ɃL�[����������J�E���g���𑝂₵�A�Ȃ���΂��̃��X�g�ɐV���ȍ��ڂ�ǉ����邽��///�̊֐��B
void chainhash(char *key1)
{
	int h;
	struct item*list,*p;
	h = hash(key1);
	list = hashtable[h]; 
	p = search_item(key1, list);

	if (p != 0) p -> count++; 
	else hashtable[h] = create_item(key1,list);
}


//hash�́A��������󂯎��A�����Őݒ肵���i�����256�j�l�őS�����R�[�h���������]��̒l��Ԃ����߂̊֐��B
int hash(char *string)
{
	int i,sum=0,a = strlen(string);
	char c;
	for(i=0;i<a;i++)
	{
		c = string[i];
		sum = sum + c;
	}
	return sum % MAX_HASH;
}


/*
repeat�́A����\���̂̃|�C���^�������Ɏ��A���́A���ɐL�тĂ��郊�X�g�̐��𐔂��邽�߂̊֐��B
���̃v���O�����Ɠ����t�H���_���ɁAtest.repeat1.txt�Ƃ����A�����n�b�V���l������2��̃e�L�X�g�t�@�C�����쐬����B
���̒��g�͈ȉ��ł���B
	this hist
���̕���������n�b�V���l�͗���184�ł���B184���i�[����hashtable�̃��X�g�̒������A�Ԃ�l�Ƃ���print����ƁA�u2�v�ƕ\�����ꂽ�B
�܂��A���̃v���O�����Ɠ����t�H���_���ɁAtest_repeat2.txt�Ƃ����A�����n�b�V���l������1��̃e�L�X�g�t�@�C�����쐬����B
���̒��g�͈ȉ��ł���B
	is
���̕���������n�b�V���l�͗���220�ł���B220���i�[����hashtable�̃��X�g�̒������A�Ԃ�l�Ƃ���print����ƁA�u1�v�ƕ\�����ꂽ�B
*/
int repeat(struct item* q)
{
	int count_list=0;
	while(q!=0)
	{
		count_list++;
		q= q->next;
	}
	return count_list;
}


/*
revers_cmp�́A�T������hashtable�̍\���̂̃|�C���^�ƁA���X�g�̐���\�������������Ɏ��B
�܂��Ap��h�Ƃ���������̃|�C���^���`���Aq���w���B
���ɁA������̃|�C���^word�ƁArever���`���Aword�́Ah�̕����񕔕����w���B
���ɁA���X�g����A���������I�сA���̕������֐�reverse�ŋt���ɂ���B
������A�t���ɂ���O�̎������܂ށA�����n�b�V���l�������X�g������Astrcmp�Ŕ�ׂāA
���������������printf����B�Ȃ���΃��X�g���I���܂Ŏ��X���Ɉڂ��Ă����B
������A�Ⴄ�����ł��J��Ԃ��A�Ⴄ���X�g�ł��J��Ԃ��B
*/
void reverse_cmp(struct item*q,int a)
{
	int i,j;
	struct item*p=q,*h=q;
	char *word=h->word,*rever;
	for(j=0;j<a;j++)
	{
		while(q!=0)
		{
			rever=reverse(h->word);
			if(strcmp(rever,q->word)==0)
			{
				printf("palindorome %s\n",q->word);
				count++;
			}
			q=q->next;
		}
		q=p;
		h=h->next;
	}
}


//pop�́A�����A�|�b�v�ɐ��������ꍇ�A�|�b�v��������Ԃ��Asp��1�������炷�B���s�����ꍇ��0��Ԃ��B
char pop()
{
	if (sp <= 0) return 0;
	sp--;
	return stack[sp];
}


//push�́A�C�ӂ̐��������Ɏ��A�X�^�b�N�T�C�Y�𒴂��Ă����ꍇ0��Ԃ��A�����Ă��Ȃ������ꍇ1��Ԃ��֐��B
int push(char c)
{
	if (sp >= STACK) return 0;
	stack[sp] = c;
	sp++;
	return 1;
}


/*
reverse�́A���镶����̃|�C���^�������Ɏ��Apush��pop���g���āA���̕�������t���ɂ��邽�߂̊֐��B
�e�X�g���@
�uabc�v�Ƃ���������̗v�f�����|�C���^�������Ɏ��Aprintf�ŕ\������ƁA�ucba�v�ƕ\�����ꂽ�B
*/
char *reverse(char *word)
{
	int i,len=strlen(word);
	char reversn[STACK],*pali;
	for(i=0;i<len;i++) push(word[i]);
	for(i=0;i<=len;i++) reversn[i]=pop();
	reversn[i]='\0';
	sp=0;
	pali=reversn;
	return pali;
}
