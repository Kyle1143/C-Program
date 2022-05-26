
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_HASH 256 //MAX_HASHを256と定義
#define STACK 100


struct item //構造体itemは文字のポインタと出現回数を数えるcountと構造体itemを指すポインタnextをメンバーに持つ
{
	int count;
	char *word;
	struct item *next;
};

struct item *hashtable[MAX_HASH];
int sp;
char stack[STACK];
int count;

 //関数のプロトタイプ宣言(昔の演習で作った関数)
int hash(char *string);
struct item *create_item(char *key,struct item *p);
char *create_string(char *buff1);
struct item *search_item(char *key, struct item *p);
void chainhash(char *key1);
struct item *delete_item(char *key, struct item *p);
char pop();
int push(char c);

//今回作った新しい関数
int repeat(struct item* q);
char * reverse(char *word);
void reverse_cmp(struct item*q,int a);
/*
このプログラムは、何らかのテキストファイルを読み込み、その中から、ハッシュ値の同じ文字を整理し、そこから「倒語」を探し出し、それを表示し、また、「倒語」の数も数え、表示するためのもの。
＊「bob」などの回文も「倒語」の定義に当てはまるので、「倒語」としてカウントすることにする。
テスト方法

まず、このプログラムと同じフォルダ内に、test.text1という、対応する倒語を3セット用意したテキストファイルを作成する。
その中身は以下である。
	deeps speed loop pool pans snap
このファイルを読み込み実行すると、
palindorome deeps
palindorome speed
palindorome pans
palindorome snap
palindorome loop
palindorome pool
倒語は6文字見つかりました.
と表示された。これは、正しく実行できているといえる。
また、このプログラムと同じフォルダ内に、test.text2という、対応する倒語2セットと、関係のない文字を3つ用意したテキストファイルを作成する。
その中身は以下である。
	no on revel lever dog cat key
このファイルを読み込み実行すると、
palindorome revel
palindorome lever
palindorome no
palindorome on
倒語は4文字見つかりました。
と表示された。これは、正しく実行できているといえる。
また、このプログラムと同じフォルダ内に、test.text3という、回文の文字2つと、関係のない文字を3つ用意したテキストファイルを作成する。
その中身は以下である。
	 bob madam test that this
このファイルを読み込み実行すると、
palindorome madam
palindorome bob
倒語は2文字見つかりました。
と表示された。これは、正しく実行できているといえる。
また、このプログラムと同じフォルダ内に、test.text4という、スペースのみを用意したテキストファイルを作成する。
このファイルを読み込み実行すると、
倒語は0文字見つかりました。
と表示された。これは、正しく実行できているといえる。
また、存在しない、error.txtというファイルを読み込ませると、
can not open 
と表示された。これは、正しく実行できているといえる。
*/
int main()
{
	int i,*p,k,kh,hantei;
	char buff[100],*test; //buffは読み込んだ文字列,delは削除したい文字列
	struct item *test1,*test2,*test3; //テスト用
	char *testn;
	FILE * istream; //ストリームを開く
	istream = fopen("dict.txt","r"); //tom.txtを開く
	if(istream == 0) //ファイルが開けなかった時
	{
		printf("can not open\n"); //メッセージを表示して終了
		return 1;
	}
	for(i=0;i<50000;i++) //文字数分
	{
		if(fscanf(istream, "%s", buff)==EOF) break; //文字列がないときは抜ける
		chainhash(buff); //hash表に文字列を登録
	}
	fclose(istream); //ファイルを閉じる
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
	printf("倒語は%d文字見つかりました.\n",count);
	return 0;
}


//create_stringは、ある文字列を引数に取り、strlenで長さを測った新たなメモリを用意し、そこに文字列をコピーするための関数。
char *create_string(char *buff1)
{
	char *p;
	p = (char *)malloc(sizeof(buff1)); 
	strcpy(p,buff1); 
	return p;
}


//create_itemは、文字列keyのポインタと構造体pのポインタを引数に取り、pのリストを左に伸ばすための関数。
struct item *create_item(char *key,struct item *p)
{
	struct item *list;
	list = (struct item *)malloc(sizeof(struct item));
	list -> count = 1;
	list -> word = create_string(key);
	list -> next = p;
	return list;
}


//search_itemは、ある文字列と構造体を引数に取り、その構造体のリストの中に入っているかを調べ、入っていたらその構造体を返し、入っていなかったら0を返すための関数。
struct item *search_item(char *key, struct item *p)
{
	while(p != 0)
	{
		if(strcmp(p->word,key)==0) return p;
		p = p ->next;
	}
	return 0; 
}

//chainhashは、文字列を引数に取り、まず、キーのハッシュ値を計算する。その後、ハッシュ値に対応するリストを制作し、その中にキーがあったらカウント数を増やし、なければそのリストに新たな項目を追加するため///の関数。
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


//hashは、文字列を受け取り、自分で設定した（今回は256）値で全文字コードを割った余りの値を返すための関数。
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
repeatは、ある構造体のポインタを引数に取り、その、左に伸びているリストの数を数えるための関数。
このプログラムと同じフォルダ内に、test.repeat1.txtという、同じハッシュ値をもつ2語のテキストファイルを作成する。
その中身は以下である。
	this hist
この文字列を持つハッシュ値は両方184である。184を格納するhashtableのリストの長さを、返り値としてprintすると、「2」と表示された。
また、このプログラムと同じフォルダ内に、test_repeat2.txtという、同じハッシュ値をもつ1語のテキストファイルを作成する。
その中身は以下である。
	is
この文字列を持つハッシュ値は両方220である。220を格納するhashtableのリストの長さを、返り値としてprintすると、「1」と表示された。
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
revers_cmpは、探したいhashtableの構造体のポインタと、リストの数を表す整数を引数に取る。
まず、pとhという文字列のポインタを定義し、qを指す。
次に、文字列のポインタwordと、reverを定義し、wordは、hの文字列部分を指す。
次に、リストから、文字列を一つ選び、その文字を関数reverseで逆順にする。
それを、逆順にする前の自分を含む、同じハッシュ値を持つリスト内から、strcmpで比べて、
同じ文字があればprintfする。なければリストが終わるまで次々左に移っていく。
それを、違う文字でも繰り返し、違うリストでも繰り返す。
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


//popは、もし、ポップに成功した場合、ポップ下文字を返し、spを1だけ減らす。失敗した場合は0を返す。
char pop()
{
	if (sp <= 0) return 0;
	sp--;
	return stack[sp];
}


//pushは、任意の数を引数に取り、スタックサイズを超えていた場合0を返し、超えていなかった場合1を返す関数。
int push(char c)
{
	if (sp >= STACK) return 0;
	stack[sp] = c;
	sp++;
	return 1;
}


/*
reverseは、ある文字列のポインタを引数に取り、pushとpopを使って、その文字列を逆順にするための関数。
テスト方法
「abc」という文字列の要素を持つポインタを引数に取り、printfで表示すると、「cba」と表示された。
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
