/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: list.h			 
* Description : 链表操作宏定义、分页操作 
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日		 
*/

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>

/*初始化链表list。链表为带头结点的双向循环链表*/
#define List_Init(list, list_node_t) {					\
		list=(list_node_t*)malloc(sizeof(list_node_t)); \
		(list)->next=(list)->prev=list;					\
	}

//释放链表list中所有数据结点。list 为链表头指针，list_node_t为链表结点类型
#define List_Free(list, list_node_t) {			\
		assert(NULL!=list);						\
		list_node_t *tmpPtr;					\
		(list)->prev->next=NULL; 				\
		while(NULL!=(tmpPtr=(list)->next)){ 	\
			(list)->next=tmpPtr->next;			\
			free(tmpPtr);						\
		}										\
		(list)->next=(list)->prev=list;			\
	}

//销毁链表list，释放所有数据结点及头结点。 list为链表头指针，tmpPtr为链表结点临时指针变量
#define List_Destroy(list, list_node_t) {		\
		assert(NULL!=list);						\
		List_Free(list, list_node_t)			\
		free(list);								\
		(list)=NULL;							\
	}

//链表头插法，list为头指针，new为新节点
#define List_AddHead(list, newNode) {			\
		(newNode)->next=(list)->next;		 	\
		(list)->next->prev=newNode;			 	\
		(newNode)->prev=(list);				 	\
		(list)->next=newNode;				 	\
	}

//链表尾插法，list为头指针，new为新节点
#define List_AddTail(list, newNode) {			\
		(newNode)->prev=(list)->prev; 		 	\
		(list)->prev->next=newNode;			 	\
		(newNode)->next=list;				 	\
		(list)->prev=newNode;				 	\
	}

//将新节点newNode加入到node之前
#define List_InsertBefore(node, newNode) {		\
		(newNode)->prev=(node)->prev; 		 	\
		(newNode)->next=node;			 		\
		(newNode)->prev->next=newNode;			\
		(newNode)->next->prev=newNode;			\
	}

//将新节点newNode加入到node之后
#define List_InsertAfter(node, newNode) {		\
		(newNode)->next=node->next;			 	\
		(newNode)->prev=node; 				 	\
		(newNode)->next->prev=newNode;			\
		(newNode)->prev->next=newNode;			\
	}

//判断链表是否为空，list