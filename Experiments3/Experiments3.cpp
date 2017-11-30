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


typedef struct BiTNode { 
	ElemType data;     
	struct BiTNode *lchild, *rchild; 
}BiTNode, *TNode, *BiTree;

typedef struct Tree 
{ 
	char name[20];  
	int length;
	int listsize;
	struct BiTNode *HeadNode; 
}Tree;


status InitBiTree(Tree&T);


//status IntiaList(LinkList & L);
//status DestroyList(LinkList & L);
//status ClearList(LinkList &L);
//status ListEmpty(LinkList L);
//int ListLength(LinkList L);
//status GetElem(LinkList L,int i,ElemType & e);
//status LocateElem(LinkList L,ElemType e); //简化过
//status PriorElem(LinkList L,ElemType cur,ElemType & pre_e);
//status NextElem(LinkList L,ElemType cur,ElemType & next_e);
//status ListInsert(LinkList & L,int i,ElemType e);
//status ListDelete(LinkList & L, int i, ElemType & e);
//status ListTraverse(LinkList L, void(*visit)(Position p));
//status LoadFromFile(char * filename, LinkList & L);
//status SaveToFile(char * filename, LinkList  L);
//
//void visit(Position p);


//int main() 
//{
//	LinkList L;
//	L.head = NULL;
//	L.tail = NULL;
//	int op = 1;
//	char fileName[20];
//	ElemType  e;
//	int ans;
//	while (op) 
//	{
//		system("cls");
//		printf("\n\n");
//		printf("      Menu for Linear Table On Sequence Structure \n");
//		printf("------------------------------------------------------\n");
//		printf("    	  1. IntiaList       8. PriorElem\n");
//		printf("    	  2. DestroyList     9. NextElem\n");
//		printf("    	  3. ClearList       10. ListInsert\n");
//		printf("    	  4. ListEmpty       11. ListDelete\n");
//		printf("    	  5. ListLength      12. ListTraverse\n");
//		printf("    	  6. GetElem         13.SaveToFile\n"); 
//		printf("    	  7. LocateElem      14. LoadFromFile\n");
//		printf("    	  0. Exit\n");
//		printf("------------------------------------------------------\n");
//		printf("    请选择你的操作[0~14]:");
//		scanf("%d", &op);
//		switch (op) 
//		{	
//		case 1:
//			if (IntiaList(L) == OK) 
//				printf("线性表创建成功！\n");
//			else 
//				printf("线性表创建失败！\n");
//			getchar(); getchar();
//			break;
//		case 2:
//			if (DestroyList(L) == OK) 
//				printf("线性表删除成功！\n");
//			else 
//				printf("线性表删除失败！\n");
//			getchar(); getchar();
//			break;
//		case 3:
//			if (ClearList(L) == OK) 
//				printf("线性表清空成功！\n");
//			else 
//				printf("线性表清空失败！\n");
//			getchar(); getchar();
//			break;
//		case 4:
//			if (ListEmpty(L) == TRUE) 
//				printf("此线性表为空！\n");
//			else 
//				printf("此线性表非空！\n");
//			getchar(); getchar();
//			break;
//		case 5:
//			int length;
//			if ((length = ListLength(L)) >= 0)
//				printf("此线性表为长度为%d！\n", length);
//			else 
//				printf("无此线性表！\n");
//			getchar(); getchar();
//			break;
//		case 6:
//			if (L.len <= 0)
//			{
//				if (L.head != NULL)
//				{
//					printf("表为空：\n");
//					getchar(); getchar();
//					break;
//				}
//				else
//				{
//					printf("表不存在！！！\n");
//					getchar(); getchar();
//					break;
//				}
//				
//			}
//			printf("请输入要获取的元素位置：\n");
//			int i;
//			scanf("%d", &i);		
//			if (GetElem(L, i, e)) 
//				printf("此线性表该位置的元素为:%d\n", e);
//			else 
//				printf("输入有误！\n");
//			getchar(); getchar();
//			break;
//		case 7:
//			if (L.len <= 0)
//			{
//				printf("表不存在！！！：\n");
//				break;
//			}
//			printf("请输入你要获取的元素：\n");
//			scanf("%d", &e);
//			if ((ans = LocateElem(L, e))) 
//				printf("此线性表该元素的位置为:%d\n", ans);
//			else 
//				printf("没有此元素！\n");
//			getchar(); getchar();
//			break;
//		case 8:
//			if (L.len <= 0)
//			{
//				if (L.head != NULL)
//				{
//					printf("表为空!!!\n");
//					getchar(); getchar();
//					break;
//				}
//				else
//				{
//					printf("表不存在!!!\n");
//					getchar(); getchar();
//					break;
//				}
//
//			}
//			else
//			{
//				printf("请输入你要获取前一个元素的元素：\n");
//				scanf("%d", &e);
//				if (PriorElem(L, e, ans))
//					printf("此线性表该元素的前一个元素为:%d\n", ans);
//				else
//					printf("没有此元素！\n");
//			}		
//			getchar(); getchar();
//			break;
//		case 9:
//			if (L.len <= 0)
//			{
//				if (L.head != NULL)
//				{
//					printf("表为空!!!\n");
//					getchar(); getchar();
//					break;
//				}
//				else
//				{
//					printf("表不存在!!!\n");
//					getchar(); getchar();
//					break;
//				}
//			}
//			else
//			{
//				printf("请输入你要获取后一个元素的元素：\n");
//				scanf("%d", &e);
//				if (NextElem(L, e, ans))
//					printf("此线性表该元素的后一个元素为:%d\n", ans);
//				else
//					printf("没有此元素！\n");
//			}
//			getchar(); getchar();
//			break;
//		case 10:
//			printf("请输入你要插入元素的位置：\n");
//			scanf("%d", &i);
//			printf("请输入你要插入的元素：\n");
//			scanf("%d", &e);
//			if (ListInsert(L, i, e)) 
//				printf("已成功插入！\n");
//			else 
//				printf("输入有误！\n");
//			getchar(); getchar();
//			break;
//		case 11:
//			if (L.len <= 0)
//			{
//				if (L.head != NULL)
//				{
//					printf("表为空!!!\n");
//					getchar(); getchar();
//					break;
//				}
//				else
//				{
//					printf("表不存在！！！\n");
//					getchar(); getchar();
//					break;
//				}
//			}
//			else
//			{
//				printf("请输入你要删除元素的位置：\n");
//				scanf("%d", &i);
//				if (ListInsert(L, i, e))
//					printf("已成功删除！元素为：%d\n", e);
//				else
//					printf("输入有误！\n");
//			}		
//			getchar(); getchar();
//			break;
//		case 12: 
//			//void *visitp = &visit;
//			if (L.len <= 0)
//			{
//				if (L.head != NULL)
//				{
//					printf("表为空!!!\n");
//					getchar(); getchar();
//					break;
//				}
//				else
//				{
//					printf("表不存在！！！\n");
//					getchar(); getchar();
//					break;
//				}
//			}
//			if (!ListTraverse(L, visit)) printf("线性表是表不存在！\n");
//			getchar(); getchar();
//			break;
//		case 13:  
//			printf("\n请输入要保存的文件名：\n");
//			scanf("%s", fileName);
//			if (SaveToFile(fileName, L)) printf("已成功保存至文件!");
//			else printf("保存失败！");
//			getchar(); getchar();
//			break;
//		case 14:
//			printf("\n请输入要读取的文件名：\n");
//			scanf("%s", fileName);
//			if (LoadFromFile(fileName, L)) printf("已成功从文件读取!");
//			else printf("读取失败！");
//			getchar(); getchar();
//			break;
//		case 0:
//			break;
//		}//end of switch
//	}//end of while
//	printf("欢迎下次再使用本系统！\n");
//}//end of main()
//

status InitBiTree(Tree & T)
{
	
	return status();
}
