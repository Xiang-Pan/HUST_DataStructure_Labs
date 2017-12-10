/* Linear Table On Sequence Structure */
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
#define EMPTYLIST -3


typedef int status;
typedef int ElemType; //数据元素类型定义


#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct  //顺序表（顺序结构）的定义
{ 
	ElemType * elem;
	int id;
	int length;
	int listsize;
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


int main() 
{
	SqList L1;
	L1.id = 1;
	L1.length = 0;
	L1.listsize = 0;
	SqList L2;
	L2.id = 2;
	L2.length = 0;
	L2.listsize = 0;
	SqList L3;
	L3.id = 2;
	L3.length = 0;
	L3.listsize = 0;

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
			if (DestroyList(L) == OK) 
				printf("线性表删除成功！\n");
			else 
				printf("线性表删除失败！\n");
			getchar(); getchar();
			break;
		case 3:
			if (ClearList(L) == OK) 
				printf("线性表清空成功！\n");
			else 
				printf("线性表清空失败！\n");
			getchar(); getchar();
			break;
		case 4:
			if (ListEmpty(L) == TRUE) 
				printf("此线性表为空！\n");
			else 
				printf("此线性表非空！\n");
			getchar(); getchar();
			break;
		case 5:
			int length;
			if ((length = ListLength(L)) >= 0)
				printf("此线性表为长度为%d！\n", length);
			else 
				printf("无此线性表！\n");
			getchar(); getchar();
			break;
		case 6:
			if (L.listsize <= 0)
			{
				printf("表不存在！！！：\n");
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
			if (L.listsize <= 0)
			{
				printf("表不存在！！！：\n");
				break;
			}
			printf("请输入你要获取的元素：\n");
			scanf("%d", &e);
			if ((ans = LocateElem(L, e))) 
				printf("此线性表该元素的位置为:%d\n", ans);
			else 
				printf("没有此元素！\n");
			getchar(); getchar();
			break;
		case 8:
			if (L.listsize <= 0)
			{
				printf("表不存在！！！不允许当前操作\n");
			}
			else
			{
				printf("请输入你要获取前一个元素的元素：\n");
				scanf("%d", &e);
				if (PriorElem(L, e, ans))
					printf("此线性表该元素的前一个元素为:%d\n", ans);
				else
					printf("没有此元素！\n");
			}		
			getchar(); getchar();
			break;
		case 9:
			if (L.listsize <= 0)
			{
				printf("表不存在！！！不允许当前操作\n");
			}
			else
			{
				printf("请输入你要获取后一个元素的元素：\n");
				scanf("%d", &e);
				if (NextElem(L, e, ans))
					printf("此线性表该元素的后一个元素为:%d\n", ans);
				else
					printf("没有此元素！\n");
			}
			getchar(); getchar();
			break;
		case 10:
			printf("请输入你要插入元素的位置：\n");
			scanf("%d", &i);
			printf("请输入你要插入的元素：\n");
			scanf("%d", &e);
			if (ListInsert(L, i, e)) 
				printf("已成功插入！\n");
			else 
				printf("输入有误！\n");
			getchar(); getchar();
			break;
		case 11:
			if (L.listsize <= 0)
			{
				printf("表不存在！！！不允许当前操作\n");
			}
			else
			{
				printf("请输入你要删除元素的位置：\n");
				scanf("%d", &i);
				if (ListInsert(L, i, e))
					printf("已成功删除！元素为：%d\n", e);
				else
					printf("输入有误！\n");
			}		
			getchar(); getchar();
			break;
		case 12: 
			if (!ListTrabverse(L)) printf("线性表是表不存在！\n");
			getchar(); getchar();
			break;
		case 13:  
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

status IntiaList(SqList & L) 
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

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

status ClearList(SqList &L) 
{
	if (!L.elem)
	{
		exit(ERROR);		
	}
	L.length = 0;                 //reset length
	L.listsize = LIST_INIT_SIZE;  //reset size
	return OK;
}

status ListEmpty(SqList L) 
{
	if (L.length == 0) 
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int ListLength(SqList L)
{
	return L.length;
}

status GetElem(SqList L, int i, ElemType &e)//get elem[i]
{
	if (i < L.length) 
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
		}
	}
	return FALSE;
}

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
		}
	}
	return FALSE;
}

status ListInsert(SqList & L, int i, ElemType e)//insert e at i
{
	int index = L.length;
	if (i > index)		
	{
		return FALSE;
	}
	assert(L.length <= L.listsize);
	if (L.length == L.listsize) //if the list is full then resize
	{
		AddListSize(L);
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

status ListDelete(SqList & L, int i, ElemType & e)
{
	int length = L.length;
	if (i > length)
	{
		return FALSE;
	}
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
status CutListSize(SqList & L)		
{
	ElemType * newBase = (ElemType *)realloc(L.elem, L.listsize - LISTINCREMENT);
	L.elem = newBase;                 
	L.listsize -= LISTINCREMENT;      
	return TRUE;
}

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


status ListTrabverse(SqList L) 
{
	int i;
	printf("\n-------------------- all elements ------------------------------\n");
	for (i = 0; i<L.length; i++) printf("%d ", L.elem[i]);
	printf("\n------------------------- end ----------------------------------\n");
	return L.length;
}

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
status SaveToFile(char * filename, SqList  L) 
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);

	if ((fp = fopen(filename, "wb")) == NULL) 
	{
		printf("文件写入错误\n ");
		return ERROR;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	fclose(fp);
	return TRUE;
}
