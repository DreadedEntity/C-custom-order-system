#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> //only for system("cls")
#include <fstream>

#include "customer.h"

using namespace std;

void listOrdersFull(vector<Customer*>);
void listOrdersNames(vector<Customer*>);
Customer* createOrder();
int removeOrder(vector<Customer*>);
void saveOrders(vector<Customer*>);
vector<Customer*> loadDatabase();

void waitForEnter();

int main() {
    vector<Customer*> customerList = loadDatabase();

    bool continueLoop = true;

    do {
        cout << endl;
        cout << "\tWelcome to the Customer Order Database" << endl << endl;
        cout << "\t  1. Check active orders" << endl;
        cout << "\t  2. Create a new order" << endl;
        cout << "\t  3. Remove an order" << endl;
        cout << "\t  4. Exit program" << endl << endl;

        int input = 0;
        do {
            cout << "\tEnter your selection: ";
            cin >> input;
            if (input < 1 || input > 4) {
                cout << "\tSelection is out of range! " << endl;
            }
        } while (input < 1 || input > 4);

        switch (input) {
            case 1: listOrdersFull(customerList); break;
            case 2:
                {
                    Customer* newCustomer = createOrder();
                    customerList.push_back(newCustomer);
                    break;
                };
            case 3:
                {
                    int num = removeOrder(customerList);
                    customerList.erase(customerList.begin() + num);
                    cout << endl << "\tOrder " << num + 1 << " was removed!" << endl;

                    waitForEnter();
                    break;
                };
            case 4: {
                saveOrders(customerList);
                continueLoop = false;
                break;
            };
            default: { cout << "How did you do this?" << endl; };
        }

        system("cls");
    } while (continueLoop);

    cout << "Thank you for using the Customer Order Database";
    return 0;
};

//function lists full details about each order
void listOrdersFull(vector<Customer*> customers) {
    for (int i = 0; i < customers.size(); i++) {
        cout << endl;
        cout << "\t" << customers[i]->getFirstName() << " " << customers[i]->getLastName() << endl;
            cout << "\t" << customers[i]->getAddress() << endl;
            cout << "\t" << customers[i]->getItemName() << ", " << customers[i]->getAmountOrdered() << endl;
    }
        cout << endl << "\tTotal orders: " << customers.size() << endl;

    waitForEnter();
};

//function lists orders, but only the names
void listOrdersNames(vector<Customer*> customers) {
    cout << endl;
    for (int i = 0; i < customers.size(); i++) {
        cout << "\t" << i + 1 << ". " << customers[i]->getFirstName() << " " << customers[i]->getLastName() << endl;
    }
}

//function prompts the user for input, then creates and returns a Customer object
Customer* createOrder() {
    cout << endl;
    cout << "\tEnter the customers first name: ";
    string firstName;
    cin >> firstName;

    cout << "\tEnter the customers last name: ";
    string lastName;
    cin >> lastName;
    cin.ignore(); //ignore newline char

    cout << "\tEnter the customers address: ";
    string address;
    getline(cin, address);

    cout << "\tEnter the name of the item ordered: ";
    string itemName;
    getline(cin, itemName);


    cout << "\tEnter the amount of items ordered: ";
    string amountOrdered;
    cin >> amountOrdered;

    Customer* c = new Customer(firstName, lastName, address, itemName, amountOrdered);

    cout << endl << "\tOrder has been added" << endl;
    waitForEnter();
    return c;
};

//function lists active orders, prompts the user for input, then returns the number
int removeOrder(vector<Customer*> customerList) {
    listOrdersNames(customerList);

    int input = 0;
    do {

        cout << "\tEnter order number to be removed: ";
        cin >> input;
        if (input < 1 || input > customerList.size()) {
            cout << "\tSelection is out of range! " << endl;
        }
    } while (input < 1 || input > customerList.size());
    input--;

    return input;
};

//function waits for the user to press enter
void waitForEnter() {
    cout << endl;
    cout << "\tPress Enter to continue" << endl;
    string temp;
    temp = cin.get();
    getline(cin, temp);
};

//function iterates the vector and saves all data
void saveOrders(vector<Customer*> customers) {
    ofstream file;
    file.open("orderdb.txt");

    for (int i = 0; i < customers.size(); i++) {
        file << customers[i]->getFirstName() << endl;
        file << customers[i]->getLastName() << endl;
        file << customers[i]->getAddress() << endl;
        file << customers[i]->getItemName() << endl;
        file << customers[i]->getAmountOrdered();
        if (i < customers.size() - 1) {
            file << endl;
        }
    }

    file.close();
}

//function loads data into file until EOF and returns the populated vector
vector<Customer*> loadDatabase() {
    ifstream file("orderdb.txt");
    vector<Customer*> customerList;

    while (!file.eof()) {
        string firstName;
        getline(file, firstName);

        string lastName;
        getline(file, lastName);

        string address;
        getline(file, address);

        string itemName;
        getline(file, itemName);

        string amountOrdered;
        getline(file, amountOrdered);

        customerList.push_back(new Customer(firstName, lastName, address, itemName, amountOrdered));
    };

    file.close();
    return customerList;
};
