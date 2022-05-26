

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *data[10000];

char *create_string(char *a);
int inputfile(FILE *fp);
void outputfile(FILE *os,int x);
void string_sort(int a);
void swap(int i,int j);


/*
���̃v���O�����́A���镶���t�@�C�������������Ƀ\�[�g���C�V�������t�@�C���ɏo�͂��邽�߂̂���
�e�X�g���@
�܂��A�ȉ��̓��e�̃t�@�C����ǂݍ��܂���
	I am a boy
	I like soccer very much
����ƁA�V����������t�@�C���ɂ�
I
I
a
am
boy
like
much
soccer
very
�ƕ\�����ꂽ�B
�܂��A�ȉ��̓��e�̃t�@�C����ǂݍ��܂���
aaa aa bbb aaaa ab abb 
����ƁA�V����������t�@�C���ɂ�
aa
aaa
aaaa
ab
abb
bbb
�ƕ\�����ꂽ�B
�܂��A�����Ȃ���Ԃ�ǂݍ��܂����
�V�����t�@�C���ɂ͉�������Ȃ�
*/


int main()
{
	printf("--start--\n");

	FILE *fp;
	int wordnum;
	fp = fopen("tom.txt","r"); 

	if(fp==0)
	{
		printf("������܂���ł����B\n");
		return 1;
	}
	else
	{
		wordnum = inputfile(fp);
		fclose(fp);
		printf("wordnum=%d\n",wordnum);
	}

	string_sort(wordnum);

	FILE *os;
	os = fopen("new.txt","w");
	
	if(os==0)
	{
		printf("�G���[����");
		return 1;
	}
	outputfile(os, wordnum);
	fclose(os);
	printf("--finish--");

	return 0;
}


char *create_string(char *a)
{
	char *newitem;
	newitem = (char *)malloc(sizeof(a));
	strcpy(newitem,a);
	return newitem;
}

/*
inputfile�́C�ǂݍ��񂾃f�[�^���ׂĂ̒P�ꂪ�����Ă���|�C���^�������Ɏ��A���ׂĂ̒P���ǂݍ��ށB
�O���[�o���ϐ��ŗp�ӂ����z��data�ɕۑ����邽�߂̊֐��B�܂��A�߂�l�Ƃ��āA�P�ꐔ��Ԃ��B
�e�X�g���@
	I am a boy
	I like soccer very much
�Ƃ����f�[�^�������Ɏ��Amain��wordnum��printf������A9�����ƕ\�����ꂽ�B
	bbb a aaa ab aa bb 
�Ƃ����f�[�^�������Ɏ��Amain��wordnum��printf������A6�����ƕ\�����ꂽ�B
*/
int inputfile(FILE *fp)
{
	int c=0;
	char **p=data;
	char buff[100];
	while(fscanf(fp,"%s",buff)!=EOF)
	{
		*p=create_string(buff);
		c++;
		p++;
	}	
	return c;
}


/*
outputfile�́Adata�t�@�C���ƁA�P�ꐔ�������Ɏ��A�z��data�ɓ����Ă���P���os�փR�s�[���邽�߂̊֐��B
�e�X�g���@
fprintf�̉��ɁA�R�s�[���ꂽdata��printf���邱�Ƃɂ���
data�t�@�C����
	I am a boy
	I like soccer very much
�Ƃ���ƁA
��ʏ��
I
I
a
am
boy
like
much
soccer
very
�ƕ\�����ꂽ�B
�܂��Adata�t�@�C����
	bbb a aaa ab aa bb 
�Ƃ���ƁA
��ʏ��
a
aa
aaa
ab
bb
bbb
�ƕ\�����ꂽ�B
*/
void outputfile(FILE *os,int x)
{
	int i;
	printf(" x:%d\n",x);
	for(i=0;i<=x-1;i++)
	{
		fprintf(os,"%s\n",data[i]);
	}
}


/*
string_sort�́A�ǂݍ���data�t�@�C���̒P�ꐔ�������Ɏ��Adata�t�@�C�����̒P����A
���������ɕ��ёւ��邽�߂̊֐��B�߂�l�͂Ȃ��B�܂��Aswap���Ȃ�������Ak�̃J�E���g��
���₵�A�P���swap���Ȃ���������break���邱�Ƃɂ����B
�e�X�g���@
main��data�ɁA
	data[0]="aaa\n"
	data[1]="bbb\n"
	data[2]="ccc\n"
	data[3]="vvv\n"
	data[4]="eee\n"
	data[5]="fff\n"
	data[6]="ggg\n"
�Ƃ����ƁA
	aaa
	bbb
	ccc
	eee
	fff
	ggg
	vvv
�ƁA�\�����ꂽ�B
main��data�ɁA
	data[0]="aaa\n"
	data[1]="bbb\n"
	data[2]="ccc\n"
	data[3]="ddd\n"
	data[4]="eee\n"
	data[5]="fff\n"
	data[6]="ggg\n"
�Ƃ����ƁA
	aaa
	bbb
	ccc
	ddd
	eee
	fff
	ggg
�ƁA�\�����ꂽ�B
*/
void string_sort(int a)
{
	int end,i,k;
	for(end=a-1;end>=0;end--)
	{
		k=0;
		for(i=0;i<end;i++)
		{
			if(strcmp(data[i],data[i+1])>0) 	swap(i,i+1);
			else	k++;
		}
		if(k==end)	break;
	}
}


/*
swap�́A�\�[�g���邽�߂ɕK�v�Ȋ֐��ŁA����P��̓Y�����ƁA���ׂ̗̒P��̓Y�����������Ɏ��A
���̗ד��m�̒P������ւ��邽�߂̊֐��B�߂�l�͂Ȃ��B
�e�X�g���@
main��data��
	data[0]="aaa\n"
	data[1]="bbb\n"
�Ƃ���Adata[0]�Adata[1]�̏��Ԃ�printf�����Ƃ��ɁA
	bbb
	aaa
�ƕ\�����ꂽ�B
main��data��
	data[6]="apple\n"
	data[80]="happy\n"
�Ƃ���Adata[6]�Adata[80]�̏��Ԃ�printf�����Ƃ��ɁA
	happy
	apple
�ƕ\�����ꂽ�B
*/
void swap(int i,int j)
{
	char *tmp;
	tmp=data[j];
	data[j]=data[i];
	data[i]=tmp;
}
