#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include <memory.h>

typedef signed long int Long;
typedef struct _node Node;
typedef struct _node{
	Node *previous;
	Node *next;
}Node;


typedef struct _linkedList
{
	Node *head;
	Node *tail;
	Long length;
	Node *current;
}LinkedList;

void Create(LinkedList *linkedList);
Node* InsertBefore(LinkedList* linkedList, Node* index, void* object, size_t size);
Node* InsertAfter(LinkedList* linkedList, Node* index, void* object, size_t size);
Node* AppendFromHead(LinkedList* linkedList, void* object, size_t size);
Node* AppendFromTail(LinkedList* linkedList, void* object, size_t size);
Node* Delete(LinkedList* linkedList, Node* index);
Node* DeleteFromHead(LinkedList* linkedList);
Node* DeleteFromTail(LinkedList* linkedList);
void Link_DeleteAllItems(LinkedList* linkedList);
Node* LinearSarchUnique(LinkedList* linkedList, void* key, int(*compare)(void*, void*));
void LinearSarchDuplicate(LinkedList* linkedList, void* key, Node* (*indexes), Long *count, int(*compare)(void*, void*));
Node* First(LinkedList* linkedList);
Node* Previous(LinkedList* linkedList);
Node* Next(LinkedList* linkedList);
Node* Last(LinkedList* linkedList);
void Destroy(LinkedList* linkedList);
void GetAt(LinkedList* linkedList, Node* index, void* object, size_t size);
#endif