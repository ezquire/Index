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
	node *foundNode = NULL;
	cout << "Search word: ";
	cin >> input;
	if(containsHelper(input, root, foundNode)){
	    cout << "Line Numbers: " << foundNode->lines[0];
	    for(unsigned i = 1; i < foundNode->lines.size(); i++)
			cout << ", " <<foundNode->lines[i]; 
	    cout << '\n';
	}
	else
	    cout << '\"' << input <<"\" is not in the document\n";
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
					insertHelper(tempWord, line, root, distWords);
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
void TTT::insertHelper(const string& x, int line, node*& t, int& distWord) {
    if(t == NULL){
	    t = new node(x, "", NULL, NULL, NULL);
	    t->lines.push_back(line);
	    distWord++;
		return;
    }
	// Always fill in this direction: left k1k2 , center k1k2 , right k1k2
	/* Cases:
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
    else if (t->left == NULL) { // t is a leaf node
		if (t->key2 == "") { // node is a 2 node
			if (x.compare(t->key1) < 0) {//x < key1 move key1 to key2, key1 = x
				t->key2 = t->key1;
				t->key1 = x;
			}
			else if(x.compare(t->key1) > 0) //x > key1, key2 = x
				t->key2 = x;
			else // The word exists, push the additional line number
				t->lines.push_back(line);			
			return;
		}
		else { // t is a 3 node, it will overflow, promote the median

			node* xNode = new node(x, "", NULL, NULL, NULL);
			node* temp = new node("", "", NULL, NULL, NULL);
			node* tempL = new node(t->key1, "", NULL, NULL, NULL);
			node* tempR = new node(t->key2, "", NULL, NULL, NULL);

			if(x.compare(t->key1) == 0 || x.compare(t->key2) == 0)
				t->lines.push_back(line); // the word already exists
			
			else if(x.compare(t->key1) > 0) {// either x or key2 are the median
				if(x.compare(t->key2) < 0) { // x is the median
					xNode->left = tempL;
					xNode->center = tempR;
					t = xNode;
					delete xNode;
					return;
				}
				else { // key2 is the median, promote key2
					temp->key1 = t->key2;
					temp->left = tempL;
					temp->center = xNode;
					t = temp;
					delete temp;
					return;
				}
			}
			else { // x is < key1 so key1 is the median, promote key1
				temp->key1 = t->key1;
				temp->left = xNode;
				temp->center = tempR;
				t = temp;
				delete temp;
				return;
			}
		}
	}
	else { // non leaf node
		return;
	}
	
	return;
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
		int leftHeight = findHeight(t->left), rightHeight = findHeight(t->right);
		if(leftHeight > rightHeight)
			return(leftHeight+1);
		else 
			return(rightHeight+1);
    }
}
