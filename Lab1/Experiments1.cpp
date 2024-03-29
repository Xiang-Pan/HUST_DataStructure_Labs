/*
File name:	Experiments1 
Author:		Xiang Pan,IOT1601,HUST
GitHub:		HoverWings
Email:		hover@hust.edu.cn
Description:Linear Table On Sequence Structure
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define BOUNDARY -3
#define EMPTYLIST -4


typedef int status;
typedef int ElemType; //数据元素类型定义


#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct SqList //顺序表（顺序结构）的定义
{ 
	ElemType * elem;
	int id;
	int length=0;
	int listsize=0;
}SqList;

status IntiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType & e);
status LocateElem(SqList L,ElemType e); //简化过
status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
status NextElem(SqList L,ElemType cur,ElemType & next_e);
status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L, int i, ElemType & e);
status ListTrabverse(SqList L);  //简化过
status LoadFromFile(char * filename, SqList & L);
status SaveToFile(char * filename, SqList  L);

status AddListSize(SqList & L);
status CutListSize(SqList & L);

//判断线性表是否存在
bool isExisted(SqList & L)
{
	if (L.elem != NULL&&L.listsize > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int main() 
{
	SqList L;

	SqList* pL;

	int op = 1;
	char fileName[20];
	ElemType  e;
	int ans;
	while (op) 
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. IntiaList       8. PriorElem\n");
		printf("    	  2. DestroyList     9. NextElem\n");
		printf("    	  3. ClearList       10. ListInsert\n");
		printf("    	  4. ListEmpty       11. ListDelete\n");
		printf("    	  5. ListLength      12. ListTraverse\n");
		printf("    	  6. GetElem         13. SaveToFile\n");
		printf("    	  7. LocateElem      14. LoadFromFile\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d", &op);
		switch (op) 
		{	
		case 1:
			if (IntiaList(L) == OK)
				printf("线性表创建成功！\n");
			else
				printf("线性表创建失败！\n");
			getchar(); getchar();
			break;
			
		case 2:
			if (isExisted(L))
			{
				if (DestroyList(L) == OK)
					printf("线性表删除成功！\n");
				else
					printf("线性表删除失败！\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			
		case 3:
			if (isExisted(L))
			{
				if (ClearList(L) == OK)
					printf("线性表清空成功！\n");
				else
					printf("线性表清空失败！\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			
		case 4:
			if (isExisted(L))
			{
				if (ListEmpty(L) == TRUE)
					printf("此线性表为空！\n");
				else
					printf("此线性表非空！\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}

			
		case 5:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			int length;
			if ((length = ListLength(L)) >= 0)
				printf("此线性表为长度为%d！\n", length);
			else 
				printf("无此线性表！\n");
			getchar(); getchar();
			break;

		case 6:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要获取的元素位置：\n");
			int i;
			scanf("%d", &i);		
			if (GetElem(L, i, e)) 
				printf("此线性表该位置的元素为:%d\n", e);
			else 
				printf("输入有误！\n");
			getchar(); getchar();
			break;

		case 7:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入你要获取的元素：\n");
			scanf("%d", &e);
			if ((ans = LocateElem(L, e))!=-1) 
				printf("此线性表该元素的位置为:%d\n", ans+1);
			else 
				printf("没有此元素！\n");
			getchar(); getchar();
			break;
		case 8:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("请输入你要获取前一个元素的元素：\n");
				scanf("%d", &e);
				status s= PriorElem(L, e, ans);
				if (s==OK)
					printf("此线性表该元素的前一个元素为:%d\n", ans);
				else
				{
					if (s == BOUNDARY)
					{
						printf("第一个元素没有前驱！\n");
					}
					else
					{
						printf("没有此元素！\n");
					}
				}				
			}		
			getchar(); getchar();
			break;
		case 9:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("请输入你要获取后一个元素的元素：\n");
				scanf("%d", &e);
				status s = NextElem(L, e, ans);
				if (s==OK)
					printf("此线性表该元素的后一个元素为:%d\n", ans);
				else
				{
					if (s == BOUNDARY)
					{
						printf("最后一个元素没有后继！\n");
					}
					else
					{
						printf("没有此元素！\n");
					}
				}
			}
			getchar(); getchar();
			break;
		case 10:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入你要插入元素的位置：\n");
			scanf("%d", &i);
			if (1 <= i&&i <= ListLength(L)+1)
			{
			}
			else
			{
				printf("插入元素位置输入错误！！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入你要插入的元素：\n");
			scanf("%d", &e);
			if (ListInsert(L, i, e)) 
				printf("已成功插入！\n");
			else 
				printf("插入失败！\n");
			getchar(); getchar();
			break;

		case 11:
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入你要删除元素的位置：\n");
			scanf("%d", &i);
			if (1 <= i&&i <= ListLength(L))
			{
			}
			else
			{
				printf("输入元素位置错误 超出边界！！\n");
				getchar(); getchar();
				break;
			}		
			if (ListDelete(L, i, e))
				printf("已成功删除！元素为：%d\n", e);
			else
				printf("输入有误！\n");	
			getchar(); getchar();
			break;

		case 12: 
			if (!isExisted(L))
			{
				printf("线性表不存在！！！\n");
				getchar(); getchar();
				break;
			}
			if (!ListTrabverse(L)) printf("线性表为空！\n");
			getchar(); getchar();
			break;

		case 13:  
			if (!isExisted(L))
			{
				printf("线性表不存在！！！无法保存\n");
				getchar(); getchar();
				break;
			}
			printf("\n请输入要保存的文件名：\n");
			scanf("%s", fileName);
			if (SaveToFile(fileName, L)) printf("已成功保存至文件!");
			else printf("保存失败！");
			getchar(); getchar();
			break;
		case 14:
			printf("\n请输入要读取的文件名：\n");
			scanf("%s", fileName);
			if (LoadFromFile(fileName, L)) printf("已成功从文件读取!");
			else printf("读取失败！");
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()


 //初始条件：线性表L存在或不存在。
 //操作结果：构造一个空的线性表。
status IntiaList(SqList & L) 
{
	if (isExisted(L))
	{
		printf("线性表已存在\n");
		if (ClearList(L) == OK)
			return OK;
		else
			return FALSE;	
	}
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

//初始条件：线性表L已存在。
//操作结果：销毁线性表L。
status DestroyList(SqList & L)
{
	if (!L.elem)
	{
		return OK;   //if L is empty
	}
	free(L.elem);             //free 
	L.length = 0;             //reset length
	L.listsize = 0;           //reset size
	return OK;
}

//初始条件：线性表L已存在；
//操作结果：将L重置为空表。
status ClearList(SqList &L) 
{
	if (!L.elem)
	{
		exit(ERROR);		
	}
	L.length = 0;                 //reset length
	//L.listsize = LIST_INIT_SIZE;  //reset size
	return OK;
}

//初始条件：线性表L已存在；
//操作结果：若L为空表则返回TRUE,否则返回FALSE。
status ListEmpty(SqList L) 
{
	if (L.length == 0) 
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

//初始条件：线性表已存在；
//操作结果：返回L中数据元素的个数。
int ListLength(SqList L)
{
	return L.length;
}

//初始条件：线性表已存在，1≤i≤ListLength(L)；
//操作结果：用e返回L中第i个数据元素的值。
status GetElem(SqList L, int i, ElemType &e)//get elem[i]
{
	i = i - 1;
	if (i < L.length&&i>=0) 
	{
		e = L.elem[i];
		return TRUE;
	}
	//if(L.listsize)
	else 
	{
		return FALSE;
	}
}

//初始条件：线性表已存在；
//操作结果：返回L中第1个与e满足关系compare（）关系的数据元素的位序，若这样的数据元素不存在，则返回值为0。
status LocateElem(SqList L, ElemType e)
{
	int i = 0;
	ElemType * head = L.elem;
	for (i = 0; i < L.length; i++) 
	{
		if (e == head[i])
		{
			return i;
		}
	}
	return -1;
}

//初始条件：线性表L已存在；
//操作结果：若cur是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
status PriorElem(SqList L, ElemType cur, ElemType & pre_e)
{
	
	int length = L.length;
	int i = 0;
	pre_e = 0;
	for (i = 0; i < length; i++) 
	{
		if (L.elem[i] == cur)
		{
			if (i >= 1) 
			{
				pre_e = L.elem[i - 1];
				return TRUE;
			}
			else
			{
				return BOUNDARY;
			}
		}
	}
	return FALSE;
}

//初始条件：线性表L已存在；
//操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义。
status NextElem(SqList L, ElemType cur, ElemType & next_e)
{
	int length = L.length;
	int i = 0;
	next_e = 0;//init to 
	for (i = 0; i < length; i++) 
	{
		if (L.elem[i] == cur) 
		{
			if (i + 1 < length) 
			{
				next_e = L.elem[i + 1];
				return TRUE;
			}
			else
			{
				return BOUNDARY;
			}
		}
	}
	return FALSE;
}

//初始条件：线性表L已存在且非空，1≤i≤ListLength(L)+1；
//操作结果：在L的第i个位置之前插入新的数据元素e。
status ListInsert(SqList & L, int i, ElemType e)//insert e at i
{
	int index = L.length;
	if (i > (index+1))		
	{
		return FALSE;
	}
	assert(L.length <= L.listsize);
	if (L.length == L.listsize) //if the list is full then resize
	{
		if (!AddListSize(L))
		{
			return OVERFLOW;
		}
	}
	ElemType * q = &(L.elem[i - 1]);//place
	ElemType * p = &(L.elem[L.length - 1]);
	for(; p >= q; p--)
	{
		*(p + 1) = *p;
	}
	*q = e;
	L.length++;
	return TRUE;
}

//初始条件：线性表L已存在且非空，1≤i≤ListLength(L)；
//操作结果：删除L的第i个数据元素，用e返回其值。
status ListDelete(SqList & L, int i, ElemType & e)
{
	int length = L.length;
	if (i > length)
	{
		return FALSE;
	}
	e = L.elem[i - 1];
	ElemType * q = &(L.elem[i - 1]);//place
	ElemType * p = &(L.elem[L.length - 1]);
	for (; q<p; q++)
	{
		*q=*(q + 1);
	}
	L.length--;
	if (L.length < ((L.listsize - LISTINCREMENT) - 2))
	{
		CutListSize(L);
	}
	return TRUE;
}

//INPUT：SqList & L
//OUTPUT:L's length got cut
status CutListSize(SqList & L)		
{
	ElemType * newBase = (ElemType *)realloc(L.elem, L.listsize - LISTINCREMENT);
	L.elem = newBase;                 
	L.listsize -= LISTINCREMENT;      
	return TRUE;
}

//INPUT：SqList & L
//OUTPUT:L's length add
status AddListSize(SqList & L)		
{
	ElemType * newBase = (ElemType *)realloc(L.elem, L.listsize + LISTINCREMENT);
	if (L.elem == NULL)
	{
		exit(OVERFLOW);
		return FALSE;
	}
	L.elem = newBase;                 
	L.listsize += LISTINCREMENT;      	
	return TRUE;
}

//初始条件：线性表L已存在；
//操作结果：依次对L的每个数据元素调用函数visit()。
status ListTrabverse(SqList L) 
{
	int i;
	printf("\n-------------------- all elements ------------------------------\n");
	for (i = 0; i<L.length; i++) printf("%d ", L.elem[i]);
	printf("\n------------------------- end ----------------------------------\n");
	return L.length;
}


//初始条件:线性表L已存在
//操作结果：从文件读取线性表L
status LoadFromFile(char * filename, SqList & L) 
{
	IntiaList(L);
	FILE  *fp;
	if ((fp = fopen(filename, "r")) == NULL) 
	{
		printf("文件打开失败\n ");
		return ERROR;
	}
	while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
	{
		L.length++;
	}
	fclose(fp);
	return TRUE;
}

//初始条件:线性表L已存在
//操作结果：将线性表L存入文件
status SaveToFile(char * filename, SqList  L) 
{
	FILE  *fp;
	if ((fp = fopen(filename, "wb")) == NULL) 
	{
		printf("文件写入错误\n ");
		return ERROR;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	fclose(fp);
	return TRUE;
}
