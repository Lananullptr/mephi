struct Item *input_list()
{
	struct Item *head = Null,*cur,*tmp;
	int n;
	char *err="";
	do
	{
		printf("%s\n", err);
		printf("Введите кол-во эл-ов от 0 до 20\n");
		err = "Повторите ввод\n";
		scanf("%d",&n);
	}while(n<0||n>20);
	while(n-->0)
	{
		tmp = malloc(sizeof(struct Item));
		printf("Введите элемент\n");
		scanf("%d", &tmp->a);
		tmp->next = Null;
		if(head == Null)
			head=cur=tmp;
		else
		{	
			cur->next = tmp;
			cur = cur->next;
		}
	}
	return head;
}

struct Item *input_list2()
{
	struct Item *head, **cur = &head;
	int n;
	printf("Введите кол-во эл-ов\n");
	scanf("%d", &n);
	while(n-->0)
	{
		*cur = malloc(sizeof(struct Item));
		printf("Введите элемент\n");
		scanf("%d", &(*cur)->a);
		cur = &(*cur)->next;
	}
	*cur = Null
	return head;
};

void print_list(struct Item *p)
{
	for (; p ; p = p->next)
		printf("%d ", p->a);
	printf("\n");
};

void print_list2(struct Item *p, int n)
{
	int i;
	for(i=1; p; p=p->next, i++)
		printf("%d%c", p->a, i%n&&p->next!=Null ? ' ':'\n');
}

void free_list(struct Item *p)
{
	struct Item *tmp;
	while(p)
	{
		tmp=p;
		p=p->next;
		free(tmp);
	}
}

void free_list2(struct Item *p)
{
	if(p)
	{
		free_list2(p->next);
		free(p);
	}
}

void oddeven_list(struct Item *p, struct Item **to1, struct Item **to2)
{
	for(; p; p = p->next)
		if(p->a%2)
		{
			*to1 = malloc(sizeof(struct Item));
			(*to1)->a = p->a;
			(*to1)->next=Null;
			to1 = &(*to1)->next;
		}
		else
		{
			*to2 = malloc(sizeof(struct Item));
			(*to2)->a = p->a;
			(*to2)->next=Null;
			to2 = &(*to2)->next;
		}
}

void  oddeven_list2(struct Item *p, struct Item **to1, struct Item **to2)
{
	struct Item ***to;
	for(;p;p=p->next)
	{
		to=p->a%2 ? &to1:&to2;
		**to = malloc(sizeof(struct Item));
		(**to)->a = p->a;
		*to = &(**to)->next;
	}
	*to1 = Null;
	*to2 = Null;
}

void sort(int a[], int n)
{
	int i,j,min,tmp;
	for(i=0;i<n-1;i++)
	{
		for(min=i, j=i+1; j<n; j++)
			if(a[j]<a[min])
				min=j;
			tmp=a[i];
			a[i]=a[min];
			a[min]=tmp;
	}
}

void sort_list(struct Item *p)
{
	struct Item *i,*j,*min;
	int tmp;
	for(i=p;i&&i->next;i=i->next)
	{	
		for(min=i; j=i->next; j=j->next)
			if(j->a < min->a) 
				min = j;
		tmp = i->a;
		i->a = min->a;
		min->a = tmp;
	}
}

void delzero_list(struct Item **p)
{
	struct Item *tmp;
	while(*p)
		if ((*p)->a)
			p=&(*p)->next;
		else
		{
			tmp = *p;
			*p=(*p)->next;
			free(tmp);
		}
}

freq_char_list(struct Item *p, char c)
{
	struct Item *q;
	for(q=p;q&&q->c!=c;q)
		if
		else
		{
			q=malloc(sizeof(struct Item));
			q->c=c;
			q->k=1;
			q->next=p;
			p=q;
		}
	return p;
}

struct item* freq_list(char str[])
{
	struct Item *q;
	for(q=null;*str; q=freq_char_list(q,*str++));
};


void gisto_list(struct Item *p)
{
	int i;
	for(;p;p=p->next)
	{	
		printf("%c ", p->c);
		for(i=0;i<p->k;i++)
			printf("*");
		printf("\n");
	}
}

void merge_list(struct Item *p, struct Item *q)
{
	struct Item *tmp;
	if(!p||!q) return;
	for(; p && p->next; p = p->next);
	for(tmp=q; q ; q=q->next)
	{
		q->next = p->next;
		p->next = q;
	}
	tmp->next = null;
}




int main()
{
	struct Item * from, *odd, *even;
	while(from = input_list)
	{
		printf("Исходный список\n");
		print_list(from);
		oddeven_list(from, &odd, &even);
		printf("Нечетный список\n");
		print_list(odd);
		printf("\n");
		print_list(even);
		free_list(from);
		free_list(odd);
		free_list(even);
	}
	return 0;
}

/*
Связь программы с ОС
int main(int argc, char* argv[],char* envp[])
$ a.out 12 ab 7
argc кол-во параметров включая a.out
argv массив указателей на строки (a.out\0 ; 12\0 ; ab\0 ; 7\0 ; null)
если параметр в "" то можно использовать пробелы "фи 12"
*/

int main(int argc, char* argv[], char* envp[])
{
	int i;
	for(i=0; i<argc; i++)
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	return 0;
}

// $ a.out *.c
// выводятся все файлы .с

#include <stdio.h>

int copy(FILE* , FILE*);

int main(int argc, char* argv[], char* envp[])
{
	FILE *from, *to;
	if(argc!=3)
	{
		fprintf(stderr, "Usage %s from file to file\n", argv[0]);
		return 1;
	}
	if((from=fopen(argv[1],"rb"))==NULL)
	{	perror(argv[1]);
		return 1;
	}
	if((to=fopen(argv[2],"wb"))==NULL)
	{
		perror(argv[2]);
		fclose(from);
		return 1;
	}
	if (copy(from, to)!=1) 
	{
		fprintf(stderr, "Error\n", );
		fclose(from);
		fclose(to);
		return 1;
	}

	fclose(from);
	fclose(to);
	return 0;
}

int copy(FILE *from, FILE *to)
{
	char buf[1024];
	int k;
	while((k=fread(buf,1,1024,from))>0)
	{
		fwrite(buf,1,k,to);
	}
	return !k;
}
/*
$env 
A=1
HOME = /student/b15v72/b15v7203

$

*/

int main(int argc, char* argv[], char* envp[])
{
	int i;
	for(i=0; envp[i]; i++)
		printf("%s\n", envp[i]);
	return 0;
}


/*

Структуры данных
физические - специфику хранения данных в памяти
			вектор , список 
логические - специфику обработки
			очередь FIFO, стек LIFO...

*/

#define SIZE 10

struct quere
{
	int a[size];
	int ib, ie, empty;
};

void init( struct quere *Q)
{
	Q->ib=Q->iq=0;
	Q->empty = 1;
}

int put(struct quere *Q, int k)
{
	if(Q->ib==Q->ie && !Q->empty)
		return 0;
	Q-> empty = 0;
	Q->a[Q->ie++]=k;
	if(Q->ie==SIZE)
		Q->ie = 0;
	return 1;
}

int get(struct quere *Q, int *pk)
{
	if(Q->empty)
		return 0;
	*pk = Q->a[Q->ib++];
	if(Q->ib ==SIZE) Q->ib = 0;
	if(Q->ib==Q->ie) Q->empty = 1;
	return 1;
}

// список

struct item
{
	int a;
	struct item *next;
};

struct queue
{
	struct item *pb, *pe;
};

void init(struct queue *Q)
{
  Q->pb=Q->pe = NULL;
}

int put(struct queue *Q, int k)
{
	struct Item *p;
	if(p = malloc(sizeof(struct Item)) == NULL)
		return 0;
	if(Q->pb)
	{
		Q->pb->next = p;
		Q->pb = p;
	}
	else
		Q->pb=Q->pe = p;
	p->a = k;
	p->next = NULL;
	return 1;
}

int get(struct queue *Q, int *pk)
{
	struct Item *p;
	if(Q->pe == NULL)
		return 0;
	p->Q->pe;
	Q->pe=Q->pe->next;
	if(!Q->pe) Q->pb = NULL;
	*pk = p->a;
	free(p);
	return 1;

}










