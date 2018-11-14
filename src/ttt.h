//Description: Prototypes for the binary search tree class.

#ifndef TTT_H
#define TTT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h>

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

		node() { left = center = right = NULL; }
 		node(const string &lk, vector<int> lv, const string &rk,
			 vector<int> rv, node *l, node *c, node *r) {
			lkey = lk; rkey = rk;
			lval = lv; rval = rv;
			left = l; center = c; right = r;
		}		
		string lkey;
		vector<int> lval;
		string rkey;
		vector<int> rval;
		node *left, *center, *right;

		bool isLeaf() { return left == NULL; }
		node *&lchild() { return left; }
		node *&rchild() { return right; }
		node *&cchild() { return center; }
		
		string getlkey() { return lkey; }
		vector<int> getlval() { return lval; }
		string getrkey() { return rkey; }
		vector<int> getrval() { return rval; }
		
		void setLeft(const string &x, vector<int> record) { lkey = x;
			lval = record; }
		void setRight(const string &x, vector<int> record) { rkey = x;
			rval = record; }
		
		void setlchild(node *t) { left = t; }
		void setrchild(node *t) { right = t; }
		void setcchild(node *t) { center = t; }

		void setlkey(const string& k) { lkey = k; }
		void setrkey(const string& k) { rkey = k; }
		void setlval(vector<int> record) { lval = record; }
		void setrval(vector<int> record) { rval = record; }

		node* insertHelper(const string &x, node *&t, int line,
						   int &distWords);
		node* add(node *t);

	};
	node* root;
	node* insertHelper(const string &x, node *&t, int line, int &distWords);
	node* add(node *t);
	bool containsHelper(const string &x, node *t, node *&result) const;
	void printTreeHelper(node *t, ostream &out) const;
	int findHeight(node *t);
};
	
#endif	
    
	

