#ifndef AVLTREE
#define AVLTREE

class AVLTree {
private:
	class AVLNode {
	public:
		string username;
		string password;
		int height;
		AVLNode* left;
		AVLNode* right;

		AVLNode() {
			username = password = "";
			left = right = NULL;
			height = 0;
		}

		AVLNode(string& un, string& pw, AVLNode* l, AVLNode* r) {
			username = un;
			password = pw;
			height = 0;
			left = l;
			right = r;
		}
	};

	typedef AVLNode* AVLNodePointer;
	AVLNodePointer myRoot = 0;

	int height(AVLNode* tree);
	AVLNode* searchAux(AVLNode* x, string& un);
	AVLNode* maximum(AVLNode* tree);
	AVLNode* minimum(AVLNode* tree);
	AVLNode* leftLeftRotation(AVLNode* k2);
	AVLNode* rightRightRotation(AVLNode* k1);
	AVLNode* leftRightRotation(AVLNode* k3);
	AVLNode* rightLeftRotation(AVLNode* k1);
	AVLNode* insertAux(AVLNode*& tree, string& un, string& pw);
	AVLNode* removeAux(AVLNode*& tree, AVLNode* z);

	void deleteAux(AVLNodePointer subtreeRoot) const;
	void printAux(AVLNodePointer subtreeRoot) const;
	void foutFileAux(ofstream& fout, AVLNodePointer subtreeRoot) const;

public:
	AVLTree();
	~AVLTree();
	bool empty();
	void setPW(string& un, string& pw);
	void print() const;//中序遍历输出
	int max(int a, int b);//查找最大高度
	AVLNode* search(string& un);
	void insert(string& un, string& pw);
	void remove(string& un);
	void foutFile() const;
};
#endif