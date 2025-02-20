#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class BankAccount
{
private:
    string owner;
    int accountNumber;
    double balance;
    vector<string> transactionHistory;

public:
    BankAccount(string name, int accNum, double initialBalance)
    {
        owner = name;
        accountNumber = accNum;
        balance = initialBalance;
        loadTransactionHistory();
    }

    void deposit(double amount)
    {
        balance += amount;
        transactionHistory.push_back("Deposited: " + to_string(amount));
        cout << "Deposit successful! New balance: " << balance << endl;
        saveTransaction("Deposit", amount);
    }

    void withdraw(double amount)
    {
          

        if (amount > balance)
        {
            cout << "Insufficient funds!" << endl;
        }
        else if (amount == 0)
        {
            cout << "your balance is zero so you can not withdraw " << endl;
        }
        else
        {
            balance -= amount;
            transactionHistory.push_back("Withdrawn: " + to_string(amount));
            cout << "Withdrawal successful! New balance: " << balance << endl;
            saveTransaction("Withdraw", amount);
        }
    }

    void displayBalance()
    {
        cout << "Account Holder: " << owner << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: " << balance << endl;
    }

    void viewTransactionHistory()
    {
        cout << "Transaction History for Account " << accountNumber << ":" << endl;
        for (const auto &transaction : transactionHistory)
        {
            cout << transaction << endl;
        }
    }

    void saveTransaction(string type, double amount)
    {
        ofstream file("transactions.txt", ios::app);
        if (file)
        {
            file << accountNumber << " " << type << " " << amount << endl;
        }
        file.close();
    }

    void loadTransactionHistory()
    {
        ifstream file("transactions.txt");
        string type;
        double amount;
        int accNum;

        if (file)
        {
            while (file >> accNum >> type >> amount)
            {
                if (accNum == accountNumber)
                {
                    transactionHistory.push_back(type + ": " + to_string(amount));
                }
            }
        }
        file.close();
    }
};

int main()
{
    vector<BankAccount> accounts;
    accounts.push_back(BankAccount("John Doe", 1001, 5000));

    int choice;
    while (true)
    {
        cout << "\nBanking System" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        double amount;
        switch (choice)
        {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[0].deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            accounts[0].withdraw(amount);
            break;
        case 3:
            accounts[0].displayBalance();
            break;
        case 4:
            accounts[0].viewTransactionHistory();
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
