#include "BinarySearchTree.h"
#include <memory.h>
#include <stdlib.h>

void BinaryTree_Create(BinaryTree *binaryTree){
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)){
	BinaryNode *node;
	BinaryNode *parent = NULL;
	BinaryNode *child;

	child = binaryTree->root;
	while (child != NULL){
		parent = child;
		if (compare(child + 1, key) > 0){
			child = child->left; 
		}
		else{
			child = child->right;
		}
	}
		node = (BinaryNode*)malloc(sizeof(BinaryNode)+size);
		memcpy(node + 1, key, size);
		node->left = NULL;
		node->right = NULL;
		if (parent != NULL){
			if (compare(parent + 1, key) > 0){
				parent->left = node;
			}
			else{
				parent->right = node;
			}
			if (compare(binaryTree->root + 1, key) > 0){
				binaryTree->balance--;
			}
			else{
				binaryTree->balance++;
			}
		}
		else{
			binaryTree->root = node;
		}
		binaryTree->length++;
		return node;
}

BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)){
	BinaryNode *index;

	index = binaryTree->root;
	while (index != NULL&&compare(index + 1, key) != 0){
		if (compare(index + 1, key) > 0){
			index = index->left;
		}
		else{
			index = index->right;
		}
	}
	return index;
}

BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)){
		BinaryNode *child;
		BinaryNode *parent = NULL;
		BinaryNode *temp = NULL;
		BinaryNode *parentTemp;
		BinaryNode *root;

		child = binaryTree->root;
		while (child != NULL && compare(child + 1, key) != 0) {
			parent = child;
			if (compare(child + 1, key) > 0) {
				child = child->left;
			}
			else {
				child = child->right;
			}
		}
		if (child->right != NULL) {
			temp = child->right;
			parentTemp = child;
			while (temp->left != NULL) {
				parentTemp = temp;
				temp = temp->left;
			}
			if (child == parentTemp) {
				parentTemp->right = temp->right;
			}
			else {
				parentTemp->left = temp->right;
			}
		}
		else if (child->left != NULL) {
			temp = child->left;
			parentTemp = child;
			while (temp->right != NULL) {
				parentTemp = temp;
				temp = temp->right;
			}
			if (child == parentTemp) {
				parentTemp->left = temp->left;
			}
			else {
				parentTemp->right = temp->left;
			}
		}
		if (temp != NULL) {
			temp->right = child->right;
			temp->left = child->left;
		}
		root = binaryTree->root;
		if (child != root) {
			if (compare(parent + 1, child + 1) > 0) {
				parent->left = temp;
			}
			else {
				parent->right = temp;
			}
			if (compare(root + 1, child + 1) < 0) {
				binaryTree->balance--;
			}
			else {
				binaryTree->balance++;
			}
		}
		else {
			binaryTree->root = temp;
			if (temp != NULL) {
				if (compare(temp + 1, root + 1) > 0) {
					binaryTree->balance--;
				}
				else {
					binaryTree->balance++;
				}
			}
		}
		free(child);
		child = NULL;
		binaryTree->length--;
		return child;
	
}

void MakeBalance(BinaryTree *binaryTree, size_t size){
	void(*keys);
	Long count;

	CopyToBuffer(binaryTree,&keys,&count,size);
	BinaryTree_DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, count, size);
}

void CopyToBuffer(BinaryTree *binaryTree, void*(*keys), Long *count, size_t size){
	*count = 0;
	*keys = calloc(binaryTree->length, size);
	Node_CopyToBuffer(binaryTree->root, *keys, count, size);
}

void Node_CopyToBuffer(BinaryNode *binaryNode, void(*keys), Long *count, size_t size){
	Long i;

	if (binaryNode != NULL){
		Node_CopyToBuffer(binaryNode->left, keys, count, size);
		i = *count;
		memcpy(((char*)(keys)) + i*size, binaryNode + 1, size);
		(*count)++;
		Node_CopyToBuffer(binaryNode->right, keys, count, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree){
	Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void Node_DeleteAllItems(BinaryNode *binaryNode){
	if (binaryNode != NULL){
		Node_DeleteAllItems(binaryNode->left);
		Node_DeleteAllItems(binaryNode->right);
		free(binaryNode);
	}
}

void MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size){
	Long mid;
	binaryTree->root = Node_MakeTree(keys, 0, count-1, size);
	binaryTree->length = count;
	mid = (count + 1) / 2;
	binaryTree->balance = (count - mid) - (mid - 1);
}

BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size){
	Long mid;
	BinaryNode *node=NULL;

	if (low <= high){
		mid = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode)+size);
		memcpy(node + 1, ((char*)keys) + (mid*size), size);
		node->left = Node_MakeTree(keys, low, mid - 1,size);
		node->right = Node_MakeTree(keys, mid + 1, high, size);
	}
	return node;
}

void BinaryTree_Destroy(BinaryTree *binaryTree){
	Node_Destroy(binaryTree->root);
}

void Node_Destroy(BinaryNode *binaryNode){
	if (binaryNode != NULL){
		Node_Destroy(binaryNode->left);
		Node_Destroy(binaryNode->right);
		free(binaryNode);
	}
}

void BinaryTree_GetAt(BinaryNode *index, void *object, size_t size){
	memcpy(object, index + 1, size);
}