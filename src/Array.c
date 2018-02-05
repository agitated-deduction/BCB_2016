#include "Array.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

void Array_Create(Array *arr, Long capacity, size_t size){
	arr->front = calloc(capacity, size);
	arr->capacity = capacity;
	arr->length = 0;
}

Long Store(Array *arr, Long index, void *object, size_t size){
	memcpy(((char*)arr->front) + (index*size), object, size);
	(arr->length)++;
	return index;
}

Long Array_Insert(Array *arr, Long index, void *object, size_t size){
	void(*temp);
	Long i = 0;
	temp = calloc(arr->capacity + 1, size);
	while (i < index){
		memcpy(((char*)temp) + (i*size), ((char*)arr->front) + (i*size), size);
		i++;
	}
	while (i < arr->length){
		memcpy(((char*)temp) + ((i + 1)*size), ((char*)arr->front) + (i*size), size);
		i++;
	}
	if (arr->front != NULL){
		free(arr->front);
		arr->front = NULL;
	}

	arr->front = temp;
	arr->capacity++;
	memcpy(((char*)arr->front) + index*size, object, size);
	arr->length++;
	return index;
}

Long AppendFromFront(Array *arr, void *object, size_t size){
	Long index = 0;
	void(*temp);
	Long i = 0;
	temp = calloc(arr->capacity + 1, size);
	while (i < arr->length){
		memcpy(((char*)temp) + ((i + 1)*size), ((char*)arr->front) + (i*size), size);
		i++;
	}
	if (arr->front != NULL){
		free(arr->front);
		arr->front = NULL;
	}
	arr->front = temp;
	arr->capacity++;
	memcpy(((char*)arr->front) + (index*size), object, size);
	arr->length++;
	return index;
}

Long AppendFromRear(Array *arr, void *object, size_t size){
	Long index;
	Long i = 0;
	void(*temp);
	temp = calloc(arr->capacity + 1, size);
	while (i < arr->length){
		memcpy(((char*)temp) + (i*size), ((char*)arr->front) + (i*size), size);
		i++;
	}
	if (arr->front != NULL){
		free(arr->front);
	}
	
	arr->front = temp;
	arr->capacity++;
	memcpy(((char*)arr->front) + (arr->capacity-1)*size, object, size);
	arr->length++;
	index = arr->capacity;
	return index;
}

Long Array_Delete(Array *arr, Long index, size_t size){
	Long i = 0;
	Long j;
	void(*temp);

	if (arr->capacity > 1){
		temp = calloc(arr->capacity - 1, size);
	}
	while (i < index){
		memcpy(((char*)temp) + (i*size), ((char*)arr->front) + (i*size), size);
		i++;
	}
	j = index + 1;
	while (j < arr->length){
		memcpy(((char*)temp) + (i*size), ((char*)arr->front) + (j*size), size);
		i++;
		j++;
	}
	free(arr->front);
	if (arr->capacity>1){
		arr->front = temp;
	}
	arr->capacity--;
	arr->length--;
	index = -1;
	return index;
}

Long DeleteFromFront(Array *arr, size_t size){
	Long index;
	void(*temp);
	Long i = 1;

	if (arr->capacity > 1){
		temp = calloc(arr->capacity - 1, size);
	}
	while (i < arr->length){
		memcpy(((char*)temp) + (i - 1)*size, ((char*)arr->front) + (i*size), size);
		i++;
	}
	free(arr->front);
	if (arr->capacity>1){
		arr->front = temp;
	}
	arr->capacity--;
	arr->length--;
	index = -1;
	return index;
}

Long DeleteFormRear(Array *arr, size_t size){
	Long index;
	void(*temp);
	Long i = 0;
	Long j;

	if (arr->capacity > 1){
		temp = calloc(arr->capacity - 1, size);
	}
	while (i < arr->capacity - 1){
		memcpy(((char*)temp) + i*size, ((char*)arr->front) + i*size, size);
		i++;
	}
	free(arr->front);
	if (arr->capacity>1){
		arr->front = temp;
	}
	arr->length--;
	arr->capacity--;
	index = -1;
	return index;
}

void Clear(Array *arr){
	if (arr->front != NULL){
		free(arr->front);
		arr->front = NULL;
	}
	arr->capacity = 0;
	arr->length = 0;
}

Long Modify(Array *arr, Long index, void *object, size_t size){
	memcpy(object, ((char*)arr->front) + index*size, size);
	return index;
}

Long Array_LinearSearchUnique(Array *arr, void *key, size_t size, int(*compare)(void*, void*)){
	Long i = 0;
	Long index = -1;
	while (i < arr->length && compare((char*)arr->front + i*size, key)){
		i++;
	}
	if (i < arr->length){
		index = i;
	}
	return index;
}

void Array_LinearSearchDuplicate(Array *arr, void *key, size_t size, Long*(*indexes), Long *count, int(*compare)(void*, void*)){
	Long i = 0, j = 0;
	*count = 0;
	*indexes = (Long(*))calloc(arr->length, sizeof(Long));
	while (i<arr->length)
	{
		if (compare(((char*)arr->front) + i*size, key) == 0){
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}

Long BinarySearchUnique(Array *arr, void *key, size_t size, int(*compare)(void*, void*)){
	Long index = -1;
	Long first = 0;
	Long last, mid;
	last = arr->length - 1;
	mid = (first + last) / 2;
	while (first <= last && (compare((char*)arr->front + mid*size, key) != 0)){
		if (compare(((char*)arr->front) + mid*size, key) < 0){
			first = mid + 1;
		}
		else{
			last = mid - 1;
		}
		mid = (first + last) / 2;
	}
	if (first <= last){
		index = mid;
	}
	return index;
}

void BinarySearchDuplicate(Array *arr, void *key, size_t size, Long*(*indexes), Long *count, int(*compare)(void*, void*)){
	Long first = 0;
	Long last, mid;
	Long i = 0, j = 0;
	*indexes = (Long(*))calloc(arr->length, size);
	last = arr->length - 1;
	mid = (first + last) / 2;
	while (first <= last && (compare((char*)arr->front + mid*size, key)) != 0){
		if (compare(((char*)arr->front) + mid*size, key) < 0){
			first = mid + 1;
		}
		else{
			last = mid - 1;
		}
		mid = (first + last) / 2;
	}
	mid--;
	while (mid >=0 && (compare((char*)arr->front + mid*size, key)) == 0){
		mid--;
	}
	mid++;
	while (mid < arr->length && (compare((char*)arr->front + mid*size, key)) == 0){
		(*indexes)[j] = mid;
		(*count)++;
		j++;
		mid++;
	}
}

void BubbleSort(Array *arr, size_t size, int(*compare)(void*, void*)){
	Long i = 0,j;
	void *temp;
	temp = malloc(size); 
	while (i < arr->length-1){
		j = 0;
		while (j < arr->length - i-1){
			if (compare(((char*)arr->front) + j*size, ((char*)arr->front) + (j + 1)*size)>0){
				memcpy(temp, ((char*)arr->front) +( j*size), size);
				memcpy((char*)arr->front + j*size, (char*)arr->front + (j+1)*size, size);
				memcpy(((char*)arr->front) + (j + 1)*size, temp, size);
			}
			j++;
		}
		i++;
	}
}

void SelectionSort(Array *arr, size_t size, int(*compare)(void*, void*)){
	Long i = 0, j, min;
	void *temp;
	temp = malloc(size);
	while (i < arr->length){
		min = i;
		j = i + 1;
		while (j < arr->length){
			if (compare(((char*)arr->front) + min*size,((char*)arr->front) + j*size)>0){
				min = j;
			}
			j++;
		}
		memcpy(temp, (char*)arr->front + i*size, size);
		memcpy((char*)arr->front + i*size, (char*)arr->front + min*size, size);
		memcpy((char*)arr->front + min*size, temp, size);
		i++;
	}
}

void InsertionSort(Array *arr, size_t size, int(*compare)(void*, void*)){
	void *position;
	Long i = 1;
	Long j;
	Long index;

	position = malloc(size);
	while (i < arr->length)
	{
		memcpy(position, ((char*)arr->front) + (i*size), size);
		j = i-1;
		while (j >= 0 && compare(position, ((char*)arr->front) + (j*size)) <0)
		{
			memcpy(((char*)arr->front) + ((j+1)*size), ((char*)arr->front) + j*size, size);
			j--;

		}
		index = j+1;
		memcpy(((char*)arr->front) + (index*size), position, size);
		i++;
	}
}

void MergeSort(Array *arr, Array *one ,Array *other, size_t size, int(*compare)(void*, void*)){
	Long i = 0;
	Long j = 0;
	Long k = 0;
	Long max;

	max = (one->length) + (other->length);

	free(arr->front);
	arr->front = calloc(max, size);
	arr->capacity = max;
	while (i < one->length && j < other->length) 
	{
		if (compare(((char*)one->front) + (i*size), ((char*)other->front) + (j*size)) <0)
		{
			memcpy(((char*)arr->front) + (k*size), ((char*)one->front) + (i*size), size);
			k++;
			i++;
		}
		else
		{
			memcpy(((char*)arr->front) + (k*size), ((char*)other->front) + (j*size), size);
			k++;
			j++;
		}
	}
	while (j < other->length)
	{
		memcpy(((char*)arr->front) + (k*size), ((char*)other->front) + (j*size), size);
		k++;
		j++;
	}

	while (i < one->length)
	{
		memcpy(((char*)arr->front) + (k*size), ((char*)one->front) + (i*size), size);
		k++;
		i++;
	}
	arr->length = max;

}

void Array_Destroy(Array *arr){
	if (arr->front != NULL){
		free(arr->front);
	}

}

void Array_GetAt(Array *arr, Long index, void *object, size_t size){
	memcpy(object, ((char*)arr->front) + (index*size), size);
}