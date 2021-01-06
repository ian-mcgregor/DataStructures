//Ian McGregor
//Assignment #1 : Community Message Board
//Instructor: Christopher Godley
//Class: CSCI 2270 Section: 310

#include <iostream>
#include <fstream> // file input and output
#include <string> //for stoi() function
#include <cstdlib> // for exit(1); function
#include <string>
#include <sstream>

#define size 100
#define WANTED 0
#define FORSALE 1

using namespace std;

struct Item{

	string type;
	bool status;
	int price;
};
void readFile(Item itemArray[], Item itemsSold[], char* filename);
void appendArray(Item itemArray[], string type, bool status, int price, int& numElements);
int ArraySearchWanted(Item itemArray[], string type, int price, int numElements);
int ArraySearchForSale(Item itemArray[], string type, int price, int numElements);
void PrintArray(Item itemArray[], int numElements);
void DeleteArray(Item itemArray[], int ret, int& numElements);
void transferArrayData(Item itemArray[], Item itemsSold[], int ret, int& numSold);
void finalPrintSold(Item itemsSold[], int numSold);
void finalPrintRemaining(Item itemArray[], int numElements);

int main(int argc, char* argv[]){
	if(argc != 2){
		cout << "Please provide filename on the command line!\n";
		return -1;
	}//create a check for argc and argv to ensure user knowns if file opening fails or succeeds from command line
	char* filename = argv[1];
	cout << "Using filename: " << filename << endl << endl;

	//Open file, and fill array of structs with data
	Item itemArray[size];
	Item itemsSold[size];
	readFile(itemArray, itemsSold, filename);

	return 0;
}
void readFile(Item itemArray[], Item itemsSold[], char* filename){

	string line, type, tempPrice, tempStatus;
	bool status;
	int price, numElements = 0, index, ret, numSold = 0;

	ifstream garageSale;
	garageSale.open(filename);

	if (garageSale.is_open()){

		cout << "File opening success!\n\n";

		while (getline(garageSale, line)){
			//Read input from file line by line and store in temp variables
			stringstream ss(line);
			getline(ss, type, ',');

			getline(ss, tempStatus, ',');
			if(tempStatus.length()>7){
				status = true;//For sale
			}else{status = false;}//Wanted

			getline(ss, tempPrice);
			price = stoi(tempPrice);

			if(status == FORSALE){//search array for "wanted" items

				ret = ArraySearchWanted(itemArray, type, price, numElements); // returns index(-1 if match not found)
				if(ret > 0){
					appendArray(itemsSold, type, status, price, numSold);//search array for wanted items if match is found, add to items sold
					transferArrayData(itemArray, itemsSold, ret, numSold);//transfer temp data into items sold as well
					DeleteArray(itemArray, ret, numElements);//delete items sold from array at index found
				
				}else{
				// add item to array NOT FOUND

					appendArray(itemArray, type, status, price, numElements);//if not found, add to itemArray which stores non matches in MB

				}
			}else{//search array for "for sale" items
				//This section is the same as above in the if portion of the block, except it searches the array for items
				//that are for sale
				ret = ArraySearchForSale(itemArray, type, price, numElements);
				if(ret > 0){
				
					appendArray(itemsSold, type, status, price, numSold);
					transferArrayData(itemArray, itemsSold, ret, numSold);
					DeleteArray(itemArray, ret, numElements);
				}else{
				// add item to array NOT FOUND
					appendArray(itemArray, type, status, price, numElements);
				}
			}
		}
		//output final output in format laid out in assignment requirements
		cout << "Items Sold: " << endl;
		finalPrintSold(itemsSold, numSold);
		cout << "Items Remaining: " << endl << endl;
		finalPrintRemaining(itemArray, numElements);
		cout << "Number of items sold: " << numSold/2 << endl << endl;
		cout << "Number of items remaining in the message board after reading all lines in the file: " << numElements << endl;
	}else{
		cout << "File opening failed!\n" << "Terminating program, try again!\n";
		exit(1);
	}

	garageSale.close();	
}
void appendArray(Item itemArray[], string type, bool status, int price, int& numElements){

	itemArray[numElements].type = type;
	itemArray[numElements].status = status;
	itemArray[numElements].price = price;
	numElements++;
}
int ArraySearchWanted(Item itemArray[], string type, int price, int numElements){ 
	bool found = false; // Have we found it?
	int index = -1; // Where was it? 
	int i = 0;
	while(!found && i <= numElements) {
		if (type == itemArray[i].type && itemArray[i].status == WANTED && price <= itemArray[i].price) {
			found = true;
			index = i;
		} else {
			i++;
		}
	}
	return index;
}
int ArraySearchForSale(Item itemArray[], string type, int price, int numElements){ 
	bool found = false; // Have we found it?
	int index = -1; // Where was it? 
	int i = 0;
	while(!found && i <= numElements) {
		if (type == itemArray[i].type && itemArray[i].status == FORSALE && price >= itemArray[i].price) {
			found = true;
			index = i;
		} else {
			i++;
		}
	}
	return index;
}
void PrintArray(Item itemArray[], int numElements){

	for (int i = 0; i < numElements; i++){
		cout << "Type: " << itemArray[i].type << "\t";
		cout << "Status: " << itemArray[i].status << "\t";
		cout << "Price: " << itemArray[i].price << "\t" << endl;
	}
}
void DeleteArray(Item itemArray[], int ret, int& numElements){
	
	for(int i = ret; i < numElements; i++){
		itemArray[i]=itemArray[i+1];
	}
	numElements--;
}
void transferArrayData(Item itemArray[], Item itemsSold[], int ret, int& numSold){
	itemsSold[numSold] = itemArray[ret];
	numSold++;

}
void finalPrintSold(Item itemsSold[], int numSold){

	for(int i = 0; i < numSold; i++){
		if (itemsSold[i].status == FORSALE){
			cout << itemsSold[i].type << " " << itemsSold[i].price << endl << endl;
		}
	}
}
void finalPrintRemaining(Item itemArray[], int numElements){

	for(int i = 0; i < numElements; i++){
		cout << itemArray[i].type;
		if(itemArray[i].status == FORSALE){
			 cout << ", for sale, ";
		}else{
			cout << ", wanted, "; 
		}
		cout << itemArray[i].price << endl << endl;
	}
}