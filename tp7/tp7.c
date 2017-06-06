#include <stdlib.h>
#include <stdio.h>

struct Item
{
  int a;
  struct Item *next;
};

struct Item *input_list()
{
  struct Item *head = NULL, *cur, *tmp;
	int n;
	char *err="";
	do {
		printf("%s",err);
		printf("Введите кол-во элементов от 1 до 20 \n");
		err="Повторите ввод \n";
		scanf("%d", &n);
	} while(n<0||n>20);
	while(n-- > 0) {
		tmp = malloc(sizeof(struct Item));
		printf("Введите элемент: ");
		scanf("%d", &tmp->a);
		tmp->next = NULL;
		if (head == NULL) {
			head = cur = tmp;
		} else {
			cur->next = tmp;
			cur = cur->next;
		}
	}
	return head;
}

void print_list(struct Item *p)
{
 for(;p;p=p->next){
	printf("%d ",p->a);
	printf("\n");}
}

void free_list(struct Item *p)
{
  struct Item *tmp;
	while(p){
		tmp=p;
		p=p->next;
		free(tmp);
	}
}

void merge_list( struct Item *p, struct Item *q)
{

	struct Item *tmp;
	if(p==NULL||!q)return;
	for(;p&&p->next;p=p->next);
	for(;q;q=tmp)
	{
		tmp=q->next;
		q->next=p->next;
		p->next=q;
	}

}

void posneg_list(struct Item *p, struct Item **to1, struct Item **to2)
{

  for(;p;p=p->next)
		if((p->a)<0){
			*to1=malloc(sizeof(struct Item));//
			(*to1)->a=p->a;
			(*to1)->next=NULL;
			to1=&(*to1)->next;
		}else if ((p->a)>0){
			*to2=malloc(sizeof(struct Item));//
			(*to2)->a=p->a;
			(*to2)->next=NULL;
			to2=&(*to2)->next;
		}

}

void swap(struct Item *elem1, struct Item *elem2){
	int tmp;
	tmp=elem1->a;
	elem1->a = elem2->a;
	elem2->a=tmp;
}

void sort(struct Item *begin, int n)
{

  struct Item *p, *q;
  int tmp;
    for(p=begin; p!=NULL;p=p->next){
		for(q=p->next; q!=NULL;q=q->next)
        if(n==0)
     	 { if(p->a <  q->a) swap(p,q);}
       else if (n==1)
         { if(p->a > q->a) swap(p,q);}


    }
}

int main()
{
  struct Item *src, *pos, *neg;
  while(src = input_list())
  {
    printf("Source list \n");
    print_list(src);
    printf("1----\n");
    posneg_list(src, &pos, &neg);
    printf("2----\n");
    sort(pos, 0);
    printf("3----\n");
    sort(neg, 1);
    printf("4----\n");

    merge_list(pos, neg);

    printf("Result1: \n");
    print_list(pos);
    /*printf("Result2: \n");
    print_list(neg);
    */
    free_list(src);

    free_list(neg);

    free_list(pos);

  }
  return 0;
}

