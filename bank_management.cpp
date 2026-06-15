#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
public:
    int accountNo;
    string name;
    float balance;
};

void createAccount() {
    BankAccount acc;

    ofstream file("accounts.txt", ios::app);

    cout << "\nEnter Account Number: ";
    cin >> acc.accountNo;

    cout << "Enter Account Holder Name: ";
    cin >> acc.name;

    cout << "Enter Initial Balance: ";
    cin >> acc.balance;

    file << acc.accountNo << " "
         << acc.name << " "
         << acc.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    BankAccount acc;

    ifstream file("accounts.txt");

    cout << "\n===== ACCOUNT DETAILS =====\n";

    while (file >> acc.accountNo >> acc.name >> acc.balance) {
        cout << "\nAccount Number: " << acc.accountNo;
        cout << "\nName: " << acc.name;
        cout << "\nBalance: " << acc.balance << endl;
    }

    file.close();
}

void depositMoney() {
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    BankAccount acc;

    while (file >> acc.accountNo >> acc.name >> acc.balance) {
        if (acc.accountNo == accNo) {
            acc.balance += amount;
            found = true;
        }

        temp << acc.accountNo << " "
             << acc.name << " "
             << acc.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney() {
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    BankAccount acc;

    while (file >> acc.accountNo >> acc.name >> acc.balance) {
        if (acc.accountNo == accNo) {
            found = true;

            if (amount <= acc.balance) {
                acc.balance -= amount;
                cout << "\nWithdrawal Successful!\n";
            } else {
                cout << "\nInsufficient Balance!\n";
            }
        }

        temp << acc.accountNo << " "
             << acc.name << " "
             << acc.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void checkBalance() {
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("accounts.txt");
    BankAccount acc;

    while (file >> acc.accountNo >> acc.name >> acc.balance) {
        if (acc.accountNo == accNo) {
            cout << "\nCurrent Balance: " << acc.balance << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 6);

    return 0;
}