//Author: Ian McGregor
//Class: Data Structures
//Section: 310
//Running this file:
// Run from the command line with exactly 2 arguments 
// argv[0] = "Assignment4"
// argv[1] = test file name of your choice

#ifndef MOVIETREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct LLNode{

	int rank, year, stock;
	string name;
	LLNode *next;
	LLNode *prev;
};

class LinkedList{
private:
	LLNode* head;

public:
	//Constructor
	LinkedList();
	//Prints contents of list
	void traverse();
	//Inserts a value to the Linked List
	LLNode* LLInsert(string name, int rank, int year, int stock);
	//Deletes a LLNode in the list
	void deleteLLNode(LLNode* value);
	//Searches alphabetically
	LLNode* listSearch(string target);

};

struct TreeNode {
	char alphabet;
	LinkedList list;
	TreeNode * parent;
	TreeNode * left;
	TreeNode * right;
};

class BST {
private:
	TreeNode * root;
	LinkedList list;
	int numMovies;
		//recursive print function
	void print_helper(TreeNode * curr, int depth);

	bool search_helper(int val, TreeNode * curr);

public:
	BST();
			//Builds tree of movies
	void buildTree (string filename, BST& BST);

	void print();

	void insert(char alphabet, string movieName, int movieRank, int movieYear, int inStock);

	LLNode* bstSearch(string name);

	void count();

	// void delete_val(int val);

	void printNumMovies();

	void deleteNode(string name);

};
#endif