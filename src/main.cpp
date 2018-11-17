//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include "bst.h"
#include "ttt.h"

using namespace std;

int main(int argc, char* argv[]) {
	int choice;
	char choice1;
	BST myTree;
	TTT twoThree;
	
	if (argc != 2) {
	    cout << "Incorrect input. Correct format: ./<exectuable.out> ";
		cout << "<inputtext.txt>\n";
	    return 1;
	}

	ifstream input(argv[1]);

	if(input.is_open()){
		while(1) {
			choice1 = ' ';
			cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 ";
			cout << "Tree\n";
			cin >> choice1;
			switch(choice1) {
			case 'a': {
				myTree.buildTree(input);
				input.close();
				while(1) {
					choice = 0;
					cout << "Options: (1) display index, (2) search, (3) ";
					cout << "save index, (4) quit\n";
					cin >> choice;
					switch(choice) {
					case 1:
						myTree.printTree(cout);	
						break;
					case 2:
						myTree.contains();
						break;
					case 3: {
						string outputFile;
						cout << "Enter a filename to save your index to ";
						cout << "(Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						myTree.printTree(output);
						output.close();
						cout << "Saved\n";
						break;
					}
					case 4:
						exit(1);
					default:
						break;
					}
				}
				break;
			}
			case 'b': {
				twoThree.buildTree(input);
				input.close();
				while(1) {
					choice = 0;
					cout << "Options: (1) display index, (2) search, (3) ";
					cout << "save index, (4) quit\n";
					cin >> choice;
					switch(choice) {
					case 1:
						twoThree.printTree(cout);	
						break;
					case 2:
						twoThree.contains();
						break;
					case 3: {
						string outputFile;
						cout << "Enter a filename to save your index to ";
						cout << "(Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						twoThree.printTree(output);
						output.close();
						cout << "Saved\n";
						break;
					}
					case 4:
						exit(1);
					default:
						break;
					}
				}
				break;
			}
			case 'c': {
			    myTree.buildTree(input);
				twoThree.buildTree(input);
				input.close();

				double time_bst, time_ttt;
				double start, finish = clock();
				
				for(int i = 0; i < myTree.getSize(); ++i)
					//myTree.contains();
					;
				finish = clock();
				time_bst = (double)(finish - start)/CLOCKS_PER_SEC;
			
				start = finish = clock();
				
				for(int i = 0; i < myTree.getSize(); i++)
					//twoThree.contains();
					;
				finish = clock();
				time_ttt = (double)(finish - start)/CLOCKS_PER_SEC;

				cout << setw(40) << std::left << "Total time taken by BST: ";
				cout << time_bst << endl;
				cout << setw(40) << std::left << "Total time taken by 2-3 ";
				cout << "Tree: ";
				cout << time_ttt << endl;
				break;
			}
			default:
				break;
			}
		}
	}	
	else {
		cout << "Invalid File Name. Restart Program.\n";
		return 2;
	}
	return 0;
}
