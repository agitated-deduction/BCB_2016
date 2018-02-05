#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void Create(LinkedList *linkedList){
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

Node* InsertBefore(LinkedList* linkedList, Node* index, void* object, size_t size){
	linkedList->current = (Node*)malloc(sizeof(Node)+size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = index;

	if (linkedList->head != index){
		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}

	index->previous = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node* InsertAfter(LinkedList* linkedList, Node* index, void* object, size_t size){
	linkedList->current = (Node*)malloc(sizeof(Node)+size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = index;
	if (linkedList->tail != index){
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node* AppendFromHead(LinkedList* linkedList, void* object, size_t size){
	linkedList->current = (Node*)malloc(sizeof(Node)+size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = linkedList->current;
	if (linkedList->head != NULL){
		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node* AppendFromTail(LinkedList* linkedList, void* object, size_t size){
	linkedList->current = (Node*)malloc(sizeof(Node)+size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = linkedList->current;
	if (linkedList->tail != NULL){
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node* Delete(LinkedList* linkedList,Node* index){
	index->previous->next = index->next;
	index->next->previous = index->previous;
	linkedList->current = index->next;
	if (linkedList->head == index){
		linkedList->head = index->next;
		index->next->previous = index->next;
	}
	if (linkedList->tail == index){
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
		index->previous->next = index->previous;
	}
	if (linkedList->head == index&&linkedList->tail == index){
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL){
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

Node* DeleteFromHead(LinkedList* linkedList){
	Node* index;

	index = linkedList->head;
	if (linkedList->tail != index){
		index->next->previous = index->next;
		linkedList->current = index->next;
		linkedList->head = index->next;
	}
	else{
		linkedList->head = NULL;
		linkedList->current = NULL;
		linkedList->tail = NULL;
	}
	if (index != NULL){
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

Node* DeleteFromTail(LinkedList* linkedList){
	Node* index;

	index = linkedList->tail;
	if (linkedList->head != index){
		index->previous->next = index->previous;
		linkedList->current = index->previous;
		linkedList->tail = index->previous;
	}
	else{
		linkedList->head = NULL;
		linkedList->current = NULL;
		linkedList->tail = NULL;
	}
	if (index != NULL){
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

void Link_DeleteAllItems(LinkedList* linkedList){
	Node* previous = NULL;

	linkedList->current = linkedList->head;
	while (previous != linkedList->current){
		linkedList->head = linkedList->head->next;
		previous = linkedList->current;
		linkedList->current = NULL;
		linkedList->current = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

Node* LinearSarchUnique(LinkedList* linkedList, void* key, int(*compare)(void*, void*)){
	Node *index = NULL;
	Node *previous = NULL;

	linkedList->current = linkedList->head;
	while (linkedList->current != previous&&compare(linkedList->current + 1, key) != 0){
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
	if (linkedList->current != previous){
		index = linkedList->current;
	}
	return index;
}

void LinearSarchDuplicate(LinkedList* linkedList, void* key, Node** (*indexes), Long *count, int(*compare)(void*, void*)){
	Long i = 0;
	Node *previous = NULL;

	*count = 0;
	
	*indexes = (Node*(*))calloc(linkedList->length, sizeof(Node*));
	linkedList->current = linkedList->head;
	while (previous != linkedList->current){
		if (compare(linkedList->current + 1, key) == 0){
			(*indexes)[i] = linkedList->current;
			(*count)++;
			i++;
		}
		previous = linkedList->current;
		linkedList->current = linkedList->current->next;
	}
}

Node* First(LinkedList* linkedList){
	linkedList->current = linkedList->head;

	return linkedList->current;
}

Node* Previous(LinkedList* linkedList){
	linkedList->current = linkedList->current->previous;

	return linkedList->current;
}

Node* Next(LinkedList* linkedList){
	linkedList->current = linkedList->current->next;

	return linkedList->current;
}

Node* Last(LinkedList* linkedList){
	linkedList->current = linkedList->tail;

	return linkedList->current;
}

void Destroy(LinkedList* linkedList){
	Node* previous = NULL;

	linkedList->current = linkedList->head;
	while (previous != linkedList->current){
		linkedList->head = linkedList->head->next;
		previous = linkedList->current;
		linkedList->current = NULL;
		linkedList->current = linkedList->head;
	}
}

void GetAt(LinkedList* linkedList, Node* index, void* object, size_t size){
	linkedList->current = index;
	memcpy(object, linkedList->current + 1, size);
}