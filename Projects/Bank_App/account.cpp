#include <iostream>
#include <iomanip>
#include "account.h"

using namespace std;

void Account::createAccount()
{
    cout << "\nEnter Account No: ";
    cin >> AccountNumber;
    cout << "\nEnter Account Holder Name: ";
    cin.ignore();
    cin.getline(name,30);
    cout << "Enter Account Type (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter Initial Deposit: ";
    cin >> balance;
    cout << "\n\nAccount Created Successfully";
}

void Account::showAccount() const
{
    cout << "\nAccount No: " << AccountNumber;
    cout << "\nAccount Holder Name: " << name;
    cout << "\nAccount Type: " << type;
    cout << "\nBalance Amount: " << balance;
}

void Account::deposit(const Amount &amount)
{
    balance += amount;
}

void Account::withdraw(const Amount &amount)
{
    balance -= amount;
}

void Account::report() const
{
    cout << setw(10) << AccountNumber << setw(20) << name << setw(10) << type << setw(10) << balance << endl;
}

AccNo Account::getAccountNunber() const
{
    return AccountNumber;
}

Balance Account::getBalance() const
{
    return balance;
}

AccType Account::getType() const
{
    return type;
}