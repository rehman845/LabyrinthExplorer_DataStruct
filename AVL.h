#pragma once
#include <iostream>

using namespace std;

template<typename type>
struct Node {
	type data;
	int height;
	Node* left;
	Node* right;
	Node(type d): data(d) {
		height = 0;
		left = right = NULL;
	}
};

template<class type>
class AVL
{
public:
	Node<type>* root;
	AVL(): root(NULL){ }
	int Height(Node<type>* ptr);
	Node<type>* RRrotation(Node<type>*& ptr);
	Node<type>* LLrotation(Node<type>*& ptr);
	Node<type>* LRrotation(Node<type>*& ptr);
	Node<type>* RLrotation(Node<type>*& ptr);
	Node<type>* insert(type val, Node<type>* ptr);
	void insert(type val) {
		root = insert(val, root);
	}

};



template<class type>
inline int AVL<type>::Height(Node<type>* ptr) {
	return ptr == NULL ? -1 : ptr->height;
}

template<class type>
inline Node<type>* AVL<type>::insert(type val, Node<type>* ptr) {
	if (ptr == NULL) {
		Node<type>* newVal = new Node<type>(val);
		ptr = newVal;
	}
	else if (val < ptr->data) {
		ptr->left = insert(val, ptr->left);
		////////////////rotation/////////////
		if (abs(Height(ptr->left) - Height(ptr->right)) >= 2) {
			if (val < ptr->left->data)
				ptr = RRrotation(ptr->left);
			else
				ptr = RLrotation(ptr->left);
		}
	}
	else {
		ptr->right = insert(val, ptr->right);
		////////////////rotation/////////////
		if (abs(Height(ptr->left) - Height(ptr->right)) >= 2)
			if (val > ptr->right->data)
				ptr = LLrotation(ptr->right);
			else
				ptr = LRrotation(ptr->right);
	}
	ptr->height = max(Height(ptr->left), Height(ptr->right)) + 1;
	return ptr;
}

template<class type>
inline Node<type>* AVL<type>::RRrotation(Node<type>*& ptr) {
	Node<type>* imbalanceNode = ptr->left;
	ptr->left = imbalanceNode->right;
	imbalanceNode->right = ptr;
	ptr->height = max(Height(ptr->left), Height(ptr->right)) + 1;
	imbalanceNode->height = max(Height(imbalanceNode->left), Height(imbalanceNode->right)) + 1;
	return imbalanceNode;
}

template<class type>
inline Node<type>* AVL<type>::LLrotation(Node<type>*& ptr) {
	Node<type>* imbalanceNode = ptr->right;
	ptr->right = imbalanceNode->left;
	imbalanceNode->left = ptr;
	ptr->height = max(Height(ptr->left), Height(ptr->right)) + 1;
	imbalanceNode->height = max(Height(imbalanceNode->left), Height(imbalanceNode->right)) + 1;
	return imbalanceNode;
}

template<class type>
inline Node<type>* AVL<type>::RLrotation(Node<type>*& ptr) {
	ptr->left = LLrotation(ptr->left);
	ptr = RRrotation(ptr);
	return ptr;
}

template<class type>
inline Node<type>* AVL<type>::LRrotation(Node<type>*& ptr) {
	ptr->right = RRrotation(ptr->right);
	ptr = LLrotation(ptr);
	return ptr;
}