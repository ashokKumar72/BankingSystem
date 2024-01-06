#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Structure to represent a bank account
struct BankAccount {
    int accountNumber;
    char name[50];
    double balance;
};

// Function to add a new account to the file
void addAccount() {
    BankAccount newAccount;

    // Prompting the user for account details
    cout << "Enter Account Number: ";
    cin >> newAccount.accountNumber;

    cout << "Enter Name: ";
    cin.ignore(); // Clear buffer
    cin.getline(newAccount.name, sizeof(newAccount.name));

    cout << "Enter Initial Balance: ";
    cin >> newAccount.balance;

    // Opening the file in append and binary mode
    ofstream outFile("bank_data.txt", ios::app | ios::binary);

    // Checking if the file is opened successfully
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Writing the account information to the file
    outFile.write(reinterpret_cast<char*>(&newAccount), sizeof(newAccount));

    // Closing the file
    outFile.close();

    cout << "Account added successfully!" << endl;
}

// Function to display all accounts from the file
void displayAllAccounts() {
    // Opening the file in binary mode for reading
    ifstream inFile("bank_data.txt", ios::binary);

    // Checking if the file is opened successfully
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    BankAccount account;

    // Displaying all accounts stored in the file
    cout << "**** All Bank Accounts ****" << endl;

    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(account))) {
        cout << "Account Number: " << account.accountNumber << endl;
        cout << "Name: " << account.name << endl;
        cout << "Balance: $" << account.balance << endl;
        cout << "------------------------" << endl;
    }

    // Closing the file
    inFile.close();
}

int main() {
    int choice;
do {
        // Displaying a menu for user choices
        cout << "\n**** Bank Management System ****" << endl;
        cout << "1. Add Account\n2. Display All Accounts\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Switching based on user choice
        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                displayAllAccounts();
                break;
            case 3:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 3);

}
