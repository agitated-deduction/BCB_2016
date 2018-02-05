#ifndef _binaryTree_H_
#define _binaryTree_H_
#include <stddef.h>
typedef signed long int Long;
typedef	struct _binaryNode BinaryNode;
typedef	struct _binaryNode
{
	BinaryNode *left;
	BinaryNode *right;
}BinaryNode;

typedef struct _binaryTree{
	BinaryNode *root;
	Long length;
	Long balance;
}BinaryTree;

void BinaryTree_Create(BinaryTree *binaryTree);
BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*));
BinaryNode* Search(BinaryTree *binaryTree, void *key, int (*compare)(void*, void*));
BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*));
void MakeBalance(BinaryTree *binaryTree, size_t size);
void CopyToBuffer(BinaryTree *binaryTree, void*(*keys), Long *count, size_t size);
void Node_CopyToBuffer(BinaryNode *binaryNode, void(*keys), Long *count, size_t size);
void BinaryTree_DeleteAllItems(BinaryTree *binaryTree);
void Node_DeleteAllItems(BinaryNode *binaryNode);
void MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size);
BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size);
void BinaryTree_Destroy(BinaryTree *binaryTree);
void Node_Destroy(BinaryNode *binaryNode);
void BinaryTree_GetAt(BinaryNode *index, void *object, size_t size);

#endif