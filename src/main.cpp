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
	vector<string> wordList;
	
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
				BST binarySearch;
				binarySearch.buildTree(input, wordList);
				input.close();
				while(1) {
					choice = 0;
					cout << "Options: (1) display index, (2) search, (3) ";
					cout << "save index, (4) quit\n";
					cin >> choice;
					switch(choice) {
					case 1:
						binarySearch.printTree(cout);	
						break;
					case 2:
						binarySearch.contains();
						break;
					case 3: {
						string outputFile;
						cout << "Enter a filename to save your index to ";
						cout << "(Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						binarySearch.printTree(output);
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
				TTT twoThree;
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
				BST bst;
				TTT ttt;
				vector<string> wordList1;
				ifstream input1(argv[1]);
				ifstream input2(argv[1]);
				cout << "Binary Search Tree: \n";
				bst.buildTree(input1, wordList1);
				cout << "2-3 Tree: \n";
				ttt.buildTree(input2);
				input1.close();
				input2.close();
				input.close();
				
				double time_bst, finish_bst, start_bst = clock();

				// BST
				for(unsigned i = 0; i < wordList1.size(); ++i)
					bst.contains(wordList1[i]);
				finish_bst = clock();
				time_bst = (double)(finish_bst - start_bst)/CLOCKS_PER_SEC;
				
				double time_ttt, finish_ttt, start_ttt = clock();
				
				// 2-3 Tree
				for(unsigned i = 0; i < wordList1.size(); i++)
					ttt.contains(wordList1[i]);
				finish_ttt = clock();
				time_ttt = (double)(finish_ttt - start_ttt)/CLOCKS_PER_SEC;

				cout << setw(40) << std::left << "Total time taken by BST: "
					 << time_bst << endl;
				cout << setw(40) << std::left
					 << "Total time taken by 2-3 Tree: " << time_ttt << endl;
				exit(1);
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
