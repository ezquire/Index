//Description: Prototypes for the binary search tree class.

#ifndef TTT_H
#define TTT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TTT {
 public: 
	TTT();
	void contains() const;
	bool isEmpty();
	void printTree(ostream &out = cout) const;
	void buildTree(ifstream &input);
 private:
	struct node {
	node(const string &x, const string &y, node *l, node *r, node *c, node *p)
	:lkey(x), rkey(y), left(l), right(r), center(c), parent(p){
		lval->resize(0);
		rval->resize(0);
	}
		string lkey, rkey;
		node *left, *right, *center, *parent;
		vector<int> *lval, *rval;
	};
	node* root;
	node* lchild(node *t) { return t->left; }
	node* rchild(node *t) { return t->right; }
	node* cchild(node *t) { return t->center; }
	string lkey(node *t) { return t->lkey; }
	string rkey(node *t) { return t->rkey; }
	vector<int>* lval(node *t) { return t->lval; }
	vector<int>* rval(node *t) { return t->rval; }
	void setLeft(const string &x, vector<int> *record, node *t) { t->lkey = x;
		t->lval = record; }
	void setRight(const string &x, vector<int> *record, node *t) { root->rkey
			= x; t->rval = record; }
	void setlchild(node *t, node *other) { t->left = other; }
	void setrchild(node *t, node *other) { t->right = other; }
	void setcchild(node *t, node *other) { t->center = other; }
	void insertHelper(const string &x, int line, node *&t, int &distWords);
	bool isLeaf(node *t) { return t->left == NULL; }
	//bool hasRoom(node *t) { return t->rkey == ""; }
	bool containsHelper(const string &x, node *t, node *&result) const;
	void printTreeHelper(node *t, ostream &out) const;
	int findHeight(node *t);
};
	
#endif	
    
	

