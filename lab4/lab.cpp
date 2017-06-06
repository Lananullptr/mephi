
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
//#include <windows.h>


struct Item {
    int key;
    char *info;
    Item *right;
    Item *left;
};

const char *msgs[] = {"0. Exit\n",
                      "1. Add\n",
                      "2. Find\n",
                      "3. Delete\n",
                      "4. Print\n",
                      "5. Delete tree\n",
                      "6. Load tree\n",
                     };

const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
const int BUF_SIZE = 64;
int max_menu_length = 0;
int D1_Add(Item *);
int D2_Find(Item *);
int D3_Delete(Item *);
int D4_Show(Item *);
int D5_DeleteTable(Item *);
int D6_LoadTable (Item *);
int (*fptr[])(Item * ) = {NULL, D1_Add, D2_Find, D3_Delete, D4_Show,
D5_DeleteTable, D6_LoadTable};
int my_dialog(const char *msgs[ ], int N);
int getInt(int*);
int getStr(char**);
void cpyStr(char **, char *);
int rem( Item * , int );
void Print2(Item *, long );
void Print( Item *  );
Item *load( const char * , Item * );
Item *add( int , char *);
void freeNode( Item *  );
void copyNode(const Item * , Item * );
void nullNode( Item *  );
Item *init_tbl(Item *);
Item *insert(Item *, int , char *);


const int M = 20; /* максимальный размер таблицы */
Item *myTable;
char buf2[BUF_SIZE];

int main()
{   //size_t ll = sizeof(int);
    //setlocale(LC_ALL, "rus");
    //system("chcp 1251");
    //setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));


    //init_tbl(myTable);
    int rc;
    while( (rc = my_dialog(msgs, NMsgs)) > 0)
        if(!fptr[rc](myTable))    break;
    //savetable(myTable);
    //D5_DeleteTable(myTable);
    return 0;
}

int my_dialog(const char *msgs[ ], int N)
{
    char *errmsg = "";
    int rc = 1;
    do
    {
        puts(errmsg);
        errmsg = "Try again.\n";
        if(rc == -1) system("cls");
        for(int i = 0; i < N; ++i)
        {

            printf("%s", msgs[i]);

        }
        printf("\nYour choice : --> ");
        if(getInt(&rc) == 0) rc = 0;
    } while(rc < 0 || rc >= N);
    return rc;
}



int D1_Add(Item *ptab)
{
    int k;
    char *info = NULL;
    Item *tab = ptab;
    printf("Enter key: -->");
    if(getInt(&k) == 0) return 0;
    printf("Enter info: ");
    getStr(&info); // вся строка вводится целиком
    if(info == NULL) return 0;  // обнаружен конец файла
    tab = insert(ptab, k, info);
    if(tab!=NULL) // вставка элемента
    {
        if (ptab==NULL)
            myTable=tab;

	    return 1;
	}
	else return 0;
}

Item *finditem(Item *fitem, int k)
{
	if (fitem!=NULL)
	{
		if(fitem->key==k)
				return fitem;
			else if(fitem->key>k)
				finditem(fitem->left,k);
			else
				finditem(fitem->right,k);

	}
    else return NULL;
}

int D2_Find(Item *ptab)
{
	int findkey;
    printf("Enter key for find: ");
    if(getInt(&findkey) == 0) return 0;

    Item *fitem = ptab;
    fitem = finditem(fitem, findkey);

    if (fitem)
    	printf("Find result > key %d - info %s\n",fitem->key, fitem->info );
    else
    	printf("Result > key not found\n");
    return 1;
}


int D3_Delete(Item *item)
{
	int findkey;
    printf("Enter key for delete: ");
    if(getInt(&findkey) == 0) return 0;
    Item *fitem = finditem(item, findkey);
    if (fitem)
    {
        int i=0;
    	int del = rem(fitem, findkey);
    	if (del)  printf("Result > Node deleted\n");
    	else printf("Result > Node wasn`t delete\n");
    }
    else
    {
    	printf("Result > Key not found\n");
    }
    //нужно найти фактически удаляемый элемент
    // x - указатель на удаляемый эл-т
    // у - реально удаляемый эл-т
    return 1;
}

int D4_Show(Item *ptab)
{
    if (ptab)
        Print2(ptab,5);
    else
        printf("Tree is empty\n");
   return 1;
}

int D5_DeleteTable(Item *ptab)
{
    while(myTable)
        rem(myTable,myTable->key);
    return 1;
}

int D6_LoadTable(Item *ptab)
{

//    delTable(ptab, false);
    printf( "Enter file name: " );
			scanf( "%s", buf2 );

    myTable = load( buf2, ptab);
    return 1;
}



Item *insert(Item *ptab, int k, char *info)
{
    Item *cur = ptab;
    if (cur == NULL)
    {
        cur=add(k,info);
        //ptab = cur;
    }
    else
    {
	    if(k>cur->key)
	    	if (cur->right != NULL)

	    		insert(cur->right,k,info);

	    	else
	    		cur->right=add(k,info);
	    else if (k<cur->key)
	    	if (cur->left != NULL)

	    		insert(cur->left,k,info);

	    	else
	    		cur->left=add(k,info);
	    else
	    	return 0;
	}
    return cur;
}

Item *add(int k, char *info)
{
	Item *tmp = new Item;
	tmp->key=k;
	tmp->info=info;
	tmp->left=tmp->right=NULL;
	return tmp;
}

void copyNode( const Item * from, Item * to )
{
	to->key   = from->key;
	cpyStr(&to->info,from->info);
	//to->left  = from->left;
	//to->right = from->right;
}

void nullNode( Item * node )
{
	if( node == 0 ) return;

	freeNode( node->left );
	freeNode( node->right );

	if( node->info != 0 ) free( node->info );

	freeNode(node);
	//node->key   = 0;
	node->info= 0;
	node->left  = 0;
	node->right = 0;
}

void freeNode( Item * node )
{
	if( node == 0 ) return;

	freeNode( node->left );
	freeNode( node->right );

	if( node->info != 0 )
        free( node->info );

	free( node );
}

int rem( Item * root, int key )
{
	// если дерево пустое
	if( root == 0 ? true : root->info == 0 ) return 0;

	int cmp = (key == root->key ? 0 : (key > root->key ? 1 : -1));//strcmp( key, root->key );
	if( cmp > 0 )
		rem( root->right, key  );
	else if( cmp < 0 )
		rem( root->left, key);
	else
	{
		// если обоих детей нет
		if( root->left == 0 && root->right == 0 )
		{
			// зануляем текущий узел
            int i=0;
			Item *cur=myTable;
			if (root==myTable->right)
                i=1;
			else if (root==myTable)
			{
                i=3;
                free(myTable->info);
                free(myTable);
                myTable=NULL;
			}
			else
			{
                i=2;
			    cur = myTable->right;
			if (cur->left)
                while(cur->left != root)
                    cur=cur->left;
			}
			if(myTable)
                freeNode( root );
			if (i==1)
                myTable->right=NULL;
            else if(i==2)
                cur->left=NULL;
		}
		// если есть только левый
		else if( root->left != 0 && root->right == 0 )
		{

		    if (root!=myTable)
		    {
                Item * child = root->left;

                copyNode( child, root );
                root->left  = child->left;
                root->right = child->right;
                freeNode( child );
                root->left=NULL;
			}
			else
			{
                Item * child = root;
                myTable = root->left;
                free(child);
			}

		}
		// если есть только правый
		else if( root->left == 0 && root->right != 0 )
		{

			Item * child = root->right;
			copyNode( child, root );
			freeNode( child );
			root->right=NULL;
		}
		// если же оба есть
		else
		{
			// ищем в правом поддереве самый левый узел
			Item * curNode = root->right;
			Item * needNode = curNode;
			while( curNode != 0 )
			{
				if( curNode->info != 0 )
					needNode = curNode;
				curNode = curNode->left;
			}
            /*
			if (needNode!=root->right)
			{
			    curNode = root->right;
			if (curNode->left)
                while(curNode->left != needNode)
                    curNode=curNode->left;
			}
			else
                curNode=root;
                */

			// левый узел "самого левого узла" может оказаться пустым. освободим память
			//freeNode( curNode->left );

			// копируем данные
			root->key = needNode->key;
			//strcpy(root->info,needNode->info);
			cpyStr(&root->info,needNode->info);

			// рекурсивно удаляем узел
			rem( needNode, needNode->key );
			/*if(i==1)
                if (curNode!=root)
                    curNode->left=NULL;
                else
                    root->right=NULL;*/


		}
		//printf("hi\n");
	}
	return  1;
}

Item *load( const char * fileName, Item * root )
{
	FILE *	file;
	char	str[64];

	int		i;
    Item *tab = root;
	file = fopen( fileName, "r" );
    int len;
	if( 0 == file)
	{
		printf( "Can not open file '%s'\n", fileName );
		return 0;
	}

	while( 2 == fscanf( file, "%i%s", &i, str ))
	{
		if(str == NULL) return 0;  // обнаружен конец файла
		else
        {
            len = strlen(str);
            char *info = NULL;
            info = (char *) malloc(len+2);
            strncpy(info,str,len+1);
            tab = insert(root, i, info);
        }
        if(tab!=NULL) // вставка элемента
        {
            if (root==NULL)
                root=tab;
        }
    }
	fclose( file );

	return root;
}




void cpyStr(char **s, char *str)
{
    free(*s);
    int len = strlen(str);
    *s = (char *) malloc(len);
    strcpy(*s,str);
}


void Print( Item * root )
{
	// если дерево пустое - выводим символ пустого узла и всё
	if( root == 0 ? true : root->info == 0 )
	{
		return;
	}

	// правое поддерево
	Print( root->right );

	// выводим себя
	printf( "%s\n", root->info );

	// рекурсивно выводим левое поддерево
	Print( root->left );
}

void Print2(Item *q, long n)
{
   /* if (q)
   {
    Print2(q->right,n);
    printf("%s\n",q->info);
    Print2(q->left,n);
   }
   */
   long i;
   if (q!=NULL)
   {
      Print2(q->right, n+5);
      for (i = 0; i < n; i++)
         printf(" ");
      printf("%s\n", q->info);
      Print2(q->left, n+5);
   }
}


/*--------------------------------------------*/
Item *init_tbl(Item *ptab)
{

	ptab = (Item *)malloc( sizeof(Item) );
	//node->key		=	0;
	ptab->info		=	0;
	ptab->left		=	0;
	ptab->right		=	0;

	return ptab;
}

int getStr(char **s)
{
    char buf[21];
    int n; // scanf result
    int len = 0;
    *s = (char *)malloc(1);
    **s = '\0';
    scanf("%*c");
    do {
        n = scanf("%20[^\n]", buf);
        if (n < 0)
        {
            free(*s);
            return NULL;
        }
        if (n > 0)
        {
            len += strlen(buf);
            *s = (char *)realloc(*s, len + 1);
            if (*s)
                strcat(*s, buf);
            else
            {
                free(*s);
                return -2;
            }
        }
        else
            scanf("%*c"); //очистка буфера
    } while (n > 0);
    return 1;
}
//----------------------------------------------
int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if(n<0)return 0;
        if(n == 0){
            printf("Error! Enter number: ");
            scanf("%*[^\n]");
        }
    } while (n == 0);
    //scanf("%*c");
    return 1;
}
