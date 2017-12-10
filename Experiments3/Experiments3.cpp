#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>
#include <String>
#include <cString>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define EMPTYLIST -3

#define DEFAULTDATA -101

typedef int LR;


typedef int status;
typedef int ElemType; //数据元素类型定义



#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10


typedef struct BiTNode 
{ 
	ElemType data;     
	struct BiTNode *lchild, *rchild; 
}*BiTNode,*BiTree,*BiTRoot;

typedef struct Tree 
{ 
	char name[20];  
	int length;
	int listsize;//二叉树链表
	struct BiTNode *head; 
}Tree;


//传入的为树根 如果是某个树的根节点 那么操作为此节点为根的子树
status InitBiTree(BiTRoot &T);
status DestroyBiTree(BiTRoot &T);
//几种实现方式
//status CreateBiTree(Tree &T, String definition);
status ClearBiTree(BiTRoot &T);
status BiTreeEmpty(BiTRoot &T);
int BiTreeDepth(BiTRoot &T);
BiTRoot Root(BiTRoot &T);
BiTNode Value(BiTRoot &T, ElemType &e);
status Assign(BiTRoot &T, ElemType &e, ElemType value);
BiTNode Parent(BiTRoot &T, ElemType &e);
BiTNode LeftChild(BiTRoot &T, ElemType &e);
BiTNode RightChild(BiTRoot &T, ElemType &e); 
BiTNode LeftSibling(BiTRoot &T, ElemType &e);
BiTNode RightSibling(BiTRoot &T, ElemType &e);

status InsertChild(BiTRoot &T, BiTNode &p, LR lr, BiTNode &c);//返回左子树或者右子树
status DeleteChild(BiTRoot &T, BiTNode &p, LR lr);

status PreOrderTraverse(BiTRoot &T, void(*visit)(BiTNode N));
status InOrderTraverse(BiTRoot &T, void(*visit)(BiTNode N));
status PostOrderTraverse(BiTRoot &T, void(*visit)(BiTNode N));
status LevelOrderTraverse(BiTRoot &T, void(*visit)(BiTNode N));


void visit(BiTNode N)
{
	printf("%d\t", N->data);
}



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


status InitBiTree(BiTRoot &T)//传入为头结点
{
	if (T->data!= NULL)
	{
		//此处执行清空
		return OK;
	}
	T = (BiTRoot)malloc(sizeof(BiTNode));
	T->data = DEFAULTDATA;
	return true;
}

status DestroyBiTree(BiTRoot &T)
{
	if (T->data == DEFAULTDATA)//Inited But Empty
	{
		free(T);
		T = NULL;//指针置空
		return OK;
	}
	if (T != NULL)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
		return OK;
	}
	else
	{
		printf("二叉树不存在，初始条件不满足");
		return false;
	}
}

status ClearBiTree(BiTRoot & T)
{
	assert(T != NULL);
	if (T->lchild != NULL)
	{
		DestroyBiTree(T->lchild);
	}
	if (T->rchild != NULL)
	{
		DestroyBiTree(T->rchild);
	}
	T->data = DEFAULTDATA;
	return true;
}

status BiTreeEmpty(BiTRoot & T)
{
	if (T->data == DEFAULTDATA)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int BiTreeDepth(BiTRoot & T)
{
	assert(T != NULL);
	int lheight = 0;
	int rheight = 0;
	int theight = 0;
	if (T->lchild != NULL)
	{
		lheight = BiTreeDepth(T->lchild);
	}
	if (T->rchild != NULL)
	{
		rheight = BiTreeDepth(T->rchild);
	}
	theight = lheight>rheight ? lheight + 1 : rheight + 1;
	return theight;
}

BiTRoot Root(BiTRoot & T)
{
	return T;
}


BiTNode Value(BiTRoot & T, ElemType &e)
{
	assert(T != NULL);
	if (T->data == DEFAULTDATA)
	{
		return NULL;
	}
	if (T->data == e)
	{
		return T;
	}
	if (T->lchild != NULL)
	{
		PreOrderTraverse(T->lchild, visit);  //访问左子节点
	}
	if (T->rchild != NULL)
	{
		PreOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	return NULL;
}

status Assign(BiTRoot & T, ElemType & e, ElemType value)
{
	BiTNode cNode = Value(T, e);
	if (cNode == NULL)
	{
		printf("未获取到当前节点");
		return ERROR;
	}
	cNode->data = value;
	return OK;
}

BiTNode Parent(BiTRoot & T, ElemType & e)
{
	assert(T != NULL);
	BiTNode vNode = Root(T);
	if (vNode->data == e)
	{
		printf("根节点，无父节点");
		return NULL;
	}
	if (e == DEFAULTDATA)
	{
		printf("输入值为数据默认值，无法查找\n");
		return NULL;
	}
	int top = -1;  
	BiTRoot stack[100], p;
	p = T;   
	stack[++top] = T;  
	while (top>-1) 
	{ 
		p = stack[top--];
		if (p == NULL)
		{
			continue;
		}
		if (p->lchild)
		{
			if (p->lchild->data == e) break;
			stack[++top] = p->lchild;
		}
		if (p->rchild) 
		{ 
			if (p->rchild->data == e) break;    
			stack[++top] = p->rchild; 
		}  
	}  
	if (top<-1) return NULL;   return p;
}

BiTNode LeftChild(BiTRoot & T, ElemType & e)
{
	BiTNode vNode = Value(T, e);
	if (vNode == NULL)
	{
		printf("查找节点不存在");
		return NULL;
	}
	if (vNode->lchild != NULL)
	{
		return vNode->lchild;
	}
	else
	{
		return NULL;
	}
}

BiTNode RightChild(BiTRoot & T, ElemType & e)
{
	BiTNode vNode = Value(T, e);
	if (vNode == NULL)
	{
		printf("查找节点不存在");
		return NULL;
	}
	if (vNode->rchild != NULL)
	{
		return vNode->rchild;
	}
	else
	{
		return NULL;
	}
}

BiTNode LeftSibling(BiTRoot & T, ElemType & e)
{
	BiTNode pNode=Parent(T,e);
	BiTNode lNode = pNode->lchild;
	if (lNode == NULL)
	{
		printf("无左兄弟\n");
		return NULL;
	}
	if (lNode->lchild->data == e)
	{
		printf("当前节点为父节点左孩子，无左兄弟");
		return NULL;
	}
	return lNode;
}

BiTNode RightSibling(BiTRoot & T, ElemType &e)
{
	BiTNode pNode = Parent(T, e);
	BiTNode rNode = pNode->rchild;
	if (rNode == NULL)
	{
		printf("无右兄弟\n");
		return NULL;
	}
	if (rNode->lchild->data == e)
	{
		printf("当前节点为父节点右孩子，无右兄弟");
		return NULL;
	}
	return rNode;
}

status InsertChild(BiTRoot & T, BiTNode &p, LR lr, BiTNode & c)
{
	if (lr == 0)//插入左子树
	{
		if (p->lchild == NULL)
		{
			p->lchild = c;
			return true;
		}
		else
		{
			ElemType e = p->data;
			BiTNode pPNode = Parent(p,e);
			c->rchild = p;
			pPNode->lchild = c;
			return true;
		}
	}
	if (lr == 1)//插入右子树
	{
		if (p->rchild == NULL)
		{
			p->rchild = c;
			return true;
		}
		else
		{
			ElemType e = p->data;
			BiTNode pPNode = Parent(p, e);
			c->rchild = p;
			pPNode->rchild = c;
			return true;
		}
	}
	return false;
}

status DeleteChild(BiTRoot & T, BiTNode & p, LR lr)
{
	if (lr == 0)//删除左子树
	{
		if (p->lchild == NULL)
		{
			printf("左子树不存在\n");
			return true;
		}
		else
		{
			ElemType e = p->data;
			BiTNode pPNode = Parent(p, e);
			pPNode->lchild = NULL;
			return DestroyBiTree(p);
		}
	}
	if (lr == 1)//删除右子树
	{
		if (p->rchild == NULL)
		{
			printf("右子树不存在\n");
			return true;
		}
		else
		{
			ElemType e = p->data;
			BiTNode pPNode = Parent(p, e);
			pPNode->rchild = NULL;
			return DestroyBiTree(p);
		}
	}
	return false;
}

status PreOrderTraverse(BiTRoot & T, void(*visit)(BiTNode N))
{
	assert(T != NULL);
	visit(T);								 //访问根节点
	if (T->lchild != NULL)
	{
		PreOrderTraverse(T->lchild, visit);  //访问左子节点
	}
	if (T->rchild != NULL)
	{
		PreOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	return true;
}

status InOrderTraverse(BiTRoot & T, void(*visit)(BiTNode N))
{
	assert(T != NULL);
	if (T->lchild!= NULL)
	{
		PreOrderTraverse(T->lchild, visit);  //访问左子节点
	}
	visit(T);								 //访问根节点
	if (T->rchild!= NULL)
	{
		PreOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	return true;
}

status PostOrderTraverse(BiTRoot & T, void(*visit)(BiTNode N))
{
	assert(T != NULL);
	if (T->lchild != NULL)
	{
		PreOrderTraverse(T->lchild, visit);  //访问左子节点
	}	
	if (T->rchild != NULL)
	{
		PreOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	visit(T);								 //访问根节点
	return true;
}

status LevelOrderTraverse(BiTRoot & T, void(*visit)(BiTNode N))
{
	assert(T != NULL);
	BiTNode NodeQueue[100];
	int frontIndex = 0;		//头部  头部弹出
	int rearIndex = 0;		//尾部	尾部插入
	NodeQueue[rearIndex++] = T;
	while (frontIndex != rearIndex)
	{
		BiTNode vNode = NodeQueue[frontIndex];
		frontIndex++;
		visit(vNode);
		if (vNode->lchild != NULL)
		{
			NodeQueue[rearIndex++]= vNode->lchild;
		}
		if (vNode->rchild != NULL)
		{
			NodeQueue[rearIndex++]= vNode->rchild;
		}
	}
	return true;
}

