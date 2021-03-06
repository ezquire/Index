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
	void printTree(ostream& out = cout) const;
	void buildTree(ifstream& input);
 private:
	struct node {
	node(const string& x, const string& y, node* l, node* r, node* c)
	:key1(x), key2(y), left(l), right(r), center(c){
		lines.resize(0);
	}
		string key1;
		string key2;
		node* left;
		node* right;
		node* center;
		vector<int> lines;
	};
	node* root;
	void insertHelper(const string& x, int line, node*& t, int& distWords);
	bool containsHelper(const string& x, node* t, node*& result) const;
	void printTreeHelper(node* t, ostream& out) const;
	int findHeight(node* t);
};
	
#endif	
    
	

