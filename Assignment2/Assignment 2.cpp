//Author: Ian McGregor
//Class: CSCI 2270
//Section: 310
//Program Requirements:
//Read in Tom_Sawyer.txt & ignoreWords.txt

//Output the following:
	//Calculate top n words

	//Calculate # of each uncommon word in the file

	//Calculate total # of uncommon words in the file
		
	//Calculate # of Array Doublings needed to store all uncommon words

	//Separate each category of output with a '#' character

#include <iostream>
#include <fstream> // file input and output
#include <cstdlib> // for exit(1); function
#include <sstream> // for stringstream
#include <string> // for strings...duh

using namespace std;

struct wordItem{
	string word;
	int count = 0;
	wordItem* resizeArr(wordItem itemArray[], int& cap);

};
	//Open file
	void readFile(string num2srch, string filename, string filename2);
	//Opens file of words to ignore.
	//Creates a dynamic array to contain them called ignoreArray[]
	string* extractIgnoreWords(string filename2, int& numIgnore);
	//Checks if line is in the array "ignoreArray[]"
	//Returns true if line is in the array, false if it is not in the array.
	bool isStopWord(string* ignoreArray, string line);
	//Checks if line already exists in the uncommonArray
	//Returns true if line is in the array, false if it is not in the array.
	bool commonInUncommon(wordItem uncommonArray[], string line, int numElements, int& found);
	// Returns uncommonArray sorted from highest count to lowest count
	wordItem* sortUncommon(wordItem uncommonArray[], int numElements);

int main(int argc, char* argv[]){
	string num2srch = argv[1];
	string filename = argv[2], filename2 = argv[3];

	readFile(num2srch, filename, filename2);

	return 0;
}
void readFile(string num2srch, string filename, string filename2){
		//Create array of words to ignore
	int numIgnore = 0;
	string* ignoreArray = extractIgnoreWords(filename2, numIgnore);
		//Open Tom
	ifstream input;
	input.open(filename);
		//File opening check
	if(!input.is_open()){
		cout << "\tInput file opening failure\n\t#\n";
	}

		//Create array of structs containing uncommon words & their counts
	wordItem* uncommonArray = new wordItem[10];
	int cap = 10;
	int numElements = 0;
	int numDoubles = 0;
	int totalNumIterations = 0;
	int totalNumUncommon = 0;
	int found = 0;
	string line;

	while(input >> line){
		totalNumIterations++;
			//CHECK AGAINST IGNORE WORDS ARRAY
		if(!isStopWord(ignoreArray, line)){
				//CHECK AGAINST WHAT IS ALREADY IN THE ARRAY
			if(!commonInUncommon(uncommonArray, line, numElements, found)){
				uncommonArray[numElements].word = line;
				uncommonArray[numElements].count++;
				numElements++;
				totalNumUncommon++;
			}else{
				uncommonArray[found].count++;
				totalNumUncommon++;
			}
		}
			//ARRAY DOUBLING
		if(numElements == cap){
			uncommonArray = uncommonArray->resizeArr(uncommonArray, cap);
			numDoubles++;
		}
	}
	uncommonArray = sortUncommon(uncommonArray, numElements);
	for (int i = 0; i < stoi(num2srch); i++){
			//set precision of output to two decimal places(reference:"Problem solving with C++", By:Walter Savitch, Page 257)
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);

		double percentage = 100 *((double)uncommonArray[i].count/totalNumIterations);
		cout <<"\t"<< uncommonArray[i].count << " - " << percentage << "% - " << uncommonArray[i].word << endl;
	}
			//TESTING BEGIN v
	cout << "\t#\n\tArray doubled: " << numDoubles << endl << "\t#" << endl;
	cout << "\tUnique noncommon words: " << numElements << endl << "\t#" << endl;
	cout << "\tTotal noncommon words: " << totalNumUncommon << endl;
			//TESTING END   ^
}
wordItem* sortUncommon(wordItem uncommonArray[], int numElements){
		//Sort in Descending OrDeR
	wordItem temp;
	for(int i = 0; i < numElements; i++){		
		for(int j = i+1; j < numElements; j++){
			if(uncommonArray[i].count < uncommonArray[j].count){
				temp = uncommonArray[i];
				uncommonArray[i] = uncommonArray[j];
				uncommonArray[j] = temp;
			}
		}
	}


	return uncommonArray;
}
bool commonInUncommon(wordItem uncommonArray[], string line, int numElements, int& found){
	for(int i = 0; i < numElements; i++){
		if (uncommonArray[i].word == line){
			found = i;
			return true;}
	}
	return false;
}
	//Checks if word being passed in is in the array "ignoreArray[]"
	//Returns true if the word is in the array, false if it is not in the array.
bool isStopWord(string* ignoreArray, string line){

	for(int i = 0; i < 50; i++){
		if(ignoreArray[i] == line){
			return true;
		}
	}
	return false;
}

string* extractIgnoreWords(string filename2, int& numIgnore){
		//Open file of words to ignore.
	ifstream ignoreWords;
	ignoreWords.open(filename2);
	//Creates a dynamic array to contain them called ignoreArray[]
	string* ignoreArray = new string[50];
	if(!ignoreWords.is_open()){
		cout << "\tIgnore words file opening failure!\n#\n";
	}else{

		string line;//for writing words from ignore file

		while(ignoreWords >> line){
			ignoreArray[numIgnore] = line;
			numIgnore++;
		}
	}
	return ignoreArray;
}
//An array of type wordItem must be passed in, as well as int "cap" which is a reference to the maximum size of the array when being passed
//Returns a wordItem array that is equal to the array passed into it, with the size double. also doubles int cap
wordItem* wordItem::resizeArr(wordItem itemArray[], int& cap){
	int newcap = cap * 2;
	wordItem* newarr = new wordItem[newcap];

	for(int i = 0; i < cap; i++){
		newarr[i] = itemArray[i];
	}
	cap = newcap;
	itemArray = newarr;
	return itemArray;
}