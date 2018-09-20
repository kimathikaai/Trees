#include "BinarySearchTree.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

// Implement the funct

BinarySearchTree::Node::Node(DataType newval)
{
	val = newval;
	right = NULL;
	left = NULL;
}

BinarySearchTree::BinarySearchTree()
{
	root_ = NULL;
	size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
	if(root_ == NULL)
		return;
	while(root_->left != NULL)
		remove(root_->left->val);
	while(root_->right != NULL)
		remove(root_->right->val);
	delete root_;
	root_ = NULL;
}

bool BinarySearchTree::insert(DataType val)
{
	if(exists(val))
		return false;

	Node* newNode = new Node(val);

	if(size_ == 0)
	{
		root_ = newNode;
		size_++;
		return true;
	}

	Node* temp = root_;
	Node* tempBelow = root_;

	while(tempBelow != NULL)
	{
		temp = tempBelow;
		if(val > tempBelow->val)
			tempBelow = tempBelow->right;
		else
			tempBelow = tempBelow->left;
	}

	if(val > temp->val)
		temp->right = newNode;
	if(val < temp->val)
		temp->left = newNode;
	size_++;
	return true;
}

bool BinarySearchTree::remove(DataType val)    // removing root special case???????
{
	if(root_ == NULL)
		return false;
	if(!exists(val))
		return false;
	size_--;
	Node* temp = root_;
	Node* tempParent = root_;

	while(temp->val != val){
		tempParent = temp;
		if(val < temp->val)
			temp = temp->left;
		else if(val > temp->val)
			temp = temp->right;
	}
	if(temp->left == NULL && temp->right == NULL)
	{
		if(temp == root_)
		{
			delete root_;
			root_ = NULL;
			temp = NULL;
			return true;
		}
		if(tempParent->right != NULL && tempParent->right->val == val)
		{
		delete temp;
		temp = NULL;
		tempParent->right = NULL;
		return true;
		}

		if(tempParent->left != NULL && tempParent->left->val == val)
		{
		delete temp;
		temp = NULL;
		tempParent->left = NULL;
		return true;
		}
	}
	if((temp->right == NULL && temp->left != NULL) || (temp->right != NULL && temp->left == NULL))
	{
		if(tempParent->right != NULL && tempParent->right->val == val)
		{
			if(temp->right == NULL)
				tempParent->right = temp->left;

			else if(temp->left == NULL)
				tempParent->right = temp->right;

		}
		else if(tempParent->left != NULL || tempParent->left->val == val)
		{
			if(temp->left == NULL)
				tempParent->left = temp->right;

			else if(temp->right == NULL)
				tempParent->left = temp->left;
		}
		delete temp;
		temp = NULL;
		return true;
	}
	else
	{
		Node* tempReplace = temp->left;
		Node* tempReplaceParent = temp->left;
		while(tempReplace->right != NULL){
			tempReplaceParent = tempReplace;
			tempReplace = tempReplace->right;
		}
		temp->val = tempReplace->val;
		if(tempReplace->left != NULL)
		{
			tempReplaceParent->right = tempReplace->left;
		}
		if(tempReplace == tempReplaceParent && tempReplaceParent->left == NULL)
		{
			temp->left = NULL;
		}
		delete tempReplace;
		tempReplace=NULL;
		return true;
	}
	return true;
}

bool BinarySearchTree::exists(DataType val) const
{
	Node* temp = root_;
	bool exist = false;
	while(temp != NULL && exist == false)
	{
		if(temp->val == val)
			exist = true;
		else if(val > temp->val)
			temp = temp->right;
		else if(val < temp->val)
			temp = temp->left;
	}
	return exist;

}

BinarySearchTree::DataType BinarySearchTree::min() const
{
	Node* temp = root_;
	Node* min = NULL;
	while(temp != NULL)
	{
		min = temp;
		temp = temp->left;
	}
	return min->val;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
	Node* temp = root_;
	Node* max = NULL;
	while(temp != NULL)
	{
		max = temp;
		temp = temp->right;
	}
	return max->val;
}

unsigned int BinarySearchTree::size() const
{
	return size_;
}

unsigned int BinarySearchTree::depth() const
{
	return getNodeDepth(root_);
}

void BinarySearchTree::print() const
{

}

int BinarySearchTree::getNodeDepth(Node* n) const //optional private function... can be used in depth()
{
	if(n == NULL)
		return -1;
	else
		return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
}








