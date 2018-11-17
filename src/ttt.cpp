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
	string input;
	key *foundNode = NULL;
	cout << "Search word: ";
	cin >> input;
	if(containsHelper(input, root, foundNode)){
	    cout << "Line Numbers: " << foundNode->lineNumbers[0];
		for(unsigned i = 1; i < foundNode->lineNumbers.size(); ++i)
			cout << ", " << foundNode->lineNumbers[i];
		cout << '\n';
	}
	else
	cout << '\"' << input <<"\" is not in the document\n";
}

bool TTT::contains(const string &x) const {
	key *result;
	return containsHelper(x, root, result);
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TTT::printTree(ostream & out) const {
	out << "Two-Three Tree Index:\n-------------------------\n";
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
			
            if (tempWord.length() > 0) {
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

node* TTT::insertNode(const string &x, node *&t, int line, int &distWord) {
	key* newKey;
	if (containsHelper(x, t, newKey)) {
		newKey->lineNumbers.push_back(line);
		return t;
	}
	else {
		newKey = new key(x);
		newKey->lineNumbers.push_back(line);
		++distWord;
		return insertKey(newKey, t);
	}
}

node* TTT::insertKey(key *newKey, node *&t) {	
	node *ret;
	if(t == NULL)
		return new node(newKey, NULL, NULL, NULL);

	// at leaf insert
	if(t->isLeaf()) {
		t = add(new node(newKey, NULL, NULL, NULL), t);
		return t;
	}

	// add to internal node
	if(newKey->word < t->lkey->word) { // insert left
		ret = insertKey(newKey, t->left);
		if(ret == t->left)
			return t;
		else {
			t = add(ret, t);
			return t;
		}
	}
	else if(t->rkey == NULL) {
		ret = insertKey(newKey, t->right);
		if(ret == t->right)
			return t;
		else {
			t = add(ret, t);
			return t;
		}
	}
	else if(newKey->word < t->rkey->word) {
		ret = insertKey(newKey, t->center);
		if(ret == t->center)
			return t;
		else {
			t = add(ret, t);
			return t;
		}
	}
	else { // Insert right
		ret = insertKey(newKey, t->right);
		if(ret == t->right)
			return t;
		else {
			t = add(ret, t);
			return t;
		}
	}
}

node* TTT::add(node *t, node *other) {
	if(other->rkey == NULL) { // only one key add here
		if(other->lkey->word < t->lkey->word) {
			other->rkey = t->lkey;
			other->center = t->left;
			other->right = t->center;
		}
		else {
			other->rkey = other->lkey;
			other->right = other->center;
			other->lkey = t->lkey;
			other->center = t->center;
		}
		return other;
	}
	else if(other->lkey->word > t->lkey->word) { // Add left
		node* newNode = new node(other->lkey, t, NULL, other);
	    t->left = other->left;
		other->left = other->center;
		other->center = other->right;
		other->right = NULL;
		other->lkey = other->rkey;
		other->rkey = NULL;
		return newNode;
	}
	else if(other->rkey->word > t->lkey->word) { // Add center
		node *newNode = new node(other->rkey, t->center, NULL, other->right);
		t->center = newNode;
		t->left = other;
		other->rkey = NULL;
		other->right = NULL;
		return t;
	}
	else { // Add right
		node *newNode = new node(other->rkey, other, NULL, t);
		t->left = other->right;
		other->right = NULL;
		other->rkey = NULL;
		return newNode;
	}
}
//Used by contains() to see if a words is present or not. Will
//give contains() a pointer tothe found node so that contains()
//can prints the lines the word was found on.
bool TTT::containsHelper(const string &x, node *t, key *&result) const{
	//cout << "hit containsHelper" << endl;
	if (t == NULL)
		return false;

	if (x.compare(t->lkey->word) == 0){
	    result = t->lkey;
 	    return 1;
	}

	if (x.compare(t->lkey->word) < 0) 
		return containsHelper(x, t->left, result);

	if(t->rkey == NULL) {
		if(x.compare(t->lkey->word) > 0)
			return containsHelper(x, t->right, result);
		return 0;
	}

	if (x.compare(t->rkey->word) == 0){
	    result = t->rkey;
 	    return 1;
	}
	
	if (x.compare(t->rkey->word) < 0)
		return containsHelper(x, t->center, result);
	else
		return containsHelper(x, t->right, result);
}

//Called by printTree(), does the actual formatted printing
void TTT::printTreeHelper(node *t, ostream & out) const{
	if(t == NULL) {
		return;
	}
	else {
		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->lkey->word << " " << t->lkey->lineNumbers[0];
		for (unsigned i = 1; i < t->lkey->lineNumbers.size(); ++i)
			out << ", " << t->lkey->lineNumbers[i];
		out << endl;
		printTreeHelper(t->center, out);
		if(t->rkey != NULL){
			out << setw(30) << std::left;
			out << t->rkey->word << " " << t->rkey->lineNumbers[0];
			for (unsigned i = 1; i < t->rkey->lineNumbers.size(); ++i)
				out << ", " << t->rkey->lineNumbers[i];
			out << endl;
		}
		printTreeHelper(t->right, out);
	}
}

//Returns height of tree. If tree has only one node, height is 1    
int TTT::findHeight(node *t){
    if(t == NULL)
		return 0;
    else {
		int left = findHeight(t->left);
		int right = findHeight(t->right);
		int center = findHeight(t->center);
		if(left > center && left > right)
			return(left + 1);
		if(center > left && center > right)
			return(center + 1);
		if(right > left && right > center)
			return(right + 1);
	}
	return 1;
}
