#ifndef _INDEXBOOK_H_
#define _INDEXBOOK_H_

#include "BinarySearchTree.h"
#include "Index.h"
#include "Businesscardbook.h"


typedef struct _indexBook{
	BinaryTree indexs;
	Long length;
}IndexBook;

void IndexBook_Create(IndexBook *indexBook);
Index* Add(IndexBook *indexBook, BusinessCard *businessCard);
Index* IndexBook_Find(IndexBook *indexBook, char(*companyName));
Index* Remove(IndexBook *indexBook, BusinessCard *businessCard, char(*companyName));
void IndexBook_Arrange(IndexBook *indexBook);
void MakeList(IndexBook *indexBook, Index* (*indexes), Long *count);
void IndexBook_Destroy(IndexBook *indexBook);
int CompareIndex(void *one, void *other);
void IndexBook_Node(BinaryNode *binaryNode);

#endif