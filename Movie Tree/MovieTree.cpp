//Author: Ian McGregor
//Class: Data Structures
//Section: 310
//Running this file:
// Run from the command line with exactly 2 arguments 
// argv[0] = "Assignment4"
// argv[1] = test file name of your choice

#include "MovieTree.hpp"

	void BST::print_helper(TreeNode * curr, int depth) {
		if (curr) {
			print_helper( curr->left, depth + 1);

			curr->list.traverse();
			print_helper( curr->right, depth + 1);
		}
	}

	LLNode* BST::bstSearch(string name) {
		TreeNode * curr = root;
		char letter = name.at(0);
		while (curr) {
			if (curr->alphabet == letter)
				return curr->list.listSearch(name);
			else if (letter < curr->alphabet)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return NULL;
	}

	BST::BST() {
		root = NULL;
		numMovies = 0;
	}
	void BST::buildTree (string filename, BST& BST){
		// LinkedList list;
		string line, tempRank, movieName, tempYear, tempStock;
		char treeNode;
		int movieRank, movieYear, inStock;

			//End Variable Declarations
		ifstream input;
		input.open(filename);

		if(input.is_open()){
			cout << "\tFile opening success.\n\n";
		}
		while(getline(input, line)){
			stringstream ss(line);

			getline(ss, tempRank, ';');
			movieRank = stoi(tempRank);

			getline(ss, movieName, ';');
			treeNode = movieName.at(0);

			getline(ss, tempYear, ';');
			movieYear = stoi(tempYear);

			getline(ss, tempStock, '\n');
			inStock = stoi(tempStock);

			if(inStock > 0){
				BST.insert(treeNode, movieName, movieRank, movieYear, inStock);
				numMovies++;
			}
		}
	}

	void BST::insert(char alphabet, string movieName, int movieRank, int movieYear, int inStock) {
		
		TreeNode * curr = root;
		TreeNode * parent = NULL;

		while (curr) {
			parent = curr;
			if (alphabet < curr->alphabet)
				curr = curr->left;
			else if(alphabet > curr->alphabet){
				curr = curr->right;
			}else/*if alphabet = curr->alphabet*/{
				curr->list.LLInsert(movieName, movieRank, movieYear, inStock);
				return;
			}
		}

		TreeNode * newTreeNode = new TreeNode;
		newTreeNode->alphabet = alphabet;
		newTreeNode->list.LLInsert(movieName, movieRank, movieYear, inStock);

		newTreeNode->parent = parent;
		newTreeNode->left = NULL;
		newTreeNode->right = NULL;

		if (parent) {
			if (alphabet < parent->alphabet) {
				parent->left = newTreeNode;
			} else {
				parent->right = newTreeNode;
			}
		} else
			root = newTreeNode;

	}


	void BST::print(){
		print_helper(root, 0);
		cout << endl;
	}
	void BST::deleteNode(string name){
        LLNode* foundMovie = bstSearch(name);
	    if(foundMovie!=NULL){
	    	list.deleteLLNode(foundMovie);
	    	cout << foundMovie->name << " deleted.\n\n";
	    }else{
	    	cout << "\nMovie not found!\n\n";
	    }
	}

void BST::printNumMovies(){
	cout << numMovies;
	return;
}


// ===============Linked List===================//


LinkedList::LinkedList(){

	LLNode* temp = new LLNode;
	temp = NULL;
	head = temp;
}

LLNode* LinkedList::listSearch(string target){

	LLNode* here = head;
	while(here != NULL && here->name != target){
		here = here->next;
	}
	if(here->name == target){
		return here;
	}else{
		return NULL;
	}
}
LLNode* LinkedList::LLInsert(string name, int rank, int year, int stock){
	
	//Initialize a new LLNode
	LLNode* temp = new LLNode;
	LLNode* tail = new LLNode;
	temp = head;

	LLNode* add = new LLNode;
	add->name = name;
	add->rank = rank;
	add->year = year;
	add->stock = stock;

	if(temp == NULL){
		head = add;
		return head;
	}
	while(temp != NULL){
		if(add->name < temp->name){
			if(temp == head){//head
				add->next = temp;
				temp->prev = add;
				add->prev = NULL;
				head = add;
				break;
			} else {//middle
				add->next = temp;
				temp->prev->next = add;
				add->prev = temp->prev;
				temp->prev = add;
				break;
			}
		}else{ // if not <
			if(temp->next == NULL){
				tail = temp;
			}
			temp = temp->next;
		}
	}

	if(temp == NULL){
		tail->next = add;
		add->prev = tail;
		tail = add;
		add->next = NULL;
	}
	return head;
}
void LinkedList::traverse(){
	LLNode* iter;
	cout << endl;
	for(iter = head; iter != NULL; iter = iter->next){
		cout << " Movie: " << iter->name << " ";
		cout << iter->stock << endl;

		if(iter->next != NULL) {cout << endl << endl;}
	}
	cout << endl;
}
void LinkedList::deleteLLNode(LLNode* value){

  if (head == NULL) {
  	return;  
  }
  
	if(head->name == value->name){
		value = head;//toDelete will be placeholder for head value
		head = head->next;
    if (head != NULL) {//shifting head to next value
    	head->prev = NULL;
    }
    delete value;
    return;
	}
  
  //delete middle or tail
  LLNode* temp = head->next;
  while(temp != NULL){
    if(temp->name == value->name){
      value = temp;
      temp->prev->next = temp->next;
      if (temp->next != NULL) {
      	temp->next->prev = temp->prev;
      }
      break;
    }
    temp = temp->next;
  }
  delete value;
}
