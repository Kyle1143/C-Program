

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
このプログラムは、ある文字ファイルを辞書式順にソートし，新しく作るファイルに出力するためのもの
テスト方法
まず、以下の内容のファイルを読み込ませる
	I am a boy
	I like soccer very much
すると、新しく作ったファイルには
I
I
a
am
boy
like
much
soccer
very
と表示された。
また、以下の内容のファイルを読み込ませる
aaa aa bbb aaaa ab abb 
すると、新しく作ったファイルには
aa
aaa
aaaa
ab
abb
bbb
と表示された。
また、何もない状態を読み込ませると
新しいファイルには何も入らない
*/


int main()
{
	printf("--start--\n");

	FILE *fp;
	int wordnum;
	fp = fopen("tom.txt","r"); 

	if(fp==0)
	{
		printf("見つかりませんでした。\n");
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
		printf("エラー発生");
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
inputfileは，読み込んだデータすべての単語が入っているポインタを引数に取り、すべての単語を読み込む。
グローバル変数で用意した配列dataに保存するための関数。また、戻り値として、単語数を返す。
テスト方法
	I am a boy
	I like soccer very much
というデータを引数に取り、mainでwordnumをprintfしたら、9文字と表示された。
	bbb a aaa ab aa bb 
というデータを引数に取り、mainでwordnumをprintfしたら、6文字と表示された。
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
outputfileは、dataファイルと、単語数を引数に取り、配列dataに入っている単語をosへコピーするための関数。
テスト方法
fprintfの下に、コピーされたdataをprintfすることにする
dataファイルを
	I am a boy
	I like soccer very much
とすると、
画面上に
I
I
a
am
boy
like
much
soccer
very
と表示された。
また、dataファイルを
	bbb a aaa ab aa bb 
とすると、
画面上に
a
aa
aaa
ab
bb
bbb
と表示された。
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
string_sortは、読み込んだdataファイルの単語数を引数に取り、dataファイル内の単語を、
辞書式順に並び替えるための関数。戻り値はなし。また、swapしなかったら、kのカウントを
増やし、１回もswapしなかった時にbreakすることにした。
テスト方法
mainでdataに、
	data[0]="aaa\n"
	data[1]="bbb\n"
	data[2]="ccc\n"
	data[3]="vvv\n"
	data[4]="eee\n"
	data[5]="fff\n"
	data[6]="ggg\n"
といれると、
	aaa
	bbb
	ccc
	eee
	fff
	ggg
	vvv
と、表示された。
mainでdataに、
	data[0]="aaa\n"
	data[1]="bbb\n"
	data[2]="ccc\n"
	data[3]="ddd\n"
	data[4]="eee\n"
	data[5]="fff\n"
	data[6]="ggg\n"
といれると、
	aaa
	bbb
	ccc
	ddd
	eee
	fff
	ggg
と、表示された。
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
swapは、ソートするために必要な関数で、ある単語の添え字と、その隣の単語の添え字を引数に取り、
その隣同士の単語を入れ替えるための関数。戻り値はなし。
テスト方法
mainでdataに
	data[0]="aaa\n"
	data[1]="bbb\n"
といれ、data[0]、data[1]の順番でprintfしたときに、
	bbb
	aaa
と表示された。
mainでdataに
	data[6]="apple\n"
	data[80]="happy\n"
といれ、data[6]、data[80]の順番でprintfしたときに、
	happy
	apple
と表示された。
*/
void swap(int i,int j)
{
	char *tmp;
	tmp=data[j];
	data[j]=data[i];
	data[i]=tmp;
}
