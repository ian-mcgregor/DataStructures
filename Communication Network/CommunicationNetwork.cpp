#include "CommunicationNetwork.hpp"
//Constructor
CommunicationNetwork::CommunicationNetwork(){
    City *temp = new City;
    temp = NULL;
    head = temp;
}
//Destructor
CommunicationNetwork::~CommunicationNetwork(){
    deleteNetwork();
    delete head;
}
/* Open the file and transmit the message between all cities in the 
 * network word by word. A word needs to be received at the beginning 
 * of the network after being sent to the end of the network before 
 * sending the next word (coast to coast to coast). Only one city can 
 * hold the message at a time; as soon as it is passed to the next 
 * city, it needs to be deleted from the sender city. */

void CommunicationNetwork::printNetwork(){
    if (head == NULL){
        cout << "Error: Network Empty.\n";
        return;
    }else{
        cout << "===CURRENT PATH===" << endl;
        City *iter;
        cout << "NULL<-";

        for(iter = head; iter != NULL; iter = iter->next){
            cout << iter->name;
            if(iter->next != NULL) {cout << "<->";}
        }
    cout << "->NULL" << endl;
    cout << "==================" << endl;
    }
}
void CommunicationNetwork::buildNetwork(){
    City *add = new City;
    add->name = "Los Angeles";
    add->message = "";
    add->next = NULL;
    add->prev = NULL;
    head = add;

    add = new City;
    City *prev = head;
        //add pheonix
    add->name = "Pheonix";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Denver";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Dallas";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "St. Louis";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Chicago";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Atlanta";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Washington D.C.";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "New York";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;

    prev = add;
    add = new City;
    add->name = "Boston";
    add->message = "";
    add->next = NULL;
    add->prev = prev;
    prev->next = add;
}
/* Build the initial network from the cities given in this writeup. 
 * The cities can be fixed in the function, you do not need to write 
 * the function to work with any list of cities. */
City* CommunicationNetwork::citySearch(string target){
    City *here = head;
    while(here != NULL && here->name != target){
        here = here->next;
        if(here == NULL){
            return here;
        }
    }if(here->name == target){
        return here;
    }
    return NULL;
}
/*Search existing network of cities for the city name at each node
*return node where city name was found.*/
void CommunicationNetwork::addCity(string newCityName, string previousCityName){

    City *addCity = new City;
    addCity->name = newCityName;
    City *prevCity = citySearch(previousCityName);

    if(prevCity == NULL && previousCityName != "First" && previousCityName != ""){
        cout << "City insert failed, " << previousCityName << " is not in the network. \n\n";
        return;
    }
    if(previousCityName == ""){
        prevCity = head;
        City *temp = new City;

        while(prevCity->next != NULL){
            prevCity = prevCity->next;
        }
        temp->name = newCityName;
        temp->message = "";
        temp->next = NULL;
        temp->prev = prevCity;
        prevCity->next = temp;
        return;
    }
    if(previousCityName == "First"){

        City *temp = new City;
        temp->name = newCityName;
        temp->message = "";
        temp->next = head;
        head->prev = temp;
        temp->prev = NULL;
        head = temp;
        return;
    }
    // cout << addCity->name << " will be added after " << prevCity->name << endl;
    addCity->next = prevCity->next;
    prevCity->next = addCity;
    addCity->prev = prevCity;

    if(addCity->next != NULL){
        addCity->next->prev = addCity;
    }
    return;
}
/* Insert a new city into the linked list after the previousCityName. 
 * The name of the new
 * city is in the argument newCityName. */
void CommunicationNetwork::deleteCity(string removeCity){
    City *toDelete;
    if(citySearch(removeCity) == NULL){
        cout << removeCity << " not found.\n";
        return;
    }

    //delete head
    if(head == NULL){
        return;
    }
    if(head->name == removeCity){
        toDelete = head;
        head = head->next;
        if(head != NULL){
            head->prev = NULL;
        }
        delete toDelete;
        return;
    }

    //delete middle or tail
    City *temp = head->next;
    while(temp != NULL){
        if(temp->name == removeCity){
            toDelete = temp;
            temp->prev->next = temp->next;
            if(temp->next != NULL){
                temp->next->prev = temp->prev;
            }
            break;
        }
        temp = temp->next;
    }
    cout << "Removing " << temp->name << endl << endl;
    delete toDelete;
}
/* Find the city in the network where city name matches removeCity. 
 * Change the next and previous pointers for the surrounding cities and
 * free the memory. */

void CommunicationNetwork::transmitMsg(char * filename){
    string line;
    ifstream input;
    input.open(filename);
    if(!input.is_open()){
        cout << "Input file opening failure\n\n";
        return;
    }
    while(input >> line){
        City *here = head;
        while(here != NULL){
            here->message = line;
            cout << here->name << " recieved " << here->message << endl;
            here->message = "";
            if(here->next!=NULL){
                here = here->next;
            }else if(here->next == NULL){
                here = here->prev;
                while(here->prev != NULL){
                    here->message = line;
                    cout << here->name << " recieved " << here->message << endl;
                    here->message = "";
                    if(here->prev != NULL){
                        here = here->prev;
                    }else{break;}
                }
            }
            if(here->prev == NULL){
                here->message = line;
                cout << here->name << " recieved " << here->message << endl;
                here->message = "";
                cout << endl;
                break;
            }
        }
    }
}
/* Open the file and transmit the message between all cities in the 
 * network word by word. A word needs to be received at the beginning 
 * of the network after being sent to the end of the network before 
 * sending the next word (coast to coast to coast). Only one city can 
 * hold the message at a time; as soon as it is passed to the next 
 * city, it needs to be deleted from the sender city. */


void CommunicationNetwork::deleteNetwork(){

    City *iter = head;

    while(iter != NULL){
        City *temp = iter;
        iter = iter->next;
        head = iter;
        cout << "Deleting " << temp->name << endl;
        delete temp;
    }
}
/* Delete all cities in the network, starting at the head city. */

