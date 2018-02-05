#include "IndexBook.h"
#include <string.h>

void IndexBook_Create(IndexBook *indexBook){
	BinaryTree_Create(&indexBook->indexs);
	indexBook->length = 0;
}

Index* Add(IndexBook *indexBook, BusinessCard *businessCard){
	Index temp;
	Index *index;
	BinaryNode *node;

	strcpy(temp.name, businessCard->company.name);
	node = Search(&indexBook->indexs, &temp, CompareIndex);
	if (node == NULL){
		Index_Create(&temp, 3);
		node = BinaryTree_Insert(&indexBook->indexs, &temp, sizeof(Index), CompareIndex);
		indexBook->length++;
	}
	index = (Index*)(node + 1);
	Increase(index, businessCard);

	return index;
}

Index* IndexBook_Find(IndexBook *indexBook, char(*companyName)){
	Index temp;
	Index *index = NULL;
	BinaryNode *node;
	strcpy(temp.name, companyName);
	node = Search(&indexBook->indexs, &temp, CompareIndex);
	if (node != NULL){
		index = (Index*)(node + 1);
	}
	return index;
}

Index* Remove(IndexBook *indexBook, BusinessCard *businessCard, char(*companyName)){
	Index temp;
	Index *index;
	Long arrayIndex;
	BinaryNode *node;
	strcpy(temp.name, companyName);
	node = Search(&indexBook->indexs, &temp, CompareIndex);
	index = (Index*)(node + 1);
	arrayIndex=Index_Find(node + 1, businessCard);
	Reduce(node + 1, arrayIndex);
	index = (Index*)(node + 1);
	if (index->length == 0){
		node = BinaryTree_Delete(&indexBook->indexs, index, CompareIndex);
		index = NULL;
		indexBook->length--;
	}
	return index;
}

void IndexBook_Arrange(IndexBook *indexBook){
	MakeBalance(&indexBook->indexs, sizeof(Index));
}

void MakeList(IndexBook *indexBook, Index* (*indexes), Long *count){
	CopyToBuffer(&indexBook->indexs, indexes, count, sizeof(Index));
}

void IndexBook_Destroy(IndexBook *indexBook){
	IndexBook_Node(indexBook->indexs.root);
	BinaryTree_Destroy(&indexBook->indexs);
}

int CompareIndex(void *one, void *other){
	int ret;
	Index *oneIndex = (Index*)one;
	Index *otherIndex = (Index*)other;

	return strcmp(oneIndex->name, otherIndex->name);
}

void IndexBook_Node(BinaryNode *binaryNode){
	if (binaryNode != NULL){
		IndexBook_Node(binaryNode->left);
		IndexBook_Node(binaryNode->right);
		Index_Destroy((Index*)(binaryNode + 1));
	}
}