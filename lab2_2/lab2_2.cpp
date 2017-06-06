// ConsoleApplication2.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

//#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct StrList
{
	char Data;
	struct StrList *Next;
}StrList;

StrList *DelFirst(StrList *List)
{

	StrList* Del=NULL;

	if (List!= NULL)
	{
		Del = List;
		List = List->Next;
		free(Del);

	}

	return List;
}

StrList *DelNext(StrList *List)
{
	StrList* Del = NULL;

	if (List != NULL)
	{
		if (List->Next != NULL)
		{
			Del = List->Next;
			List->Next = List->Next->Next;
			free(Del);
		}
	}

	return List;

}

StrList *AddFirst(StrList *List,char Data)
{

	StrList *NewEl = NULL;
	NewEl=(StrList *)malloc(sizeof(StrList));

	NewEl->Next = List;
	NewEl->Data = Data;

	return NewEl;
}

StrList *AddNext(StrList *List, char Data)
{
	if (List != NULL)
	{
		StrList *NewEl = NULL;
		NewEl =(StrList *)malloc(sizeof(StrList));

		NewEl->Next = List->Next;
		List->Next = NewEl;
		NewEl->Data = Data;
	}
	else
	{
		List = AddFirst(List, Data);

	}
	return List;

}

StrList *ClearList(StrList *List)
{
	StrList *LastEl = List;
	StrList *CurrentEl = List;
	int SpOrTb=1;
	if (List != NULL)
	{
		//Ôèëüòðóåì ïåðâûå
		while (SpOrTb)
		{
			if (List != NULL)
			{
				if ((List->Data == ' ') || (List->Data == '	'))
				{
					List = DelFirst(List);
				}
				else
				{
					SpOrTb = 0;
				}
			}
			else
			{
				SpOrTb = 0;

			}

		}
		CurrentEl = List;
		LastEl = List;
		//Íàõîäèì ïîñëåäíþþ áóêâó
		while (CurrentEl != NULL)
		{
			if (!((CurrentEl->Data == ' ') || (CurrentEl->Data == '	')))
				LastEl = CurrentEl;
			CurrentEl = CurrentEl->Next;
		}

		//Âñå, ïîñëå ïîñëåäíåé áóêâû ôèëüòðóåì
		if (LastEl != NULL)
		{
			while (LastEl->Next != NULL)
			{
				LastEl = DelNext(LastEl);

			}
		}

	}

	return List;
}

StrList *FilterList(StrList* List)
{
	int CurrentSpace = 0;
	StrList *CurrentEl=List;

	if (List!= NULL)
	{
		while (CurrentEl->Next != NULL)
		{
			if (CurrentSpace)
			{
				if
					(
					(CurrentEl->Next->Data == ' ')
					||
					(CurrentEl->Next->Data == '	')
					)
				{
					CurrentEl = DelNext(CurrentEl);

				}
				else
				{
					CurrentEl = CurrentEl->Next;
					CurrentSpace = 0;
				}
			}
			else
			{
				if (CurrentEl->Next->Data == ' ')
				{
					CurrentEl = CurrentEl->Next;
					CurrentSpace = 1;
				}
				else if (CurrentEl->Next->Data=='	')
				{
					CurrentEl = AddNext(DelNext(CurrentEl),' ');
					CurrentEl = CurrentEl->Next;
					CurrentSpace = 1;
				}
				else
				{
					CurrentEl = CurrentEl->Next;
				}
			}

		}

	}
	return List;
}

int CountSpaceLR(StrList *List, int LengthStr)
{
	StrList *CurrentEl=List;
	int CountSpace = 0;
	int CountEl = 0;
	if (List != NULL)
	{
		while (CurrentEl != NULL)
		{
			CountEl += 1;
			CurrentEl = CurrentEl->Next;
		}


		CountSpace = (LengthStr - CountEl) / 2;

	}

	return CountSpace;

}

StrList *SelectLine(StrList **List)
	/*
	Âûäåëÿåì ñëåäóþùóþ ñòðîêó èç ècõîäíîé, List âåðí¸òñÿ áåç òåêóùåé ñòðîêè
	Ðåçóëüòàò ôóíêöèè - íà÷àëî òåêóùåé ñòðîêè äëÿ âûâîäà
	*/
{
	StrList *CurrentEl=*List;
	StrList *PrEl = NULL;
	StrList *NewLine=*List;
	int NewLineint = 0;
	if (List != NULL)
	{
		while ((!NewLineint))/*Íîâàÿ ñòðîêà íå ïîëó÷åíà*/
		{
			if (CurrentEl!=NULL)
			{
				if ((CurrentEl->Data == '\\')&&(CurrentEl->Next!=NULL))
				{
					if (CurrentEl->Next->Data=='n')
					{
						NewLineint = 1;
						*List = CurrentEl->Next->Next;/*"\n" íàéäåí, ïåðåíåñòè List ê íîâîé ñòðîêå*/

						if (PrEl == NULL)//Åñëè \n â íà÷àëå
						{
							//CurrentEl íà "\"
							CurrentEl=DelFirst(CurrentEl);/*  Óäàëèòü "\"  */
							CurrentEl=DelFirst(CurrentEl);/*  Óäàëèòü "n"  */

							NewLine = NULL;
						}
						else//Åñëè \n íå â íà÷àëå
						{
							CurrentEl = NULL;
							/*PrEl íà ïðåäûäóùåì îò "\"*/
							DelNext(PrEl);/*  Óäàëèòü "\"  */
							DelNext(PrEl);/*  Óäàëèòü "n"  */

							PrEl->Next = NULL; /*
											   Ñòðîêà îêîí÷åíà, íà÷àëî â "NewLine", êîíåö â "PrEl"
											   "List" ïåðåâåä¸í íà ñëåäóþùóþ ñòðîêó
											   */

						}
					}
					else
					{
						PrEl = CurrentEl;//Õðàíèì àäðåñ ïðåäûäóùåãî ýëåìåíòà
						CurrentEl = CurrentEl->Next;
					}

				}
				else
				{

					PrEl = CurrentEl;//Õðàíèì àäðåñ ïðåäûäóùåãî ýëåìåíòà
					CurrentEl = CurrentEl->Next;
				}
			}
			else /*Åñëè ïóñòàÿ èçíà÷àëüíî, ëèáî â ñàìîì êîíöå íåòó "\n"*/
			{
				NewLineint=1;
				*List=NULL;
			}

		}
	}

	return NewLine;
}



StrList *ShowStr(StrList *List)//Íà âõîäå òîëüêî ñòðîêà äëÿ âûâîäà
{
	//Î÷èñòèòü ýêðàí÷èê ëó÷øå áû
	int CountSpace=CountSpaceLR(List,79);//Óçíàåì ñêîëüêî ïðîáåëîâ äîáàâèòü â íà÷àëå è â êîíöå
    int i;
	for (i=0;i<CountSpace;i++)
	{
		printf(" ");
	}

	while (List!=NULL)
	{
		printf("%c",List->Data);
		List=DelFirst(List);
	}

	for (i=0;i<CountSpace;i++)
	{
		printf(" ");
	}
	printf("%s","\n");

	return List;
}



int main()
{

	/*
	Ïðàâèëà ââîäà:
	Ââîäèòñÿ ñòðîêà äî 500 ñèìâîëîâ
	Ñòðîêà âêëþ÷àåò ïðîáåëû, òàáû è "\n"
	Ââîä çàâåðøàåò ïî "Enter"
	*/

	StrList *List=NULL;
	StrList *CurrentEl = NULL;
	char Str[500];

	int i=0;
	gets(Str);


	while (Str[i]!='\0')
	{

		//CurrentEl=AddNext(CurrentEl,Str[i]);//Ôîðìèðóåì èñõîäíûé ñïèñîê
		if (i == 0)
		{
			CurrentEl = AddFirst(CurrentEl, Str[i]);
			List = CurrentEl;
		}
		else
		{

			CurrentEl = AddNext(CurrentEl, Str[i]);
			CurrentEl = CurrentEl->Next;
		}
		i+=1;
	}

	List=ClearList(List);//Î÷èñòèì ñòðîêó îò ëèøíåãî â íà÷àëå è â êîíöå
	List=FilterList(List);//Âûïðÿìèì ñòðîêó (ëèøíèå ïðîáåëû óäàëèòü, ïî íåîáõîäèìîñòè çàìåíèòü òàá íà ïðîáåë)

	while (List!=NULL)//Ïîñòðî÷íî âûâîäèì íà êàæäîé èòåðàöèè
	{
		ShowStr(SelectLine(&List));
	}


	gets(Str);
    return 0;
}

