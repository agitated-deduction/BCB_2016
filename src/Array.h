#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stddef.h>
typedef signed long int Long;

typedef struct _array{
	void *front;
	Long capacity;
	Long length;
}Array;

void Array_Create(Array *arr, Long capacity, size_t size);
Long Store(Array *arr, Long index, void *object, size_t size);
Long Array_Insert(Array *arr, Long index, void *object, size_t size);
Long AppendFromFront(Array *arr, void *object, size_t size);
Long AppendFromRear(Array *arr, void *object,size_t size);
Long Array_Delete(Array *arr, Long index, size_t size);
Long DeleteFromFront(Array *arr,size_t size);
Long DeleteFormRear(Array *arr,size_t size);
void Clear(Array *arr);
Long Modify(Array *arr,Long index,void *object,size_t size);
Long Array_LinearSearchUnique(Array *arr, void *key, size_t size, int(*compare)(void*, void*));
void Array_LinearSearchDuplicate(Array *arr, void *key, size_t size, Long*(*indexes), Long *count, int(*compare)(void*, void*));
Long BinarySearchUnique(Array *arr,void *key,size_t size,int (*compare)(void*,void*));
void BinarySearchDuplicate(Array *arr, void *key, size_t size, Long*(*indexes), Long *count, int(*compare)(void*, void*));
void BubbleSort(Array *arr,size_t size,int (*compare)(void*,void*));
void SelectionSort(Array *arr,size_t size,int (*compare)(void*,void*));
void InsertionSort(Array *arr,size_t size,int (*compare)(void*,void*));
void MergeSort(Array *arr,size_t size,int(*compare)(void*,void*));
void Array_Destroy(Array *arr);
void Array_GetAt(Array *arr, Long index, void *object, size_t size);
#endif