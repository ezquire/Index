//Description: Implementations for the two-three tree class.

#include "ttt.h"
#include "time.h"
#include <iomanip>
#include <sstream>

//Constructor
TTT::TTT(){
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TTT::isEmpty(){
    return root == NULL;
}

//Used to implement the search function in the main
//program.
void TTT::contains() const{
	//string input;
	//node *foundNode = NULL;
	/*cout << "Search word: ";
	cin >> input;
	if(containsHelper(input, root, foundNode)){
	    cout << "Line Numbers: " << foundNode->lval[0]; // need to change this
	    for(unsigned i = 1; i < foundNode->lval.size(); i++)
			cout << ", " <<foundNode->lval[i]; 
	    cout << '\n';
	}
	else
	cout << '\"' << input <<"\" is not in the document\n";*/
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TTT::printTree(ostream & out) const {
	out << "Binary Search Tree Index:\n-------------------------\n";
	printTreeHelper(root, out);
}

//Receives the specified input file and constructs 
//the actual tree. Prints a message when finished.
void TTT::buildTree(ifstream & input){
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	vector<int> *lines = {0};
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (unsigned i = 0; i < tempLine.length(); i++) {
		    //Insert valid chars into tempWord until a delimiter (newline
			//or space) is found
		    while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
		    }
		   
            //Trim any punctuation off end of word.
			// Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
			    tempWord.resize(tempWord.size() -1);   
			
            if (tempWord.length() > 0)
				{
					//Once word is formatted,call insert with the word,
					//the line of the input file it came from, the root of our
					// tree, and the distinct word counter
					//lines->push_back(line);
					insertHelper(tempWord, lines, root, distWords);
					//Increment our total number of words inserted
					numWords++;
					//Clear out tempWord so we can use it again
					tempWord.clear();
				}
			
		}
		line++;
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
	treeHeight = findHeight(root);

	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords<< endl;

	cout << setw(40) << std::left 
		 << "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left 
		 <<"Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
		 <<"Height of TTT is : " << treeHeight << endl;
 
}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
TTT::node* TTT::insertHelper(const string& x, vector<int>* record, node *t, int& distWord) {
	node *ret;
	if(t == NULL){
		distWord++;
		return new node(x, record, "", NULL, NULL, NULL, NULL);
    }
	/*
	// Always fill in this direction: left k1k2 , center k1k2 , right k1k2
	Cases:
	   1. leaf is not full - find correct node, insert key, if key < key1 
	   move key1 to key2, key1 = key, else key2 = key
	   2. leaf is full but parent is not - insert key in new right child, 
	   promote key2 from center child to parent
	   3. both leaf and parent are full - the median(key, key1, key2) is
	   promoted to a parent, the min of the leftover keys becomes the 
	   left child, the max of them becomes the right child if the 
	   parent is full the process is called recursively on the parent 
	   until it is not full
	*/
	if(t->isLeaf()) { // at leaf insert here
		return add(new node(x, record, "", NULL, NULL, NULL, NULL));
	}
	// add to internal node
	if(x.compare(t->getlkey()) < 0){ // insert left
		ret = insertHelper(x, record, t->lchild(), distWord);
		if( ret == t->lchild())
			return t;
		else
			return add(ret);
	}
	else if((t->getrkey() == "") || (x.compare(t->getrkey()) < 0)) {
		ret = insertHelper(x, record, t->cchild(), distWord);
		if(ret == t->cchild())
			return t;
		else
			return add(ret);
	}
	else { // insert right
		ret = insertHelper(x, record, t->rchild(), distWord);
		if(ret == t->rchild())
			return t;
		else
			return add(ret);
	}
}

TTT::node* TTT::add(node *t) {
	if(root->getrkey() == "") { // only one key
		if(root->getlkey().compare(t->getlkey()) < 0) {
			root->setrkey(t->getlkey());
			root->setrval(t->getrval());
			root->setcchild(t->lchild());
			root->setrchild(t->cchild());
		}
		else {
			root->setrkey(root->getlkey());
			root->setrval(root->getlval());
			root->setrchild(root->cchild());
			root->setlkey(t->getlkey());
			root->setlval(t->getlval());
			root->setcchild(t->cchild());
		}
		return root;
	}
	else if(root->getlkey().compare(t->getlkey()) >= 0) { // Add left
		node* newNode = new node(root->getlkey(), root->getlval(),  "", NULL,
								 t, root, NULL);
		t->setlchild(root->lchild());
		root->setlchild(root->cchild());
		root->setcchild(root->rchild());
		root->setrchild(NULL);
		root->setlkey(root->getrkey());
		root->setlval(root->getrval());
		root->setrkey("");
		root->setrval(NULL);
		return newNode;
	}
	else if(root->getrkey().compare(t->getlkey()) >= 0) { // Add center
		t->setcchild(new node(root->getrkey(), root->getrval(), "", NULL, t->cchild(), root->rchild(), NULL));
		t->setlchild(root);
		root->setrkey("");
		root->setrval(NULL);
		root->setrchild(NULL);
		return t;
	}
	else { // Add right
		node *newNode = new node(t->getrkey(), t->getrval(), "", NULL, root, t, NULL);
		t->setlchild(root->rchild());
		root->setrchild(NULL);
		root->setrkey("");
		root->setrval(NULL);
		return newNode;
	}
}
//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TTT::containsHelper(const string & x, node * t, node * &result) const{
	/*	if (t == NULL)
		return false;
	if (t->key.compare(x) == 0){
	    result = t;
 	    return true;
	}
	else if (x > t->key)
		return containsHelper(x, t->right, result);
	else
	return containsHelper(x, t->left, result);*/
	return 1;
}

//Called by printTree(), does the actual formatted printing
void TTT::printTreeHelper(node *t, ostream & out) const{
	/*    if(t == NULL)
		return;
	else {
		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->key << " " << t->lines[0];
		for (unsigned i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
		printTreeHelper(t->right, out);
		}*/
}

//Returns height of tree. If tree has only one node, height is 1    
int TTT::findHeight(node *t){
    if(t == NULL)
		return 0;
    else {
		int leftHeight = findHeight(t->lchild());
			int rightHeight = findHeight(t->rchild());
		if(leftHeight > rightHeight)
			return(leftHeight+1);
		else 
			return(rightHeight+1);
    }
}
