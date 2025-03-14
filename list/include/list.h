#ifndef _HLIST
#define _HLIST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int elem_t;
#define ELEM_SPECIFIER "%d"

const int POISON = 0x1ABA;
const size_t LIST_DATA_SIZE = 4096;

typedef struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    elem_t value = 0;
} Node;

typedef struct List
{
    Node *head = nullptr;
    Node *tail = nullptr;
    int size = 0;
    int error_code;
} List;

enum ListErrors
{
    OK = 0,
    LIST_STRUCT_NULLPTR = 1,
    ERROR_NODE_ALLOCATION = 3,
    NODE_NULLPTR = 4,
    INVALID_POSITION = 5,
    LIST_EMPTY = 6
};

typedef struct ServiceLines {
    char list_data[LIST_DATA_SIZE] = "";
} ServiceLines;

ServiceLines* GetServiceLines();

ListErrors ListRemove(List *lst, Node *remove_node);
Node* ListFind(List *lst, elem_t value);
Node* ListGetFirst(List* lst);
Node* ListGetLast(List* lst);
Node* ListGetNext(Node* current);
Node* ListGetPrev(Node* current);
ListErrors ListInsertFirst(List *lst, elem_t value);
ListErrors ListInsertLast(List *lst, elem_t value);
ListErrors ListInsert(List *lst, elem_t value, size_t position);
void ListFree(List *lst);
List *ListInit();
void ListPrint(List *lst);
void GetListData(List *lst);
void RemoveSingleNode(List *lst, Node *remove_node);
void RemoveEnd(List *lst, Node *remove_node);
void RemoveBegin(List *lst, Node *remove_node);
void RemoveNode(List *lst, Node *remove_node);
int ListDumpDot (List *lst);
ListErrors ListReverse(List *lst);
bool ListHasCycle(List *lst);

#endif //_HLIST
