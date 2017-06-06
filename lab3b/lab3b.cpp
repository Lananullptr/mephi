//ВАРИАНТ 23

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

const int SIZE = 10;
const int PRINTABLE_WIDE = 80;
const int DEFAULT_GENERATE = 20;

int hash_count = 0;

bool filebase = false;

struct Info {
    int release;
    size_t sizeofinfo;
    long offset;
    char *txtinfo; //3a version
    Info *next;
};

struct Item {
    int key;
    int release_count;
    Info *info;
    Item *next;
};
const char *msgs[] = {"0. Выход\n",
                      "1. Добавить\n",
                      "2. Найти\n",
                      "3. Удалить\n",
                      "4. Вывод на экран\n",
                      "5. Удалить таблицу\n",
                      "6. Последний рез-т поиска\n",
                      "7. Сохранить таблицу\n",
                      "8. Загрузить таблицу\n"
                     };
const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
int max_menu_length = 0;
int D1_Add(Item **);
int D2_Find(Item **);
int D3_Delete(Item **);
int D4_Show(char *showtxt, Item **);
int D4_Show(Item **);
//int D5_Generate(Item **);
int D5_DeleteTable(Item **);
int D6_ShowLastResult(Item **);
int D7_SaveTable(Item **);
int D8_LoadTable(Item **);

int (*fptr[])(Item **) = {NULL, D1_Add, D2_Find, D3_Delete, D4_Show, D5_DeleteTable, D6_ShowLastResult,
        D7_SaveTable, D8_LoadTable};
//int my_dialog(const char *, int );
int my_dialog(const char *msgs[ ], int N);

#define hash(key) key%SIZE
Item *finditem(Item **ptab, int k, int release);
Info *findinfo(Item **ptab, int release);
Item *insert(Item **ptab, int k, char *info);
Item *insert(Item **ptab, int k, char *info, int release);
Item *insert2(Item **ptab, Info *info, Item *item, int release);
void init_tbl(Item **);
int delTable(Item**ptab, bool resultout);
//int delItem(Item**ptab);
//int delInfo(Item**ptab);
int getInt(int*);
int savetable(Item**);
int saveitem(Item *pitem);
//long saveinfo(Info*);
//Item *loadinfo(Item **ptab, int key, long offset);
int loadtable(Item**);
int getStr(char**);
int intlength(int );
Item *searchResult[SIZE];
char *tablefilename="default.tbl";
char *infofilename="info.tbl";
char *tablename;
//int inputfilename(tablefilename);
FILE *finfo, *ftbl;
//============================================
int main()
{   //size_t ll = sizeof(int);
    srand((unsigned int)time(NULL));
    Item *myTable[SIZE];
    init_tbl(myTable); init_tbl(searchResult);
    int rc;
    while( (rc = my_dialog(msgs, NMsgs)) > 0)
        if(!fptr[rc](myTable))    break;   // обнаружен конец файла
    printf("That's all. Bye!\n");
    savetable(myTable);
    delTable(myTable, true);
    return 0;
}
//============================================

int my_dialog(const char *msgs[ ], int N)
{
    char *errmsg = "";
    int rc = 1;
    do
    {
        puts(errmsg);
        errmsg = "Попробуйте еще раз.\n";
        if(rc == -1) system("cls");
        for(int i = 0; i < N; ++i)
        {

            printf("%s", msgs[i]); // вывод списка альтернатив

        }
        printf("\nВыбор пункта меню : --> ");
        if(getInt(&rc) == 0) rc = 0;   // конец файла – конец работы
    } while(rc < 0 || rc >= N);
    return rc;
}
//---------------------------------------------
Item *finditem(Item **ptab, int k)
{
    int ti = hash(k);
    if(ptab[ti] == NULL)
        return NULL;
    else
    {
        Item *pcur = ptab[ti];
        do
        {
            if(pcur->key == k) return pcur;
        } while( (pcur = pcur->next) != NULL);
    }
    return NULL;
}
//---------------------------------------------
Info *findinfo(Item *ptab, int release)
{
    Info *pinfo = ptab->info;
    do
    {
        if(pinfo->release == release) return pinfo;
    } while ( (pinfo = pinfo->next) != NULL);
}

int saveitem(Item* pitem)
{
    Info *pinfo = pitem->info;
    fwrite(&pitem->key, sizeof(int), 1, ftbl);
    fwrite(&pitem->release_count, sizeof(int), 1, ftbl);
    //printf("release_count=%d\n",pitem->release_count);
    do
    {
        //pinfo->offset = ftell(fbase);
        fwrite(&pinfo->release,sizeof(int),1,ftbl);
        fwrite(&pinfo->sizeofinfo,sizeof(size_t),1,ftbl);
        fwrite(&pinfo->offset,sizeof(long),1,ftbl);
    }while((pinfo = pinfo->next) != NULL);
    return 1;
}
//---------------------------------------------
int savetable(Item** ptab)
{
    Item *pcur;
    if((ftbl = fopen(tablefilename, "wb")) == NULL)
    {
        printf("Ошибка: нельзя открыть файл '%s'\n", tablefilename);
        return 1;
    }
    filebase = true;
    for(int i = 0; i < SIZE; i++)
    {
        if(ptab[i]==NULL)continue;
        pcur = ptab[i];
        do
        {
            saveitem(pcur);
        } while( (pcur = pcur->next) != NULL);
    }
    fclose(ftbl);
    return 1;
}


//---------------------------------------------
int loadtable(Item** ptab)
{
    Item *pcur, *ptmp;
    Info *curinfo, *tmpinfo;
    int key, h;
    //char tablefilename = (char*)calloc(strlen(info) + 1, sizeof(char));
    if((ftbl = fopen(tablefilename, "rb")) == NULL)
    {
        printf("Ошибка: нельзя открыть файл '%s'\n", tablefilename);
        return 1;
    }
    filebase = true;
    delTable(ptab, false);
    while(fread(&key, sizeof(int),1,ftbl) == 1)
    {
        //printf("reading key = %d\n", key);
        h = hash(key);
        ptmp = new Item;
        ptmp->key = key;
        fread(&ptmp->release_count, sizeof(int), 1, ftbl);
        ptmp->info = NULL;
        ptmp->next = NULL;
        for(int i = 1; i <= ptmp->release_count; i++)
        {
            tmpinfo = new Info;
            fread(&tmpinfo->release,sizeof(int),1,ftbl); //printf(" release = %d\n", tmpinfo->release);
            fread(&tmpinfo->sizeofinfo,sizeof(size_t),1,ftbl); //printf("sizeofinfo = %d\n", tmpinfo->sizeofinfo);
            fread(&tmpinfo->offset,sizeof(long),1,ftbl); //printf("offset = %d\n", tmpinfo->offset);
            tmpinfo->next = NULL;
            if(ptmp->info == NULL)
            {
                ptmp->info = tmpinfo;
            }
            else
                curinfo->next = tmpinfo;
            curinfo = tmpinfo;
        }
        if(ptab[h] == NULL)
        {
            ptab[h] = ptmp;
        }
        else
            pcur->next = ptmp;
        pcur = ptmp;
    }
    fclose(ftbl);
    return 1;
}
//---------------------------------------------
int D1_Add(Item **ptab)
{
    int k, rc;
    char *info = NULL;
    printf("Введите key: -->");
    if(getInt(&k) == 0) return 0; // обнаружен конец файла
    printf("Введите info: ");
    getStr(&info); // вся строка вводится целиком
    if(info == NULL) return 0;  // обнаружен конец файла
    insert(ptab, k, info); // вставка элемента
    free(info);   // в таблицу вставляется копия
    return 1;
}
//---------------------------------------------
int D2_Find(Item **ptab)
{
    int findkey;
    int findrelease;
    printf("Введите key для поиска: ");
    if(getInt(&findkey) == 0) return 0;
    printf("Введите номер release или '0' если нужно найти всё: ");
    if(getInt(&findrelease) == 0) return 0;
    delTable(searchResult, false);
    Item *fitem = finditem(ptab, findkey);
    if(fitem == NULL)
    {
        printf("Итог > В таблице нет такого key\n");
        return 1;
    }
    Info *finfo = fitem->info;
    if(findrelease == 0)
        for(; finfo != NULL; finfo = finfo->next)
        {
            insert2(searchResult, finfo, fitem, finfo->release);
        }
    else
    {
        finfo = findinfo(fitem,findrelease);
        if(finfo == NULL)
        {
            printf("Итог > В таблице есть key, но нет такого release\n");
            return 1;
        }
        insert2(searchResult, finfo, fitem, finfo->release);
    }
    D4_Show(" Итог поиска:\n", searchResult);
    return 1;
}
//---------------------------------------------
int D3_Delete(Item **ptab)
{
    int findkey;
    int findrelease;
    printf("Введите key для удаления: ");
    if(getInt(&findkey) == 0) return 0;
    printf("Введите номер release или '0' если нужно удалить всё: ");
    if(getInt(&findrelease) == 0) return 0;
    Info *pinfo = NULL;
    Item *fitem = finditem(ptab, findkey); //нашли элемент без инфо.

    if(fitem == NULL)
    {
        printf("Итог > В таблице нет такого key\n");
        return 1;
    }

    if ((ptab[hash(findkey)] == fitem) && (findrelease==0))
    {
        printf("Итог > Удалено %d элементов\n", fitem->release_count);
        ptab[hash(findkey)] = fitem->next;
        free(fitem);
        savetable(ptab);
        return 1;
    }
    if (findrelease) pinfo = findinfo(fitem, findrelease);
    if(pinfo == NULL)
    {
        printf("Итог > В таблице есть key, но нет такого release\n");
        return 1;
    }
    if(fitem->info==pinfo)
    {
        printf("Итог > Удален элемент\n");
        fitem->info = pinfo->next;
        free(pinfo);
        if(fitem->release_count==1)
            if (ptab[hash(findkey)] == fitem)
            {
                ptab[hash(findkey)] = fitem->next;
                free(fitem);
                //savetable(ptab);
                return 1;
            }
            else
            {
                Item *pitem = ptab[hash(findkey)];
                for(;pitem->next != fitem; pitem=pitem->next);
                pitem->next = fitem->next;
                free(fitem);
                //savetable(ptab);
                return 1;
            }
        else fitem->release_count--;
        //savetable(ptab);
        return 1;
    }
    else
    {
        printf("Итог > удален элемент\n");
        Info *finfo = fitem->info;
        for(int i=0 ; (i < fitem->release_count) && (finfo->next != pinfo); i++, finfo=finfo->next);
        finfo->next=pinfo->next;
        free(pinfo);
        //savetable(ptab);
        return 1;
    }

}
//---------------------------------------------
int D4_Show(Item **ptab)
{
    D4_Show("================ ТАБЛИЦА ================:\n", ptab);
}

int D4_Show(char *showtxt, Item **ptab)
{
    int numkey = 0;
    int numinfo = 0;
    char *txtinfo;
    printf("%s", showtxt);
    if((finfo = fopen(infofilename, "rb")) == NULL)
    {
       printf("Ошибка: невозможно открыть файл '%s'\n", tablefilename);
        return 1;
    }
    for(int i = 0; i < SIZE; i++)
        if(ptab[i] != NULL)
        {
            Item *ts = ptab[i];
            printf("=== ХЭШ %d : ===\n", i);
            do
            {
                int printed = 0;
                Info *tmpinfo = ptab[i]->info;
                numkey++;
                printed += printf("   => key=%d:", ts->key);
                do
                {
                    //printf("TEST === %d", tmpinfo->sizeofinfo);
                    txtinfo = new char[tmpinfo->sizeofinfo + 1];
                    fseek(finfo, tmpinfo->offset, SEEK_SET);
                    fread(txtinfo, sizeof(char), tmpinfo->sizeofinfo, finfo);
                    txtinfo[tmpinfo->sizeofinfo]='\0';
                    if(printed + strlen(" release  = ") +
                                 intlength(tmpinfo->release) +
                                 strlen(txtinfo) > PRINTABLE_WIDE &&
                            printed > strlen("   => key=:") + intlength(ts->key) + 1)
                    {
                        printf("\n");
                        printed = 0;
                    }
                    printed += printf(" release %d = %s;", tmpinfo->release, txtinfo);
                    numinfo++;
                    delete txtinfo;
                } while( (tmpinfo = tmpinfo->next) != NULL);
                printf("\n");
            } while( (ts = ts->next) != NULL);
        }
    if(numkey)
    {
        printf("-------------------------\n");
        printf("Таблица содержит: %d keys и %d info\n", numkey, numinfo);
    }
    else
        printf("Итог > Таблица не заполнена!\n");
    return 1;
}

//---------------------------------------------
int D5_DeleteTable(Item **ptab)
{
    delTable(ptab, true);
    return 1;
/*int whatdel = 0;
    printf("1. Delete all table\n");
    printf("2. Delete key with all releases\n");
    printf("3. Delete only one release\n");
    printf("Enter your choise or another value to cancel: ");
    if(getInt(&whatdel) == 0) return 0;
    switch(whatdel)
    {
        case 1:
                delTable(ptab, true);
                break;
        case 2:
                delItem(ptab);
                break;
        case 3:
                delInfo(ptab);
                break;
        default:
                printf("Result > canceled by user");
                break;
    }

    return 1;*/
}

//---------------------------------------------
int D6_ShowLastResult(Item **ptab)
{
    D4_Show("Последний рез-т поиска:\n", searchResult);
    return 1;
}
//---------------------------------------------
int D7_SaveTable(Item **ptab)
{
    savetable(ptab);
    return 1;
}

//---------------------------------------------
int D8_LoadTable(Item **ptab)
{
    delTable(ptab, false);
    loadtable(ptab);
    return 1;
}
//---------------------------------------------
Item *insert(Item **ptab, int k, char *info) //без релиза обычная вставка нового элемента
{
    return insert(ptab, k, info, -1);
}
//---------------------------------------------
Item *insert(Item **ptab, int k, char *info, int release) //release нужен для вставки в таблицу поиска
{
    Item *ptmp = finditem(ptab, k);
    if (ptmp == NULL)
    {
        ptmp = new Item;
        int h = hash(k);
        ptmp->key = k;
        ptmp->info = NULL;
        ptmp->release_count = 0;
        ptmp->next = ptab[h];
        ptab[h] = ptmp;
    }
    Info *pinfo = new Info;
    if(release != -1)
    {
        pinfo->release = release;

    }
    else if(ptmp->info) pinfo->release = ptmp->info->release+1;
    else pinfo->release = 1;

    if(info != NULL)
    {
        if((finfo = fopen(infofilename, "ab")) == NULL)
        {
            printf("Ошибка: невозможно открыть файл '%s'\n", tablefilename);
            return NULL;
        }
        fseek(finfo,0,SEEK_END);
        pinfo->offset = ftell(finfo); //printf("offset: %d\n", pinfo->offset);
        pinfo->sizeofinfo = strlen(info); //printf("sizeofinfo: %d\n", pinfo->sizeofinfo);
        fwrite(info,sizeof(char),pinfo->sizeofinfo,finfo);
        pinfo->txtinfo=info;
        fclose(finfo);
    }
    /*else
    {
        pinfo->sizeofinfo=ptmp->info->sizeofinfo;
        pinfo->offset=ptmp->info->offset;
        pinfo->release=ptmp->info->release;
        pinfo->txtinfo=ptmp->info->txtinfo;
    }*/
    pinfo->next = ptmp->info;
    ptmp->info = pinfo;
    ptmp->release_count++;

    //savetable(ptab);

    return ptmp;
}

Item *insert2(Item **ptab, Info *info, Item *item, int release)
{
        Item *ptmp = new Item;
        int h = hash(item->key);
        ptmp->key = item->key;
        ptmp->info = NULL;
        ptmp->release_count = 0;
        ptmp->next = ptab[h];
        ptab[h] = ptmp;
        Info *pinfo = new Info;
        if(release != -1)
    {
        pinfo->release = info->release;

    }
    else if(ptmp->info) pinfo->release = ptmp->info->release+1;
    else pinfo->release = 1;
    pinfo->sizeofinfo=info->sizeofinfo;
    pinfo->offset=info->offset;
    pinfo->release=info->release;
    pinfo->txtinfo=info->txtinfo;

    pinfo->next = ptmp->info;
    ptmp->info = pinfo;
    ptmp->release_count++;
    return ptmp;
}
//---------------------------------------------
void init_tbl(Item **ptab)
{
    for(int i = 0; i < SIZE; i++)
        ptab[i] = NULL;

    for(int i = 0; i< NMsgs; i++)
        if(max_menu_length < strlen(msgs[i])) max_menu_length = strlen(msgs[i]);
}

//---------------------------------------------
int delTable(Item **ptab, bool resultout)
{
    int infodeleted = 0;
    int itemsdeleted = 0;
    for(int i = 0; i<SIZE; i++)
    {
        if(ptab[i] == NULL) continue;
        for(Item *curitem = ptab[i]; curitem != NULL; itemsdeleted++)
        {
            for(Info *curinfo = curitem->info; curinfo != NULL; infodeleted++)
            {
                Info *delinfo = curinfo;
                curinfo = delinfo->next;
                delete delinfo;
            }
            Item *delitem = curitem;
            curitem = delitem->next;
            delete delitem;
        }
        ptab[i] = NULL;
    }
    if(resultout)
    {
        if(infodeleted == 0 && itemsdeleted == 0) printf("Нечего удалять!\n");
            else printf("Итог: %d items и %d info было удалено\n", itemsdeleted, infodeleted);
    }
    return 1;
}
//---------------------------------------------

/*
int delItem(Item**ptab)
{
    int delkey;
    printf("Enter items key for delete: ");
    if(getInt(&delkey) == 0) return 0;
    int ti = hash(delkey);
    if(ptab[ti] == NULL)
    {
        printf("Result > This key not found in table\n");
    }
    else
    {
        Item *pcur = ptab[ti];
        if(pcur->key == delkey)
        {

        }
        do
        {
            //if(pcur->key == delkey) return pcur;
        } while( (pcur = pcur->next) != NULL);
    }
    return NULL;
    return 1;
}

int delInfo(Item**ptab)
{
    return 1;
}
*/
//---------------------------------------------
//int inputfilename(tablefilename)
//{
//    printf("Enter name of table file: ");
//}
//---------------------------------------------
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
            printf("Error! Input integer value: ");
            scanf("%*[^\n]");
        }
    } while (n == 0);
    //scanf("%*c");
    return 1;
}
//---------------------------------------------
int intlength(int n)
{
    int c = 0;
    for (; n>0; n/=10, c++);
    return c;
}
//---------------------------------------------

