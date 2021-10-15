#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#include"AVL.h"

AVLTree::AVLTree() {
	myRoot = 0;
}

AVLTree::~AVLTree() {
	deleteAux(myRoot);
}

bool AVLTree::empty() {
	return myRoot == 0;
}

void AVLTree::deleteAux(AVLNodePointer subtreeRoot) const {
	if (subtreeRoot != 0) {
		deleteAux(subtreeRoot->left);
		deleteAux(subtreeRoot->right);
		delete subtreeRoot;
	}
}

void AVLTree::print() const {
	printAux(myRoot);
}

void AVLTree::printAux(AVLNodePointer subtreeRoot) const {
	if (subtreeRoot != NULL) {
		printAux(subtreeRoot->left);
		cout << "用户名：" << subtreeRoot->username << endl;
		cout << "密码：" << subtreeRoot->password << endl << endl;
		printAux(subtreeRoot->right);
	}
}

void AVLTree::setPW(string& un, string& pw) {
	search(un)->password = pw;
}

void AVLTree::foutFile() const {
	ofstream file("Adm.txt");//重新打开文件，清空文件内容
	foutFileAux(file, myRoot);
}

void AVLTree::foutFileAux(ofstream& fout, AVLNodePointer subtreeRoot) const {
	try {
		if (subtreeRoot != NULL) {
			foutFileAux(fout, subtreeRoot->left);
			fout << "un:" << subtreeRoot->username << "\npw:" << subtreeRoot->password <<"\n";
			foutFileAux(fout, subtreeRoot->right);
		}
	}
	catch (...) { ; }
}

AVLTree::AVLNode* AVLTree::search(string& un)
{
	return searchAux(myRoot, un);
}

AVLTree::AVLNode* AVLTree::searchAux(AVLNode* x, string& un)
{
	if (x == NULL || x->username == un)
		return x;
	if (un < x->username)
		return searchAux(x->left, un);
	else
		return searchAux(x->right, un);
}

AVLTree::AVLNode* AVLTree::maximum(AVLNode* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

AVLTree::AVLNode* AVLTree::minimum(AVLNode* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

int AVLTree::height(AVLNode* tree)
{
	if (tree != NULL)
		return tree->height;
	return 0;
}

int AVLTree::max(int a, int b)
{
	return a > b ? a : b;
}

AVLTree::AVLNode* AVLTree::leftLeftRotation(AVLNode* k2)
{
	AVLNode* k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;

	return k1;
}

AVLTree::AVLNode* AVLTree::rightRightRotation(AVLTree::AVLNode* k1)
{
	AVLTree::AVLNode* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;

	return k2;
}

AVLTree::AVLNode* AVLTree::leftRightRotation(AVLNode* k3)
{
	k3->left = rightRightRotation(k3->left);

	return leftLeftRotation(k3);
}

AVLTree::AVLNode* AVLTree::rightLeftRotation(AVLNode* k1)
{
	k1->right = leftLeftRotation(k1->right);

	return rightRightRotation(k1);
}

AVLTree::AVLNode* AVLTree::insertAux(AVLNode* &tree, string& un, string& pw)
{
	if (tree == NULL)
	{
		tree = new AVLNode(un, pw, NULL, NULL);
	}
	else if (un < tree->username) // 应该将key插入到"tree的左子树"的情况
	{
		tree->left = insertAux(tree->left, un, pw);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (un < tree->left->username)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (un > tree->username) // 应该将key插入到"tree的右子树"的情况
	{
		tree->right = insertAux(tree->right, un, pw);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (un > tree->right->username)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

void AVLTree::insert(string& un, string& pw)
{
	insertAux(myRoot, un, pw);
}

AVLTree::AVLNode* AVLTree::removeAux(AVLNode* &tree, AVLNode* z)
{
	// 待删除的节点在"tree的左子树"中
	if (z->username < tree->username)
	{
		tree->left = removeAux(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLNode *r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	// 待删除的节点在"tree的右子树"中
	else if (z->username > tree->username){
		tree->right = removeAux(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLNode *l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	// tree是对应要删除的节点。
	else 
	{
		if ((tree->left != NULL) && (tree->right != NULL))
		{
			if (height(tree->left) > height(tree->right))
			{
				AVLNode* max = maximum(tree->left);
				tree->username = max->username;
				tree->left = removeAux(tree->left, max);
			}
			else
			{
				AVLNode* min = minimum(tree->right);
				tree->username = min->username;
				tree->right = removeAux(tree->right, min);
			}
		}
		else
		{
			AVLNode* tmp = tree;
			tree = (tree->left != NULL) ? tree->left : tree->right;
			delete tmp;
		}
	}
	return tree;
}

void AVLTree::remove(string& un)
{
	AVLNode* z;

	if ((z = searchAux(myRoot, un)) != NULL)
		myRoot = removeAux(myRoot, z);
}