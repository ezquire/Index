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
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (unsigned i = 0; i < tempLine.length(); i++) {
		    //Insert valid chars into tempWord until a delimiter (newline
			//or space) is found
			while (tempLine[i] != ' '&& tempLine[i] != '\n' &&
				   i < tempLine.length() ) {
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
		    }
            //Trim any punctuation off end of word.
			// Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 &&
				  !isalnum(tempWord[tempWord.length() - 1]))
			    tempWord.resize(tempWord.size() -1);   
			
            if (tempWord.length() > 0)
				{
					//Once word is formatted,call insert with the word,
					//the line of the input file it came from, the root of our
					// tree, and the distinct word counter
					//lines->push_back(line);
					insertHelper(tempWord, root, line, distWords);
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
TTT::node* TTT::insertHelper(const string &x, node *&t, int line,
							 int &distWord) {
	node *ret;
	vector<int> emptyvec;
	emptyvec.resize(0);
	const string nullstring = "";
	
	if(t == NULL) {
		vector<int> newRecord;
		newRecord.push_back(line);
		//cout << "newRecord[0]: " << newRecord[0] << endl;
	    t = new node(x, newRecord, nullstring, emptyvec,
					 NULL, NULL, NULL);
		//cout << "lval[0]: " << newNode->lval[0] << endl;
		//cout << "hit here\n";
		distWord++;
		return t;
    }
	if(t->isLeaf()) { // at leaf insert here
		t = add(new node(x, t->getlval(), nullstring, emptyvec,
						 NULL, NULL, NULL));
		return t;
	}
	// add to internal node
	if(x.compare(t->getlkey()) < 0) { // insert left
		ret = insertHelper(x, t->lchild(), line, distWord);
		if(ret == t->lchild())
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
	else if((t->getrkey() == "") || (x.compare(t->getrkey()) < 0)) {
		// insert center
		ret = insertHelper(x, t->cchild(), line, distWord);
		if(ret == t->cchild())
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
	else {
		ret = insertHelper(x, t->rchild(), line, distWord);
		if(ret == t->rchild())
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
}

TTT::node* TTT::add(node *t) {
	const string nullstring = "";
	vector<int> emptyvec;
	emptyvec.resize(0);
	if(root->rkey == "") { // only one key
		if(root->lkey.compare(t->getlkey()) < 0) {
			root->rkey = t->getlkey();
			/*cout << "rkey: " << root->rkey << endl;
			cout << "lkey: " << root->lkey << endl;
			vector<int> tval = t->getlval();
			cout << "t rval: " << tval[0] << endl;*/
			root->rval = t->getlval();
			root->center = t->lchild();
			root->right = t->cchild();
		}
		else {
			root->rkey = root->lkey;
			root->rval = root->lval;
			root->right = root->center;
			root->lkey = t->getlkey();
			root->lval = t->getlval();
			root->center = t->cchild();
		}
		return root;
	}
	else if(root->lkey.compare(t->getlkey()) >= 0) { // Add left
		node* newNode = new node(root->lkey, root->lval,
								 nullstring, emptyvec, t, root, NULL);
		t->setlchild(root->lchild());
		root->setlchild(root->cchild());
		root->setcchild(root->rchild());
		root->setrchild(NULL);
		root->setlkey(root->getrkey());
		root->setlval(root->getrval());
		root->setrkey("");
		root->setrval(emptyvec);
		return newNode;
	}
	else if(root->getrkey().compare(t->getlkey()) >= 0) { // Add center
		t->setcchild(new node(root->rkey, root->getrval(), nullstring,
							  emptyvec, t->cchild(), root->rchild(), NULL));
		root->setrkey("");
		root->setrval(emptyvec);
		root->setrchild(NULL);
		t->setlchild(root);
		return t;
	}
	else { // Add right
		node *newNode = new node(t->getrkey(), t->getrval(), nullstring,
								 emptyvec, root, t, NULL);
		root->setrchild(NULL);
		root->setrkey("");
		root->setrval(emptyvec);
		t->setlchild(root->right);
		return newNode;
	}
}
//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TTT::containsHelper(const string & x, node * t, node * &result) const{
	if (t == NULL)
		return false;
	if (t->lkey.compare(x) == 0 || (t->rkey != "" && t->rkey.compare(x) == 0)){
	    result = t;
 	    return true;
	}
	if (x > t->lkey && (t->rkey == "" || x < t->rkey)) {
		return containsHelper(x, t->cchild, result);
	}

	if (t->rkey != "" && x > t->rkey){
		return containsHelper(x, t->rchild, result);
	}

	return false;
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
    /*if(t == NULL)
		return 0;
    else {
		int leftHeight = findHeight(t->lchild());
		int rightHeight = findHeight(t->rchild());
		if(leftHeight > rightHeight)
			return(leftHeight+1);
		else 
			return(rightHeight+1);
			}*/
	return 1;
}
