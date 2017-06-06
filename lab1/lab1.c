#include <stdio.h>
#include <malloc.h>
#include <locale.h>

typedef struct Line
{
    int n;
    int *ar;
} Line;

typedef struct Matrica
{
    int m;
    Line *pt;
} Matrica;

int input (Matrica *);
void output(Matrica );
void erase(Matrica *);
//void vr18(Matrica , int*);
int main()
{
    Matrica inp;
    int s,i,j,s1,s2;
    i=j=0;

    int* b;
    setlocale(LC_ALL, ".1251");
    printf("Введите кол-во строк, для каждой строки кол-во эл-ов и эл-ты\n");
    s = input(&inp);
    printf("Исходная матрица\n");
    output(inp);
    b = (int *) calloc(s,sizeof(int));
    s1=0;
    s2=0;
    for(i=0;i<inp.m;++i)
    {
        s1=0;
        s2=0;
        for(j=0; j<inp.pt[i].n; ++j)
            if(j % 2)
                s1+=inp.pt[i].ar[j];
            else
                s2+=inp.pt[i].ar[j];
        b[i]=s1-s2;

    }
    printf("Вектор b: \n");
    for(j=0;j<i;j++)
        printf("b[%d]=%d\n",j,b[j]);

    erase(&inp);

    free(b);

    return 0;

}

void erase(Matrica *rm)
{
   int i;
    for(i=0; i<rm->m; i++) {
        free(rm->pt[i].ar);
    }
    free(rm->pt);
    rm->pt = NULL;

}

int baka() {
    int i;
    char *err;
    err="";
    while(scanf("%d",&i) != 1)
    {
        printf("%s",err);
        while(getchar() != '\n');
        err = "try again\n";
    }
    return i;
}

int input (Matrica *rm)
{
    int a, m,i,n,j;
    char *err;
    err="";
    printf("Кол-во строк \n");
    do
    {
      printf("%s",err);
      m = baka();\
      err = "try again\n";
    }
    while (m<=0||m>20);
    err="";
    rm->m = m;
    rm->pt = (Line *) calloc(m,sizeof(Line));
    for (i=0; i<m; ++i)
    {
        printf("Кол-во эл-ов\n");
        do
        {
            printf("%s",err);
            n = baka();\
            err = "try again\n";
        }
        while (n<0||n>20);
        err="";
        rm->pt[i].n=n;
        rm->pt[i].ar = (int *) calloc(n,sizeof(int *));
        for(j=0; j<n; ++j)
        {
            printf("a[%d] = ",j);
            a = baka();
            printf("\n");
            rm->pt[i].ar[j]=a;
        }
    }
    return m;
}
void output(Matrica rm)
{
    int i,j;
    for(i=0;i<rm.m;++i)
    {
        for(j=0; j<rm.pt[i].n; ++j)
            printf("%d ",rm.pt[i].ar[j]);
        printf("\n");
    }
}


