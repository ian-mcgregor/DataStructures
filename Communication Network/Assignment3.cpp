#include "CommunicationNetwork.cpp"


int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Invalid # of arguments to argv[], try again.\n";
        return -1;
    }
    int selection = 0;
    string toAdd;
    string prevCity;
    string toDelete;
    CommunicationNetwork Network;

    while(selection != 7){   
        cout << "======Main Menu======\n"
             << "1. Build Network\n"
             << "2. Print Network Path\n"
             << "3. Transmit Message Coast-To-Coast\n"
             << "4. Add City\n"
             << "5. Delete City\n"
             << "6. Clear Network\n"
             << "7. Quit\n\n";
        cin >> selection;
        if(selection == 1){

            Network.buildNetwork();

        }else if(selection == 2){

            Network.printNetwork();

        }else if(selection == 3){

            Network.transmitMsg(argv[1]); 

        }else if(selection == 4){

            cout << "Enter the name of the city you would like to add.\n\n";
            cin.ignore();
            getline(cin, toAdd);

            cout << "Enter the name of the city you would like to add " << toAdd << " after.\n\n";
            getline(cin, prevCity);
            Network.addCity(toAdd, prevCity);

        }else if(selection == 5){

            cout << "Enter the name of the city you would like to delete.\n\n";
            cin.ignore();
            getline(cin,toDelete);
            Network.deleteCity(toDelete);

        }else if(selection == 6){

            Network.deleteNetwork();

        }else if(selection < 1 || selection > 7 ){
            cout << "Invalid Entry, please try again!\n\n";
            if(cin.fail()){
                cin.clear();
                cin.ignore();
                cout << "Please enter an integer only!\n\n";
            }
        }
    }
    Network.~CommunicationNetwork();
    cout << "Goodbye!\n";

    return 0;
}