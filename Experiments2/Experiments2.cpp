// line table base on linked list  with head node
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

#define DEFAULTDATA -1

typedef int status;
typedef int ElemType; //数据元素类型定义



#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10


typedef struct LNode // sequence list node definition
{
	ElemType data;
	LNode *next;
}*Link, *Position,LNode;

typedef struct  
{
	Link head, tail;
	int len;
}LinkList;


status MakeNode(Link&p,ElemType e)
{
	p= (Link)malloc(sizeof(LNode));
	if (p == NULL)
	{
		return false;
	}
	p->data = e;
	p->next = NULL;
	return true;
}

void FreeNode(Link&p)
{
	free(p);
}

status IntiaList(LinkList & L);
status DestroyList(LinkList & L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType & e);
status LocateElem(LinkList L,ElemType e); //简化过
status PriorElem(LinkList L,ElemType cur,ElemType & pre_e);
status NextElem(LinkList L,ElemType cur,ElemType & next_e);
status ListInsert(LinkList & L,int i,ElemType e);
status ListDelete(LinkList & L, int i, ElemType & e);
status ListTraverse(LinkList L, void(*visit)(Position p));
status LoadFromFile(char * filename, LinkList & L);
status SaveToFile(char * filename, LinkList  L);

void visit(Position p);


int main() 
{
	LinkList L;
	L.head = NULL;
	L.tail = NULL;
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
		printf("    	  6. GetElem         13.SaveToFile\n"); 
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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空！！！\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
			}
			if (ClearList(L) == OK) 
				printf("线性表清空成功！\n");
			else 
				printf("线性表清空失败！\n");
			getchar(); getchar();
			break;
		case 4:
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空！！！\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
			}
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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空！！！\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空！！！\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空!!!\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在!!!\n");
					getchar(); getchar();
					break;
				}

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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空!!!\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在!!!\n");
					getchar(); getchar();
					break;
				}
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
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空!!!\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
			}
			else
			{
				printf("请输入你要删除元素的位置：\n");
				scanf("%d", &i);
				if (ListDelete(L, i, e))
					printf("已成功删除！元素为：%d\n", e);
				else
					printf("输入有误！\n");
			}		
			getchar(); getchar();
			break;
		case 12: 
			//void *visitp = &visit;
			if (L.len <= 0)
			{
				if (L.head != NULL)
				{
					printf("表为空!!!\n");
					getchar(); getchar();
					break;
				}
				else
				{
					printf("表不存在！！！\n");
					getchar(); getchar();
					break;
				}
			}
			if (!ListTraverse(L, visit)) printf("线性表是表不存在！\n");
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



status IntiaList(LinkList & L)// now the first elem is empty
{
	if (L.head!=NULL)
	{
		return OK;
	}
	L.head = (Link)malloc(sizeof(LNode));
	L.tail = L.head;
	L.head->data = DEFAULTDATA;
	L.len = 0;
	return true;
}

status DestroyList(LinkList & L)
{
	if (L.head == L.tail)
	{
		free(L.head);
		return OK;
	}
	else//traversal and release the whole list
	{
		Position p = L.head;
		while (p != L.tail)
		{
			Position t = p->next;
			free(p);
			p = t;
		}
		free(p);
		L.len = 0;
		return OK;
	}
}

status ClearList(LinkList & L)
{
	if (L.head == NULL)//the LinkList is no existed  ERROR!
	{
		exit(ERROR);
		return false;
	}
	Position p = L.head;
	while (p != L.tail)
	{
		Position t = p->next;
		free(p);
		p = t;
	}
	free(p);
	L.len = 0; //the DEFAULTDATA is not the stored data
	L.tail = L.head;// with empty node
	L.head->data = DEFAULTDATA;
	return OK;
}

status ListEmpty(LinkList L)
{
	// linked list exists 
	if (L.len == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ListLength(LinkList L)
{
	return L.len;
}

status GetElem(LinkList L, int i, ElemType & e)
{
	Position p = L.head;
	int index = 1;
	while (p&&index < i)
	{
		p == p->next;
		index++;
	}
	if (!p || index > i)
	{
		return ERROR;
	}
	e = p->data;
	return OK;
}

status LocateElem(LinkList L, ElemType e)
{
	int index = 1;
	Position p = L.head;
	for (index = 1; index <= L.len; index++)
	{
		if (p->data == e)
		{
			return index;//the index begin from 1
		}
	}
	return -1;
}

status PriorElem(LinkList L, ElemType cur, ElemType & pre_e)
{
	Position p = L.head;
	int index = 1;
	pre_e = 0;
	ElemType pre_data = DEFAULTDATA;
	for (index = 1; index <= L.len; index++)
	{
		if (p->data == cur)
		{
			pre_e = pre_data;
			return true;
		}
		pre_data = p->data;
	}
	return false;
}

status NextElem(LinkList L, ElemType cur, ElemType & next_e)
{
	Position p = L.head;
	while (p != L.tail)
	{
		if (p->data = cur)
		{
			if ((p->next) != NULL)
			{
				next_e = p->next->data;
				return true;
			}
		}		
	}
	return false;
}

status ListInsert(LinkList & L, int i, ElemType e)
{
	if (i > L.len+1)
	{
		return false;
	}
	//process the init but empty linklist
	assert(L.head != NULL);
	if (L.head != NULL && L.head == L.tail && (L.head->data) == DEFAULTDATA )
	{
		if (i == 1)
		{
			Position p = L.head;
			p->data = e;
			L.len = 1;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (i == 1)
	{
		Position insertp;
		if (MakeNode(insertp, e))
		{
			insertp->next = L.head;
			L.head = insertp;
			L.len++;
			return true;			
		}
		else
		{
			return false;
		}
	}
	if (i == L.len+1)
	{
		Position insertp;
		if (MakeNode(insertp, e))
		{
			insertp->next=NULL;
			L.tail ->next= insertp;
			L.tail = insertp;
			L.len++;
			return true;
		}
		else
		{
			return false;
		}
	}
	int index = 1;
	Position p = L.head;
	for (index = 1; index < i; i++)
	{
		p = p->next;
	}
	Position pre = p;
	p = p->next;
	Position insertp;
	if (MakeNode(insertp, e))
	{
		pre->next = insertp;
		insertp->next = p;
		L.len++;
		return true;
	}
	else
	{
		return false;
	}

}

status ListDelete(LinkList & L, int i, ElemType & e)
{
	if (i > L.len)
	{
		return false;
	}
	if (i == 1)//此处需要处理链表只有一个节点 删除第一个节点的的情况
	{
		Position p = L.head;
		L.head = L.head->next;
		free(p);
		L.len--;
	}
	if (i == L.len)
	{
		Position p = L.head;
		while (p->next != L.tail)
		{
			p = p->next;
		}
		Position pre = p;
		free(p);
		pre->next == NULL;
		L.tail = pre;
		L.len--;
	}
	int index = 1;
	Position p = L.head;
	for (index = 1; index < i; i++)
	{
		p = p->next;
	}
	Position pre = p;
	p = p->next;
	pre->next = p->next;
	free(p);
	L.len--;
	return true;
}

void visit(Position p)
{
	printf("%d\t", p->data);
}

status ListTraverse(LinkList L,void (*visit)(Position p))
{

	Position p = L.head;
	while (p != L.tail)
	{
		visit(p);
		p = p->next;
	}
	visit(p);
	return true;
}

status LoadFromFile(char * filename, LinkList & L)
{
	IntiaList(L);
	FILE  *fp;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件打开失败\n ");
		return ERROR;
	}
	Position p = L.head;
	ElemType t = DEFAULTDATA;
	while (fread(&t, sizeof(ElemType), 1, fp))
	{
		
		Position insertp;
		if (MakeNode(insertp, t))
		{
			L.tail->next = insertp;
			L.tail = insertp;
			L.len++;
		}
		else
		{
			return false;
		}
	}
	fclose(fp);
	return true;
}

status SaveToFile(char * filename, LinkList L)
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);

	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("文件写入错误\n ");
		return ERROR;
	}
	Position p = L.head;
	while (p!=L.tail)
	{
		fwrite(&(p->data), sizeof(ElemType),1, fp);
		p = p->next;
	}
	fwrite(&(p->data), sizeof(ElemType), 1, fp);
	fclose(fp);
	return true;
}


