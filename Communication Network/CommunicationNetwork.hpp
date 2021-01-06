/* 
 * CommunicationNetwork.hpp
 */

#ifndef COMMUNICATIONNETWORK_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream> // file input and output

using namespace std;

// City: the node struct that will be stored in the CommunicationNetwork
//       linked-list
struct City
{
    string name;         // name of the city
    string message;      // message this city has received
    City *next;            // pointer to the next city
    City *prev;            // pointer to the next city
};

// class for storing and manipulating linked-list of cities
class CommunicationNetwork {
    private:
        City *head;
    public:
        CommunicationNetwork();
        ~CommunicationNetwork();
        City* citySearch(string target);

        void addCity(string newCityName, string previousCityName);
        /* Insert a new city into the linked list after the previousCityName. 
         * The name of the new
         * city is in the argument newCityName. */

        void transmitMsg(char * filename);
        /* Open the file and transmit the message between all cities in the 
         * network word by word. A word needs to be received at the beginning 
         * of the network after being sent to the end of the network before 
         * sending the next word (coast to coast to coast). Only one city can 
         * hold the message at a time; as soon as it is passed to the next 
         * city, it needs to be deleted from the sender city. */

        void printNetwork();
        /* Start at the head of the linked list and print the name of each city
         * in order to the end of the list. */

        void buildNetwork();
        /* Build the initial network from the cities given in this writeup. 
         * The cities can be fixed in the function, you do not need to write 
         * the function to work with any list of cities. */

        void deleteCity(string removeCity);
        /* Find the city in the network where city name matches removeCity. 
         * Change the next and previous pointers for the surrounding cities and
         * free the memory. */

        void deleteNetwork();
        /* Delete all cities in the network, starting at the head city. */
};
#endif
