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
このプログラムは、ある二分木を与え、もし、その二分木の整数の順番の構成が間違っていたら、"incorrect order"と表示する。
もし、記号の構成が間違っていたら、"ERROR:間違ったものが入力されています。"と表示する。そのとき、どこに間違いがあるかを確認するため、間違っている部分の記号も表示する。
しっかりとした二分木が与えられたら、main引数として与えた整数を挿入した、新しい二分木を表示する。

テスト方法
"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力を与え"8"を引数に与えたとき、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と表示されたことを目視確認した。
"<-,20,->"と入力を与え、"2"を引数に与えたとき、"<<-,2,->,20,->"と表示されたことを目視確認した。
"<-,20,-"、"ERROR:間違ったものが入力されています。(>)"と表示されたことを目視確認した。
"<<-,30,->,20,->"と入力を与えたとき、"incorrect order"と表示された。
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

//create_nodeは、左側の木の構造体のポインタと、節点の整数と、右側の木の構造体のポインタを引数に取り、新たに作った構造体nodeへのポインタを返すための関数。

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
search_btは、ある構造体のポインタと、ある整数を受け取り、二分探索木に、その整数があるかを探すための関数。あった場合はその文字までを表示し、なかった場合、また、端の文字を探した場合は、最後まで表示する。

テスト方法
引数に取る整数を30にして、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力したとき、20,30の順序で表示された。
これは、二分探索木を、20からスタートし、次に、20より大きい整数なので、右に進め、30を表示する。これで、30が見つかったので、表示を終了する。
引数に取る整数を1にして、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力したとき、20,10,5の順番で表示された。
これは、二分探索木を、20からスタートし、次に、20より小さい整数なので、左に進め、10を表示する。次に、10より小さい整数なので、左に進め、5を表示する。5で最後なので表示が終了する。
引数に取る整数を36にして、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力したとき、20,30,35の順番で表示された。
これは、二分探索木を、20からスタートし、次に、20より大きい整数なので、右に進め、300を表示する。次に、30より大きな整数なので、右に進め、35を表示する。35で最後なので表示が終了する。
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
read_treeは、nextchの指している文字列から木の要素を1つずつ読み込み、そのねになる構造体nodeへのポインタを返すための関数。

テスト方法
"<-,10,-"と入力したとき、"ERROR:間違ったものが入力されています。(>)"と表示されたので、">"の部分でエラーが起こったことを示せている。
また、エラーのテキストを、二つ目の'>'のところだけ"ERROR:テスト用2"と変えて"<-,10-＞"と入力したとき、"ERROR:テスト用2"と表示されたので、二つ目の","の部分でエラーが起こったことを示せている。
"-"と入力したとき、エラーメッセージが表示されなかったので正しい。
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
		printf("ERROR:間違ったものが入力されています。(<)\n");
	 	return 0;
	}
	else nextch++;;	

	struct node *p1;
	p1=read_tree();

	if(*nextch!=',')
	{
		printf("ERROR:間違ったものが入力されています。(,)\n")	;
		return 0;
	}
	else nextch++;

	int p2;
	p2=read_number();

	if(*nextch!=',')
	{
		printf("ERROR:間違ったものが入力されています。(,)\n")	;
		return 0;
	}
	else nextch++;

	struct node *p3;
	p3=read_tree();

	if(*nextch!='>')
	{
		printf("ERROR:間違ったものが入力されています。(>)\n")	;
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
check_nodeは、再帰関数を使った、深さ優先探索を、通りがけ順に並んでいるかを確認するための関数。確認の仕方としては、一つ前のcheck_nodeで表示した値より今の値の方が大きいかを調べる。もし、一つ前のcheck_nodeで表示した値より今の値の方が小さかったとき、"incorrect order"というエラーメッセージを表示する。

テスト方法
<<-,15,->,20,<-,7,->>と入力を与えたとき、"incorrect order"と表示されたことを目視確認した。
<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>と入力を与えたとき、エラーが出なかったことを目視確認した。
<<<-,5,->,10,<-,40,->>,20,<-,30,<-,35,->>>と入力を与えたとき、"incorrect order"と表示されたことを目視確認した。
*/

void check_node(struct node *f)
{
	if(f->value < check_number) printf("incorrect order\n");

	check_number = f->value;
}

/*
print_treeは、ある構造体のポインタを引数に取り、その二分木を表示するための関数。

テスト方法
引数として3引数の構造体
n1=create_node(0,10,0);
n2=create_node(0,30,0);
n3=create_node(n1,20,n2);
を受け取ったとき、"<<-,10,->,20,<-,30,->>"と表示された。これは、二分木として正しいといえる。

また、引数として4引数の構造体
	n1=create_node(0,25,0);
	n2=create_node(0,10,0);
	n3=create_node(n1,30,0);
	n4=create_node(n2,20,n3);
を受け取ったとき、"<<-,10,->,20,<<-,25,->,30,->>"と表示された。これは、二分木として正しいといえる。
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
insert_btは、構造体のポインタと、構造体のポインタを指すポインタと、ある整数を引数に取り、その整数を二分探索木に挿入するための再帰関数。

テスト方法
引数として、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力し、"36"を与えたとき、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,<-,36,->>>>"と出力されたことを目視確認した。
引数として、"<<<-,5,->,10,<-,15,->>,20,>>"と入力し、"36"を与えたとき、"<<<-,5,->,10,<-,15,->>,20,<-,36,->>"と出力されたことを目視確認した。
引数として、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力し、"0"を与えたとき、"<<<<-,0,->,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と出力されたことを目視確認した。
引数として、"<<<-,5,->,10,<-,15,->>,20,<-,30,<-,35,->>>"と入力し、"7"を与えたとき、"<<<-,5,<-,7,->>,10,<-,15,->>,20,<-,30,<-,35,->>>"と出力されたことを目視確認した。
引数として、"-"と入力し、"36"を与えたとき、"<-,36,->"と出力されたことを目視確認した。
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





