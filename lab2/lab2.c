#include <stdio.h>
#include <malloc.h>
#include <locale.h>

typedef struct String
{
    char c;
    struct String *p;
} String;

char* input_string();
String* true_list(String*);
String* add(String* , char , int );
String* rem(String* , String* );
String* centr(String* );
void print(String* );
String* str_list(char* );
void erase(String*);

int main()
{
    String *s;

    setlocale(LC_ALL, ".1251");

        s = str_list(input_string());
        s = true_list(s);
        s = centr(s);
        print(s);
        erase(s);

}

char* input_string() {
    char buf[256];
    char* str;
    int size;
    scanf("%[^EOF]s",&buf);
    for(size=0;buf[size]!=NULL;size++);
    str=(char*)calloc(size,sizeof(char));
    strncat(str,buf,size);
    return str;
}

String* str_list(char* str)
{
    String* head = NULL;
    String* last = NULL;
    //String* tmp = NULL;
    char* str_t = str;
    while(*str_t !='\0')
    {
        if(head==NULL)
        {    head=add(head,*str_t,0);
             last=head;
        }
        else
        {    add(last,*str_t,1);
             last=last->p;
        }
        *str_t++;
    }
    free(str);
    return head;
}

/*String* true_list(String* s)
{
    String *tmp=s;
    int i=0;
    for(;tmp->p!=NULL;tmp=tmp->p)
    {
        if(tmp==s && tmp->c==' '||tmp->c=='\t') s=rem(s,tmp);
        else
            if((tmp->p->c==' '||tmp->p->c=='\t')&&(tmp->p->p->c==' '||tmp->p->p->c=='\t'))
            s=rem(s,tmp);
        if((tmp->p->c==' '||tmp->p->c=='\t')&&(tmp->p->p==NULL))
            s=rem(s,tmp);
    }
    return s;
}*/

String* true_list(String* s)
{
    String *tmp=s;
    int state,state2;
    state=state2=0;
    int i=0;
    while((tmp!=NULL)&&((tmp->c==' ')||(tmp->c=='\t')))
    {
        s=rem(s,tmp);
        tmp=s;
    }
    if(tmp->p->c==' '||tmp->p->c=='\t') state=1;
    else if(tmp->p->c=='\n')
    {
        state=2;
        state2=2;
    }
    else state=3;
    for(;tmp->p!=NULL;)
    {
        switch(state)
        {
        case 1:
                tmp->p=rem(s,tmp->p);
                if(tmp->p!=NULL)
                {
                    if(tmp->p->c==' '||tmp->p->c=='\t') state=1;
                    else if(tmp->p->c=='\n')state=2;
                    else if(state2!=2)
                    {
                        add(tmp,' ',1);
                        tmp=tmp->p;
                        state=3;
                    }
                    else
                    {
                        tmp=tmp->p;
                        state=3;
                        state2=0;
                    }
                }
                break;
        case 2:
                    tmp=tmp->p;
                    if(tmp->p!=NULL)
                {
                    if(tmp->p->c==' '||tmp->p->c=='\t') state=1,state2=2;
                    else if(tmp->p->c=='\n') rem(s,tmp->p);
                    else
                    {
                        state=3;
                        state2=2;
                    }
                }
                break;
        case 3:
                if(tmp->p)
                {
                    if(tmp->p->c==' '||tmp->p->c=='\t') state=1;
                    else if(tmp->p->c=='\n') state=2;
                    else tmp=tmp->p, state2=0;
                }
                break;
        }

    }
    return s;
}

String* rem(String* head, String* r)
{
    String * tmp;
    if(r==head)
    {
        head=r->p;
        free(r);
        return head;
    }
    else
    {
        tmp=r->p;
        free(r);
        r=tmp;
        return r;
    }
}


String* add(String* head, char c, int i)
{
    String* tmp=head;
    String* t;
    switch (i)
    {
    case 0:
        t=(String*)calloc(1,sizeof(String));
        t->c=c;
        t->p=head;
        head=t;
        break;
    case 1:
        t=(String*)calloc(1,sizeof(String));
        t->c=c;
        t->p=head->p;
        tmp->p=t;
    }
    return head;
}


String* centr(String* head)
{
    //aaa bbbb\nmmmm lll lllll ddd\n\0
    String* tmp=head;
    String* tmp2=head;
    int i=0;
    int j,k,m;
    int space;
    j=k=m=0;
    for(;tmp2->p!=NULL;tmp2=tmp2->p)
        if (tmp2->c=='\n') k++;
    k++;
    tmp=tmp2=head;
    for(i=0;i<k;i++)
    {
        for(j=0;tmp2->p->c!='\n';tmp2=tmp2->p,j++);
        tmp2=tmp2->p;
        space=79-j;
        for(m=0;m<space;m++)
        {
            if (m==space/2)
                for(;tmp->p->c!='\n';tmp=tmp->p,j++);
            if(tmp==head)
            {
                head=add(head,' ',0);
                tmp=head;
            }
            else
                add(tmp,' ',1);
        }
        for(;tmp->c!='\n';tmp=tmp->p);
        if(tmp->p!=NULL)
            tmp2=tmp;
    }
    return head;
}

void print(String* head)
{
    String* t=head;
    for(;t->p!=NULL;t=t->p)
        printf("%c",t->c);
    printf("\n");
    //printf("%c",head->c);

}

void erase(String * head)
{
    String* tmp=NULL;
    while(head->p!=NULL)
    {    tmp=head;
        head=head->p;
        free(tmp);
    }
    free(head);
}
