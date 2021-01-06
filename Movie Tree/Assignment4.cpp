//Author: Ian McGregor
//Class: Data Structures
//Section: 310
//Running this file:
// Run from the command line with exactly 2 arguments 
// argv[0] = "Assignment4"
// argv[1] = test file name of your choice

#include "MovieTree.cpp"


using namespace std;


int main(int argc, char* argv[]){

	if (argc != 2){
		cout << "\t Error: Invalid number of arguments to command line.\n\n";
		return -1;
	}

	string filename = argv[1];
	BST bst;
	string title;
	int selection;
	LLNode * foundMovie;

	bst.buildTree(filename, bst);
	while(selection != 6){   
        cout << "======Main Menu======\n"
             << "1. Find a Movie\n"
             << "2. Rent a Movie\n"
             << "3. Print the inventory\n"
             << "4. Delete a Movie\n"
             << "5. Count the movies\n"
             << "6. Quit\n\n";
        cin >> selection;

   		if(selection == 1){

            cout << "Enter Title:" << endl;
            cin.ignore();
            getline(cin, title, '\n');
            foundMovie = bst.bstSearch(title);
            if(foundMovie != NULL){
            cout << "Movie Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << foundMovie->rank << endl;
			cout << "Title:" << foundMovie->name << endl;
			cout << "Year:" << foundMovie->year << endl;
			cout << "Quantity:" << foundMovie->stock << endl << endl;
			}else{
				cout << "\nMovie not found!\n\n";
			}

        }else if(selection == 2){

        	cout << "Rent movie not yet implemented\n\n";

        }else if(selection == 3){

        	bst.print();

        }else if(selection == 4){
            cout << "Enter Title:" << endl;
            cin.ignore();
            getline(cin, title, '\n');
            bst.deleteNode(title);

        }else if(selection == 5){

        	cout << "Tree contains: "; 
        	bst.printNumMovies();
        	cout << " movies." << endl; 

		}else if(selection < 1 || selection > 6 ){
            cout << "Invalid Entry, please try again!\n\n";
            if(cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Please enter an integer only!\n\n";
            }
        }
    }
    cout << "Goodbye!\n";
	return 0;
}
