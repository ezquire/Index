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
					root = insertNode(tempWord, root, line, distWords);
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

TTT::node* TTT::insertNode(const string &x, node *&t, int line, int &distWord) {
	key* newKey;
	if (containsHelper(x, t, newKey)){
		newKey->lineNumbers.push_back(line);
		return t;
	}
	else {
		distWord++;
		key *k = new key(x);
		k->lineNumbers.push_back(line);
		return insertKey(k, t);
	}

}

TTT::node* TTT::insertKey(key *newKey, node *&t) {	
	node *ret;
	if(t == NULL) {
		return new node(newKey, NULL, NULL, NULL);
    }
	if(t->isLeaf()) { // at leaf insert here
		t = add(new node(newKey, NULL, NULL, NULL));
		return t;
	}
	// add to internal node
	if(newKey->word.compare(t->lkey->word) < 0) { // insert left
		ret = insertKey(newKey, t->left);
		if(ret == t->left)
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
	else if(t->rkey == NULL) {
		ret = insertKey(newKey, t->right);
		if(ret == t->right)
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
	else if(newKey->word.compare(t->rkey->word) < 0) {
		ret = insertKey(newKey, t->center);
		if(ret == t->center)
			return t;
		else {
			t = add(ret);
			return t;
		}
	}
	else {
		ret = insertKey(newKey, t->center);
		if(ret == t->right)
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
	if(root->rkey == NULL) { // only one key add here
		if(root->lkey->word < t->lkey->word) {
			root->rkey = t->lkey;
			root->center = t->left;
			root->right = t->center;
		}
		else {
			root->rkey = root->lkey;
			root->right = root->center;
			root->lkey = t->lkey;
			root->center = t->center;
		}
		return root;
	}
	else if(root->lkey->word > t->lkey->word) { // Add left
		node* newNode = new node(root->lkey, t, NULL, root);
	    t->left = root->left;
		root->left = root->center;
		root->center = root->right;
		root->right = NULL;
		root->lkey = root->rkey;
		root->rkey = NULL;
		return newNode;
	}
	else if(root->rkey->word > t->lkey->word) { // Add center
		node *newNode = new node(root->rkey, t->center, NULL, root->right);
		t->center = newNode;
		t->left = root;
		root->rkey = NULL;
		root->right = NULL;
		return t;
	}
	else { // Add right
		node *newNode = new node(root->rkey, root, NULL, t);
		t->left = root->right;
		root->right = NULL;
		root->rkey = NULL;
		return newNode;
	}
}
//Used by contains() to see if a words is present or not. Will
//give contains() a pointer tothe found node so that contains()
//can prints the lines the word was found on.
bool TTT::containsHelper(const string &x, node *t, key *&result) const{
	if (t == NULL)
		return 0;
	if (t->rkey == NULL) {
		if (x.compare(t->lkey->word) < 0)
			return containsHelper(x, t->right, result);
		return 0;
	}
	if (x.compare(t->lkey->word) == 0){
	    result = t->lkey;
 	    return 1;
	}
	if (x.compare(t->lkey->word) > 0)
		return containsHelper(x, t->right, result);	
	if (x.compare(t->rkey->word) == 0){
	    result = t->rkey;
 	    return 0;
	}
	if (x.compare(t->rkey->word) > 0)
		return containsHelper(x, t->center, result);
	else
		return containsHelper(x, t->right, result);
	return containsHelper(x, t->left, result);
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
