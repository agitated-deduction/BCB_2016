#ifndef _INDEX_H_
#define _INDEX_H_

#include "Array.h"
#include "Businesscardbook.h"
typedef signed long int Long;

typedef struct _index{
	char name[32];
	Array businessCards;
	Long capacity;
	Long length;
}Index;

void Index_Create(Index *index, Long capacity);
Long Increase(Index *index, BusinessCard *businessCard);
Long Index_Find(Index *index, BusinessCard *businessCard);
Long Reduce(Index *index, Long arrayIndex);
BusinessCard* Index_GetAt(Index *index, Long arrayIndex);
void Index_Destroy(Index *index);
int CompareCards(void *one, void *other);


#endif