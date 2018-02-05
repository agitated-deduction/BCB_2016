#include "Index.h"

void Index_Create(Index *index, Long capacity){
	Array_Create(&index->businessCards, capacity, sizeof(BusinessCard*));
	index->capacity = capacity;
	index->length = 0;
}

Long Increase(Index *index, BusinessCard *businessCard){
	Long arrayIndex;
	if (index->length < index->capacity){
		arrayIndex=Store(&index->businessCards, index->length, &businessCard, sizeof(BusinessCard*));
	}
	else{
		arrayIndex=AppendFromRear(&index->businessCards, &businessCard, sizeof(BusinessCard*));
		index->capacity++;
	}
	index->length++;
	return arrayIndex;
}

Long Index_Find(Index *index, BusinessCard *businessCard){
	Long arrayIndex;
	arrayIndex = Array_LinearSearchUnique(&index->businessCards, businessCard, sizeof(BusinessCard*), CompareCards);
	
	return arrayIndex;
}

Long Reduce(Index *index, Long arrayIndex){
	Long ret;
	ret=Array_Delete(&index->businessCards, arrayIndex, sizeof(BusinessCard*));
	index->length--;
	index->capacity--;
	return ret;
}

BusinessCard* Index_GetAt(Index *index, Long arrayIndex){
	BusinessCard *businessCard;
	Array_GetAt(&index->businessCards, arrayIndex, &businessCard, sizeof(BusinessCard*));
	return businessCard;
}

void Index_Destroy(Index *index){
	Array_Destroy(&index->businessCards);
}

int CompareCards(void *one, void *other){
	int ret;
	BusinessCard* oneCard = (BusinessCard*)one;
	BusinessCard* otherCard = (BusinessCard*)other;
	if (oneCard > otherCard){
		ret = 1;
	}
	else if (oneCard == otherCard){
		ret = 0;
	}
	else if (oneCard < otherCard){
		ret = -1;
	}
	return ret;
}
