//Description: Prototypes for the two-three tree class.

#ifndef TTT_H
#define TTT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct key {
	key() {
		word = "";
		lineNumbers.resize(0);
	}
	key(const string &x) {
		word = x;
		lineNumbers.resize(0);
	}
	string word;
	vector<int> lineNumbers;
};

struct node {
	node() { left = center = right = NULL; }
	node(key *k, node *l, node *c, node *r) {
		lkey = k;
		rkey = NULL;
		left = l;
		center = c;
		right = r;
	}		
	key *lkey, *rkey;
	node *left, *center, *right;

	bool isLeaf() { return (left == NULL && center == NULL && right == NULL); }

};

class TTT { 
 public: 
	TTT();
	void contains() const;
	bool contains(const string &x) const;
	bool isEmpty();
	void printTree(ostream &out = cout) const;
	void buildTree(ifstream &input);
 private:
	node* root;
	int words = 0;
	node* insertNode(const string &x, node *&t, int line, int &distWords);
	node* insertKey(key *k, node *&t);
	node* add(node *t, node *rt);
	bool containsHelper(const string &x, node *t, key *&result) const;
	void printTreeHelper(node *t, ostream &out) const;
	int findHeight(node *t);
};
	
#endif
