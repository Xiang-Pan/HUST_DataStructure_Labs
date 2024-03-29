/*
File name:	Experiments3
Author:		Xiang Pan,IOT1601,HUST
GitHub:		HoverWings
Email:		hover@hust.edu.cn
Description:Tree structure without head node
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include<iostream>
#include <string.h>
#include<cstring>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define NOTFOUND -1
#define INFEASTABLE -1
#define OVERFLOW -2
#define EMPTYTREE -3
#define BOUNDARY -4

#define DEFAULTVALUE '#'

//define the buffer used to print the tree
#define MAXBUFROW 75
#define MAXBUFCOL 75

typedef int LR;


typedef int status;
typedef char ElemType; //数据节点类型定义



#define TREELISTSIZE 101
#define LISTINCREMENT  10


//二叉树节点定义
typedef struct BiTNode
{ 
	int key;
	ElemType value;     
	struct BiTNode *lchild, *rchild; 
}*pBiTNode,*BiTree,*BiTRoot,BiTNode;


//线性表节点定义
typedef struct TreeListNode
{
	char name[20];
	BiTree T;
	int nodeNum = 0;
}TreeListNode,*pTreeListNode;

//线性表定义
typedef struct TreeList
{
	pTreeListNode* elem;	//指向一个指针数组
	int length;
	int size;
}TreeList;

//全局变量定义
int nodeNum = 0;
char dispbuf[MAXBUFROW][MAXBUFCOL];//打印缓冲区

//传入的为树根 如果是某个树的根节点 那么操作为此节点为根的子树
status InitBiTree(BiTRoot &T);
status DestroyBiTree(BiTRoot &T);
//几种实现方式
status CreateBiTreeByDLR(BiTRoot &T, char* defiantion,int &index);//DLR WITH #
BiTRoot CreateBiTreeByDLR_LDR(BiTRoot &T, char* DLR,char *LDR,int length); //DLR LDR without #
BiTRoot CreateBiTreeByLRD_LDR(BiTRoot &T, char* LRD,char *LDR,int length);//LRD LRD without #
status ClearBiTree(BiTRoot &T);
status BiTreeEmpty(BiTRoot &T);
int BiTreeDepth(BiTRoot &T);
pBiTNode Root(BiTRoot &T);
ElemType Value(BiTRoot &T, int& key);
status Assign(BiTRoot &T, int& key, ElemType value);
pBiTNode Parent(BiTRoot &T, int& key);
pBiTNode LeftChild(BiTRoot &T, int& key);
pBiTNode RightChild(BiTRoot &T, int& key); 
pBiTNode LeftSibling(BiTRoot &T, int& key);
pBiTNode RightSibling(BiTRoot &T, int& key);
status InsertChild(BiTRoot &T, pBiTNode &p, LR lr, pBiTNode &c);//返回左子树或者右子树
status DeleteChild(BiTRoot &T, pBiTNode &p, LR lr);
status PreOrderTraverse(BiTRoot &T, void(*visit)(pBiTNode N));
status InOrderTraverse(BiTRoot &T, void(*visit)(pBiTNode N));
status PostOrderTraverse(BiTRoot &T, void(*visit)(pBiTNode N));
status LevelOrderTraverse(BiTRoot &T, void(*visit)(pBiTNode N));
status SaveToFile(char * filename, pBiTNode& L);
status LoadFromFile(char * filename, pBiTNode& L);


void PrintTree(BiTree &root, int root_x, int root_y, int r_c_interval, char disp_buf[][MAXBUFCOL]);
void beforePrint();
void printTreeToBuffer(BiTree &root, int root_x, int root_y, int r_c_interval, char disp_buf[][MAXBUFCOL]);
int afterPrint();
void printToScreen();

//判断树中节点是否存在
bool isExisted(BiTRoot &T)
{
	if (T!=NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判断线性表是否存在
bool isExistedTreeListNode(pTreeListNode TreeListNode)
{
	if (TreeListNode!= NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//INPUT:空节点指针
//OUTPUT:节点申请空间
bool MakeNode(pBiTNode &T)//传入节点指针
{
	T = (BiTRoot)malloc(sizeof(BiTNode));
	T->value = DEFAULTVALUE;
	T->key = nodeNum++;
	T->lchild = NULL;
	T->rchild = NULL;
	return true;
}

void visit(pBiTNode N)
{
	printf("%c\t", N->value);
}

//INPUT:树根节点T，获取节点KEY
//OUTPUT:获取节点指针
pBiTNode GetNodeByKey(BiTree &T,int key)
{
	assert(T != NULL);
	if (T->key == key)
	{
		return T;
	}
	if (T->lchild != NULL)
	{
		pBiTNode node = GetNodeByKey(T->lchild, key);  //访问左子节点
		if (node != NULL)
		{
			return node;
		}
	}
	if (T->rchild != NULL)
	{
		pBiTNode node = GetNodeByKey(T->rchild, key);  //访问右子节点
		if (node != NULL)
		{
			return node;
		}
	}
	return NULL;
}




int main()
{
	TreeList* pTL= (TreeList*)malloc(sizeof(TreeList));

	//TreeListNode elem[TREELISTSIZE] = {};
	pTL->elem = (pTreeListNode*)malloc(TREELISTSIZE * sizeof(pTreeListNode));//数组
	for (int i = 0; i < TREELISTSIZE; i++)
	{
		pTL->elem[i] = NULL;
	}
	pTL->size = TREELISTSIZE;
	pTL->length = 0;
	//pTL->elem=elem;
	
	
	pTreeListNode* opTreeListNode = NULL;
	BiTree pT = NULL;
	BiTree *ppT = NULL;


	int op = 1;
	int s = 0; //to save the return state
	int index = 0;//index为节点含有空节点的个数
	pBiTNode cT = NULL;//插入节点定义
	char fileName[20];
	char TreeName[20];
	int  key; 
	char value;
	pBiTNode returnNode=NULL;
	int ans;
	int opIndex;// the LinkListNum to operate
	LR lr;
	char definition[100] = {};
	pBiTNode node = NULL;

	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. InitBiTree       12. RightChild\n");
		printf("    	  2. DestroyBiTree    13. LeftSibling\n");
		printf("    	  3. CreateBiTree     14. RightSibling\n");
		printf("    	  4. ClearBiTree      15. InsertChild\n");
		printf("    	  5. BiTreeEmpty      16. DeleteChild\n");
		printf("    	  6. BiTreeDepth      17. PreOrderTraverse\n");
		printf("    	  7. Root	      18. InOrderTraverse\n");
		printf("    	  8. Value            19. PostOrderTraverse\n");
		printf("    	  9. Assign           20. LevelOrderTraverse\n");
		printf("    	  10. Parent          21. PrintTree\n");
		printf("    	  11. LeftChild       22. SaveToFile\n");
		printf("			      23. LoadFromFile\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~23]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1://1. InitBiTree
			printf("请输入你要初始化的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem)[opIndex];	
			if (*opTreeListNode == NULL)
			{
				*opTreeListNode = (pTreeListNode)malloc(sizeof(TreeListNode));
				(*opTreeListNode)->T = NULL;
				(*opTreeListNode)->nodeNum = 0;
			}
			else
			{
				printf("二叉树%d已存在\n",opIndex);
				getchar(); getchar();
				break;
			}
			// ;
			ppT = &(*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			printf("请输入二叉树名称\n");
			scanf("%s", TreeName);
			if (InitBiTree(*ppT) == OK)
			{
				strcpy((*opTreeListNode)->name, TreeName);
				pTL->length++;
				printf("二叉树%d创建成功！\n", opIndex);
			}
				
			else
				printf("二叉树%d创建失败！\n", opIndex);
			getchar(); getchar();
			break;

		case 2://2. DestroyBiTree
			printf("请输入你要销毁的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法销毁", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (DestroyBiTree(pT) == OK)
			{
				printf("二叉树%d删除成功！\n", opIndex);
				free(*opTreeListNode);
				*opTreeListNode = NULL;
			}		
			else
				printf("二叉树%d删除失败！\n", opIndex);
			getchar(); getchar();
			break;

		case 3://CreateBiTreeByDLR
			printf("请输入你要定义的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法定义", opIndex);
				getchar(); getchar();
				break;
			}
			if ((*opTreeListNode)->nodeNum != 0)
			{
				printf("二叉树%d存在且非空,无法定义", opIndex);
				getchar(); getchar();
				break;
			}
			nodeNum = (*opTreeListNode)->nodeNum;
			pT = (*opTreeListNode)->T;
			printf("请输入定义深度上限100 空节点为#\n");
			scanf("%s", definition);
			index = 0;
			if (CreateBiTreeByDLR(pT, definition, index) == OK)
			{
				printf("index%d\n", index);
				printf("definition%d\n", strlen(definition));
				if (index != strlen(definition))
				{		
					printf("定义有误\n");				
					printf("二叉树%d创建失败！\n", opIndex);
					ClearBiTree(pT);
				}
				else
				{
					printf("二叉树%d创建成功！\n", opIndex);
					(*opTreeListNode)->nodeNum = nodeNum;
					printf("二叉树共有%d节点", (*opTreeListNode)->nodeNum);
				}				
			}			
			else
				printf("二叉树%d创建失败！\n", opIndex);
			getchar(); getchar();
			break;

		case 4:
			printf("请输入你要定义的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法清空", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			if (ClearBiTree(pT) == OK)
			{
				printf("二叉树%d清空成功！\n", opIndex);
				(*opTreeListNode)->nodeNum = 0;
			}			
			else
			{
				printf("二叉树%d清空失败！\n", opIndex);
			}			
			getchar(); getchar();
			break;

		case 5://BiTreeEmpty
			printf("请输入你要查询是否为空的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			if (BiTreeEmpty(pT) == TRUE)
				printf("二叉树%d为空！\n", opIndex);
			else
				printf("二叉树%d非空！\n", opIndex);
			getchar(); getchar();
			break;

		case 6://BiTreeDepth
			printf("请输入你要查询深度二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}
			int Depth ;
			if ((Depth = BiTreeDepth(pT)) >= 0)
				printf("此二叉树为深度为%d！\n", Depth);
			else
				printf("无此二叉树！\n");
			getchar(); getchar();
			break;

		case 7://Root
			printf("请输入你要查询根节点二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}
			if (Root(pT))
			{
				pBiTNode root = Root(pT);
				printf("二叉树%d根节点的key为%d\n", opIndex, root->key);
				if (root->value == DEFAULTVALUE)
				{
					printf("value为默认value\n");
				}
				else
				{
					printf("根节点的value为%c", root->value);
				}
				getchar(); getchar();
				break;
			}
			else
			{
				printf("无根节点");//见鬼了
			}

		case 8://Value
			printf("请输入你要获取节点所在的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入要获取的节点编号\n");
			scanf("%d", &key);
			ans  = Value(pT, key);
			if (ans!=-1)
				printf("此二叉树该节点的value为:%c\n", ans);
			else
				printf("没有此节点！\n");
			getchar(); getchar();
			break;

		case 9://Assign
			printf("请输入你要获取赋值节点所属的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要赋值节点的编号：\n");
			scanf("%d%*c", &key);
			printf("请输入你要赋值节点的值(char)：\n");
			scanf("%c", &value);
			if (Assign(pT, key, value))
			{
				printf("赋值成功:%d号节点的值赋为%c\n", key,value);
			}
			else
			{
				printf("赋值失败！\n");
			}
			getchar(); getchar();
			break;

		case 10://Parent
			printf("请输入你要获取双亲的节点的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要获取双亲的节点编号：\n");
			scanf("%d", &key);
			returnNode = Parent(pT, key);
			if (returnNode !=NULL)
			{
				if (returnNode != pT)
				{
					printf("该节点的父节点编号为:%d\n", returnNode->key);
				}		
				else
				{
					if (returnNode->lchild->key == key || returnNode->rchild->key == key)
					{
						printf("该节点的父节点编号为:%d\n", returnNode->key);
					}				
					else
					{
						printf("根节点，无父节点");
					}				
				}
			}
			else
			{
				printf("没有此节点！\n");
			}
			getchar(); getchar();
			break;

		case 11://LeftChild		
			printf("请输入你要左孩子节点的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要获取左孩子节点的编号：\n");
			scanf("%d", &key);
			if (returnNode = LeftChild(pT, key))
			{
				if (returnNode != pT)
				{
					printf("该节点的左孩子节点编号为:%d\n", returnNode->key);
				}
				else
				{
					printf("查找节点不存在");
				}
			}
			else
			{
				printf("没有左孩子节点！\n");
			}
			getchar(); getchar();
			break;


		case 12://RightChild
			printf("请输入你要获取右孩子节点的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要获取右孩子节点的编号：\n");
			scanf("%d", &key);
			if (returnNode = RightChild(pT, key))
			{
				if (returnNode != pT)
				{
					printf("该节点的右孩子节点编号为:%d\n", returnNode->key);
				}			
				else
				{
					printf("查找节点不存在");
				}
			}
			else
			{
				printf("没有右孩子节点！\n");
			}
			getchar(); getchar();
			break;


		case 13://LeftSibling
			printf("请输入你要获取左兄弟节点的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要获取左兄弟节点的编号：\n");
			scanf("%d", &key);
			ans=Value(pT, key);
			if (ans == NOTFOUND)
			{
				printf("查找节点不存在!\n");
				getchar(); getchar();
				break;
			}
			if (returnNode = LeftSibling(pT, key))
			{
				if (returnNode != pT)
				{
					printf("该节点的左兄弟节点编号为:%d\n", returnNode->key);
				}		
				else
				{

				}
			}
			else
			{
				printf("没有左兄弟节点！\n");
			}
			getchar(); getchar();
			break;


		case 14://RightSibling
			printf("请输入你要获取右兄弟节点的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入你要获取右兄弟节点的编号：\n");
			scanf("%d", &key);
			ans = Value(pT, key);
			if (ans == NOTFOUND)
			{
				printf("查找节点不存在!\n");
				getchar(); getchar();
				break;
			}
			if (returnNode = RightSibling(pT, key))
			{
				if (returnNode != pT)
				{
					printf("该节点的右兄弟节点编号为:%d\n", returnNode->key);
				}			
			}
			else
			{
				printf("没有右兄弟节点！\n");
			}
			getchar(); getchar();
			break;


		case 15://InsertChild
			printf("请输入你要插入子树的二叉树的编号(0~100):");
			scanf("%d%*c", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入左0右1\n");
			scanf("%d%*c", &lr);
			//printf("lr%d\n",lr);
			if (lr != 0 && lr !=1)
			{
				printf("输入错误\n");
				getchar(); getchar();
				break;
			}
			printf("请输入想要插入子树的节点编号\n");
			scanf("%d%*c", &key);
			node=  GetNodeByKey(pT, key);
			if (node == NULL)
			{
				printf("无此节点");
				getchar(); getchar();
				break;
			}
			printf("请输入插入子树的定义\n");
			cT=NULL;
			InitBiTree(cT);
			scanf("%s", definition);
			index = 0;
			if (CreateBiTreeByDLR(cT, definition, index) == OK)
			{
				if (cT->rchild != NULL)
				{
					printf("右子树非空！插入失败");
					free(cT);
					cT = NULL;
					getchar(); getchar();
					break;
				}
				if ((index != strlen(definition)))
				{			
					printf("子树定义有误！\n");
					free(cT);
					cT = NULL;
					getchar(); getchar();
					break;
				}
				else
				{
					(*opTreeListNode)->nodeNum = nodeNum;
					printf("子树创建成功！\n");
				}
			}			
			else
			{
				printf("子树创建失败！\n");
			}			
			if (InsertChild(pT, node, lr, cT) == OK)
			{
				printf("插入成功\n");
			}
			else
			{
				printf("插入失败\n");
				DestroyBiTree(cT);
			}
			getchar(); getchar();
			break;

		case 16://DeleteChild
			printf("请输入你要删除子树的二叉树的编号(0~100):");
			scanf("%d%*c", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在！", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum == 0)
			{
				printf("二叉树%d为空！", opIndex);
				getchar(); getchar();
				break;
			}

			printf("请输入左0右1\n");
			scanf("%d%*c", &lr);
			if (lr != 0 && lr != 1)
			{
				printf("输入错误");
			}
			printf("请输入想要删除子树节点的编号\n");
			scanf("%d%*c", &key);
			node = GetNodeByKey(pT, key);
			if (node == NULL)
			{
				printf("无此节点！\n");
				getchar(); getchar();
				break;
			}
			if (DeleteChild(pT, node, lr) == OK)
			{
				printf("删除成功\n");
				printf("删除节点数目%d\n", (*opTreeListNode)->nodeNum-nodeNum);
				(*opTreeListNode)->nodeNum = nodeNum;
				printf("剩余节点数目%d\n", (*opTreeListNode)->nodeNum);
			}
			else
			{
				printf("删除失败\n");
			}
			getchar(); getchar();
			break;

		case 17://PreOrderTraverse
			printf("请输入你要前序遍历的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法遍历", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			s = PreOrderTraverse(pT, visit);
			if (s== OK)
			{
				printf("遍历成功\n");
			}
			else
			{
				if (s == EMPTYTREE)
				{
					printf("二叉树%d为空，遍历为空\n",opIndex);
				}
				else
				{
					printf("遍历失败\n");
				}
			}
			getchar(); getchar();
			break;

		case 18://InOrderTraverse
			printf("请输入你要中序遍历的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法遍历", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;

			s = InOrderTraverse(pT, visit);
			if (s== OK)
			{
				printf("遍历成功\n");
			}
			else
			{
				if (s == EMPTYTREE)
				{
					printf("二叉树%d为空，遍历为空\n", opIndex);
				}
				else
				{
					printf("遍历失败\n");
				}			
			}
			getchar(); getchar();
			break;

		case 19://PostOrderTraverse
			printf("请输入你要后序遍历的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法遍历", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			s = PostOrderTraverse(pT, visit);
			if (s == OK)
			{
				printf("遍历成功\n");
			}
			else
			{
				if (s == EMPTYTREE)
				{
					printf("二叉树%d为空，遍历为空\n", opIndex);
				}
				else
				{
					printf("遍历失败\n");
				}			
			}
			getchar(); getchar();
			break;

		case 20://LevelOrderTraverse
			printf("请输入你要层次遍历的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法遍历", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			s = LevelOrderTraverse(pT, visit);
			if (s== OK)
			{
				printf("遍历成功\n");
			}
			else
			{
				if (s == EMPTYTREE)
				{
					printf("二叉树%d为空，遍历为空\n",opIndex);
				}
				else
				{
					printf("遍历失败\n");
				}
			}
			getchar(); getchar();
			break;

		case 21://PrintTree
			printf("请输入你要打印的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法遍历", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			printf("nodeNum=%d\n", nodeNum);
			PrintTree(pT,20,0,4,dispbuf);
			getchar(); getchar();
			break;

		case 22://SaveToFile
			printf("请输入你要保存的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,无法保存", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (pT->value == DEFAULTVALUE)//Inited But Empty
			{
				printf("二叉树%d为空,无法保存", opIndex);
				getchar(); getchar();
				break;
			}
			if (SaveToFile(fileName, pT))
			{
				printf("成功\n");
			}
			else
			{
				printf("失败\n");
			}
			getchar(); getchar();
			break;

		case 23://LoadFromFile
			printf("请输入你要读取的二叉树的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opTreeListNode = &(pTL->elem[opIndex]);
			if ((*opTreeListNode) == NULL)
			{
				printf("二叉树%d不存在,需要初始化\n", opIndex);
				getchar(); getchar();
				break;
			}
			pT = (*opTreeListNode)->T;
			nodeNum = (*opTreeListNode)->nodeNum;
			if (nodeNum != 0)
			{
				printf("二叉树%d已存在,且不为空需要清空\n", opIndex);
				getchar(); getchar();
				break;
			}
			if (LoadFromFile(fileName, pT))
			{
				(*opTreeListNode)->nodeNum = nodeNum;
				printf("成功\n");
			}
			else
			{
				printf("失败\n");
			}
			getchar(); getchar();
			break;

		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()

//初始条件：二叉树T不存在
//操作结果：构造空二叉树T
status InitBiTree(BiTRoot &T)//传入为头结点
{
	if (T!=NULL)
	{
		//ClearBiTree(T);//初始化
		return OK;
	}
	T = (BiTRoot)malloc(sizeof(BiTNode));
	T->value = DEFAULTVALUE;
	T->key = nodeNum;//有节点 但是节点为空
	T->lchild = NULL;
	T->rchild = NULL;
	return true;
}

//初始条件：二叉树T已存在
//操作结果：销毁二叉树T 将当前T置为NULL
status DestroyBiTree(BiTRoot &T)
{
	if (T->value == DEFAULTVALUE)//Inited But Empty
	{
		nodeNum--;
		free(T);
		T = NULL;//指针置空
		return OK;
	}
	if (T != NULL)
	{
		if (isExisted(T->lchild))
		{
			DestroyBiTree(T->lchild);
		}
		if (isExisted(T->rchild))
		{
			DestroyBiTree(T->rchild);
		}
		nodeNum--;
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


//INPUT:树根指针，前序遍历字符串，当前字符串位置
//OUTPUT:根据创建二叉树
status CreateBiTreeByDLR(BiTRoot &T, char* defiantion,int& index)// de为 index=0
{
	if (index == strlen(defiantion))
	{
		return OK;
	}
	if (defiantion[index] == '#')
	{
		index++;
		T = NULL;
	}
	else
	{
		if (T != NULL)
		{
			if (T->value == DEFAULTVALUE)//第一个节点
			{ 
				T->value = defiantion[index];
				T->key = nodeNum++;
				printf("\nkey:%d\tvalue%c\n", T->key, T->value);
				index++;
				CreateBiTreeByDLR(T->lchild, defiantion, index);
				CreateBiTreeByDLR(T->rchild, defiantion, index);
			}
		}	
		else
		{
			MakeNode(T);
			T->value = defiantion[index];
			index++;
			printf("key:%d\tvalue%c\n", T->key, T->value);		
			CreateBiTreeByDLR(T->lchild, defiantion, index);
			CreateBiTreeByDLR(T->rchild, defiantion, index);
		}
	}
	//printf("index%d", index);
	return OK;
}

//构造的树根T指针(未申请空间)  
//根据前序和中序遍历构建指针
BiTRoot CreateBiTreeByDLR_LDR(BiTRoot & T, char * DLR, char * LDR,int length)
{
	if (length <= 0 || DLR == NULL || LDR == NULL)////递归出口深度为0时二叉树示建树完毕  
	{
		return NULL;
	}
	ElemType rootValue = LDR[0];
	InitBiTree(T);
	T->value = rootValue;
	int leftLength, rightLength, i = 0;//左子树的深度，右子树的深度  
	while (i<length&&LDR[i] != rootValue)
	{
		i++;
	}
	leftLength = i;
	rightLength = length - leftLength - 1;
	if (leftLength>0)//建立左子树  
	{
		 CreateBiTreeByDLR_LDR(T->lchild,DLR + 1, LDR, leftLength);
	}
	if (rightLength>0)//建立右子树  
	{
		 CreateBiTreeByDLR_LDR(T->rchild,DLR + length - rightLength, LDR + length - rightLength, rightLength);
	}
	return T;
}

//根据后序和中序遍历构建指针
BiTRoot CreateBiTreeByLRD_LDR(BiTRoot & T, char * LRD, char * LDR,int length)
{
	if (length <= 0 || LRD == NULL || LDR == NULL)////递归出口深度为0时二叉树示建树完毕  
	{
		return NULL;
	}
	ElemType rootValue = LDR[length-1];
	InitBiTree(T);
	T->value = rootValue;
	int leftLength, rightLength, i = 0;//左子树的深度，右子树的深度  
	while (i<length&&LDR[i] != rootValue)
	{
		i++;
	}
	leftLength = i;
	rightLength = length - leftLength - 1;
	if (leftLength>0)//建立左子树  
	{
		CreateBiTreeByLRD_LDR(T->lchild, LRD, LDR, leftLength);
	}
	if (rightLength>0)//建立右子树  
	{
		CreateBiTreeByLRD_LDR(T->rchild, LRD + leftLength, LDR + leftLength+1, rightLength);
	}
	return T;
}

//初始条件：二叉树T存在
//操作结果：按definition构造二叉树T
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
	T->value = DEFAULTVALUE;
	return OK;
}

//初始条件：二叉树T存在
//操作结果：若T为空二叉树则返回TRUE，否则返回FALSE
status BiTreeEmpty(BiTRoot & T)
{
	if (T->value == DEFAULTVALUE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//初始条件：二叉树T存在
//操作结果：返回T的深度
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

//初始条件：二叉树T存在
//操作结果：返回T的根
BiTRoot Root(BiTRoot & T)
{
	return T;
}

//获得结点
//初始条件：二叉树T已存在,e是T中的某个结点
//操作结果：返回e的值 若未找到返回NOTFOUND
ElemType Value(BiTRoot & T, int &key)
{
	assert(T != NULL);
	if (T->value == DEFAULTVALUE)
	{
		printf("二叉树为空\n");
		return T->value;
	}
	if (T->key == key)
	{
		if (T->value == DEFAULTVALUE)
		{
			printf("为默认值\n");
		}
		return T->value;
	}
	if (T->lchild != NULL)
	{
		ElemType ans=Value(T->lchild, key);  //访问左子节点
		if (ans != NOTFOUND)
		{
			return ans;
		}
	}
	if (T->rchild != NULL)
	{
		ElemType ans=Value(T->rchild, key);  //访问左子节点
		if (ans != NOTFOUND)
		{
			return ans;
		}
	}
	return NOTFOUND;
}

//结点赋值
//初始条件：二叉树T已存在,e是T中的某个结点
//操作结果：结点e赋值为value
status Assign(BiTRoot & T, int &key, ElemType value)
{
	pBiTNode cNode = GetNodeByKey(T, key);
	if (cNode == NULL)
	{
		printf("未获取到当前节点");
		return ERROR;
	}
	cNode->value = value;
	return OK;
}

//初始条件：二叉树T已存在，e是T中的某个结点
//操作结果：若e是T的非根结点，则返回它的双亲结点指针，否则返回NULL
pBiTNode Parent(BiTRoot & T, int& key)
{
	assert(T != NULL);
	pBiTNode p = Root(T);
	if (p->key == key)
	{
		return T;
	}
	int top = -1;  
	BiTRoot stack[100];
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
			if (p->lchild->key == key)break;
			stack[++top] = p->lchild;
		}
		if (p->rchild) 
		{ 
			if (p->rchild->key == key) break;
			stack[++top] = p->rchild; 
		}  
	}  
	if (top == -1)//栈空结束
	{
		if (p->lchild != NULL || p->rchild != NULL)
		{
			if (p->lchild->key == key || p->rchild->key == key)
			{
				return p;
			}
		}
		return	NULL;
	}
	if (top < -1)
	{
		return NULL;
	}
	//if (p == T)
	//{
	//	return NULL;
	//}
	return p;
}

//初始条件：二叉树T存在，e是T中某个节点
//操作结果：返回e的左孩子结点指针。若e无左孩子，则返回NULL
pBiTNode LeftChild(BiTRoot & T, int &key)
{
	pBiTNode vNode = GetNodeByKey(T, key);
	if (vNode == NULL)
	{
		return T;
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

//初始条件：二叉树T存在，e是T中某个节点
//操作结果：返回e的右孩子结点指针。若e无右孩子，则返回NULL
pBiTNode RightChild(BiTRoot & T, int& key)
{
	pBiTNode vNode = GetNodeByKey(T, key);
	if (vNode == NULL)
	{
		return T;
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

//初始条件：二叉树T存在，e是T中某个结点
//操作结果：返回e的左兄弟结点指针。若e是T的左孩子或者无左兄弟，则返回NULL
pBiTNode LeftSibling(BiTRoot & T, int & key)
{
	pBiTNode pNode=Parent(T, key);
	pBiTNode lNode = pNode->lchild;
	if (lNode == NULL||lNode==T)
	{
		//printf("无左兄弟\n");
		return NULL;
	}
	if (T->key == key)
	{
		printf("当前节点为根节点\n");
		return NULL;
	}
	if (pNode->lchild->key == key)
	{
		printf("当前节点为父节点左孩子\n");
		return T;
	}
	return lNode;
}

//初始条件：二叉树T已存在，e是T中某个结点
//操作结果：返回e的右兄弟结点指针。若e是T的右孩子或者无有兄弟，则返回NULL
pBiTNode RightSibling(BiTRoot & T, int &key)
{
	pBiTNode pNode = Parent(T, key);
	pBiTNode rNode = pNode->rchild;
	if (rNode == NULL||rNode==T)
	{
		//printf("无右兄弟\n");
		return T;
	}
	if (T->key == key)
	{
		printf("当前节点为根节点\n");
		return NULL;
	}
	if (pNode->rchild->key == key)
	{
		printf("当前节点为父节点右孩子");
		return NULL;
	}
	return rNode;
}

//初始条件:二叉树T存在，p指向T中的某个结点，LR为0或1，,非空二叉树c与T不相交且右子树为空
//传入参数：
//T:树根
//p:插入子树的节点
//LR:左右
//c:插入子树(右子树为空)
//操作结果:根据LR为0或者1，插入c为T中p所指结点的左或右子树，p	所指结点的原有左子树或右子树则为c的右子树
status InsertChild(BiTRoot & T, pBiTNode &p, LR lr, pBiTNode & c)
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
			pBiTNode pL = p->lchild;
			p->lchild = c;
			c->rchild = pL;
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
			pBiTNode pL = p->rchild;
			p->rchild = c;
			c->rchild = pL;
			return true;
		}
	}
	return false;
}

//初始条件：二叉树T存在，p指向T中的某个结点，LR为0或1
//操作结果：根据LR为0或者1，删除c为T中p所指结点的左或右子树
status DeleteChild(BiTRoot & T, pBiTNode & p, LR lr)
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
			int s=DestroyBiTree(p->lchild);
			p->lchild = NULL;
			return s;
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
			int s = DestroyBiTree(p->rchild);
			p->rchild = NULL;
			return s;
		}
	}
	return false;
}

//初始条件：二叉树T存在，Visit是对结点操作的应用函数
//操作结果：先序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败
status PreOrderTraverse(BiTRoot & T, void(*visit)(pBiTNode N))
{
	assert(T != NULL);
	if (T->value == DEFAULTVALUE)
	{
		return EMPTYTREE;
	}
	visit(T);								 //访问根节点
	if (T->lchild != NULL)
	{
		PreOrderTraverse(T->lchild, visit);  //访问左子节点
	}
	if (T->rchild != NULL)
	{
		PreOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	return OK;
}

//初始条件：二叉树T存在
//操作结果：中序遍历T，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败
status InOrderTraverse(BiTRoot & T, void(*visit)(pBiTNode N))
{
	assert(T != NULL);
	if (T->value == DEFAULTVALUE)
	{
		return EMPTYTREE;
	}	
	if (T->lchild!= NULL)
	{
		InOrderTraverse(T->lchild, visit);  //访问左子节点
	}
	visit(T);								 //访问根节点
	if (T->rchild!= NULL)
	{
		InOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	return true;
}

//初始条件：二叉树T存在
//操作结果：后序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
status PostOrderTraverse(BiTRoot & T, void(*visit)(pBiTNode N))
{
	assert(T != NULL);
	if (T->value == DEFAULTVALUE)
	{
		return EMPTYTREE;
	}
	if (T->lchild != NULL)
	{
		PostOrderTraverse(T->lchild, visit);  //访问左子节点
	}	
	if (T->rchild != NULL)
	{
		PostOrderTraverse(T->rchild, visit);  //访问左子节点
	}
	visit(T);								 //访问根节点
	return true;
}

//初始条件：二叉树T存在
//操作结果：层序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
status LevelOrderTraverse(BiTRoot & T, void(*visit)(pBiTNode N))
{
	assert(T != NULL);
	if (T->value == DEFAULTVALUE)
	{
		return EMPTYTREE;
	}
	pBiTNode NodeQueue[100];
	int frontIndex = 0;		//头部  头部弹出
	int rearIndex = 0;		//尾部	尾部插入
	NodeQueue[rearIndex++] = T;
	while (frontIndex != rearIndex)
	{
		pBiTNode vNode = NodeQueue[frontIndex];
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

//初始条件：二叉树T存在
//操作结果：把二叉树保存到文件中
status SaveToFile(char * filename, pBiTNode& T)
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件写入错误\n ");
		return ERROR;
	}
	pBiTNode stack[100],p;
	pBiTNode pop;
	char str[100];
	int strIndex=0;
	int top = -1;
	p = T;
	while (top > -1 || p != NULL)
	{
		while (p->lchild != NULL)
		{
			str[strIndex++] = p->value;
			stack[++top] = p;
			p = p->lchild;
		}
		assert(p->lchild == NULL);
		str[strIndex++] = p->value;		//p值
		str[strIndex++] = DEFAULTVALUE; //左孩子值
		p = p->rchild;
		while (p == NULL)
		{
			str[strIndex++] =DEFAULTVALUE;		
			//str[strIndex++] = pop->value;
			if (top > -1)
			{
				pop = stack[top--];
				p = pop->rchild;
			}
			else
			{
				break;
			}
			
		}
	}
	str[strIndex++] = '\0';
	printf("%s", str);
	fprintf(fp, "%s", str);
	fclose(fp);
	return OK;
}

//读取文件
//操作结果：将文件内容载入二叉树
status LoadFromFile(char * filename, pBiTNode& L)
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件打开失败\n ");
		return ERROR;
	}
	int index = 0;
	char str[100];
	fgets(str, 100, fp);
	printf("%s", str);
	int s=CreateBiTreeByDLR(L, str, index);
	return s;
}

//树形打印二叉树
#pragma region PrintTree
//参数:
//root:根结点
//root_x:根结点的水平位置
//root_y:根结点的竖直位置
//r_c_interval:当前根结点与其左右儿子的水平间距
//disp_buf:用于暂存打印内容的缓存区
void PrintTree(BiTree &root, int root_x, int root_y, int r_c_interval, char disp_buf[][MAXBUFCOL])
{
	beforePrint();
	printTreeToBuffer(root,root_x,root_y,r_c_interval,disp_buf);
	afterPrint();
	printToScreen();
}

void beforePrint()
{
	for (int i = 0; i<MAXBUFROW; ++i)
	{
		for (int j = 0; j<MAXBUFCOL; ++j)
		{
			dispbuf[i][j] = ' ';
		}
	}
}
//参数从左至右依次为：根结点、根结点的水平位置、根结点的竖直位置、当前根结点与其左右儿子的水平间距、用于暂存打印内容的缓存
void printTreeToBuffer(BiTree &root, int root_x, int root_y, int r_c_interval, char disp_buf[][MAXBUFCOL])
{
	int left_child, right_child;

	left_child = root_x - r_c_interval;//左右节点的水平位置
	right_child = root_x + r_c_interval;

	if (root == NULL) return;     //递归出口  
	else
	{ 
		disp_buf[root_y][root_x - 1] = root->value;//打印根结点 		
		if (root->lchild != NULL)    disp_buf[root_y + 1][root_x - 2] = '/';//左子树非空，打印左连接符  	
		if (root->rchild != NULL) disp_buf[root_y + 1][root_x] = '\\';//右子树非空，打印右连接符  
		printTreeToBuffer(root->lchild, left_child, root_y + 2, (r_c_interval >> 1), disp_buf);//递归打印左子树。注意左子树根结点的位置，以及左子树根结点与其儿子的水平距离  
		printTreeToBuffer(root->rchild, right_child, root_y + 2, (r_c_interval >> 1), disp_buf);//递归打印右子树  
	}
}

int afterPrint()
{
	int effectiveLine = 0;
	for (int i = 0; i<MAXBUFROW; ++i)
	{
		int j = MAXBUFCOL - 1;
		while (dispbuf[i][j] == ' ' && j >= 0) --j;
		if (j>-1)
		{
			dispbuf[i][j + 1] = '('; //随便赋一个值作为终止标记  
			++effectiveLine;
			continue;
		}
		else
			break;
	}
	return effectiveLine;
}
//输出缓冲区到屏幕
void printToScreen()
{
	int effectiveLine = afterPrint();
	for (int i = 0; i<effectiveLine; ++i)
	{
		for (int j = 0; j<MAXBUFCOL; ++j)
		{
			if (dispbuf[i][j] != '(')
			{
				printf("%c", dispbuf[i][j]);
			}
			else break;
		}
		printf("\n");
	}
}
#pragma endregion


