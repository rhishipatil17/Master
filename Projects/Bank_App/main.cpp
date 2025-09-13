#include <iostream>
#include "account.h"

using namespace std;

int main()
{
    int choice;
    AccNo accNo;

    do
    {
        cout << "Bank Management System";
        cout << "\n1. New Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Balance Enquiry";
        cout << "\n5. All Account Holder List";
        cout << "\n6. Close Account";
        cout << "\n7. Modify Account";
        cout << "\n8. Exit";
        cout << "\nSelect your option (1 - 8)-> ";

        switch (choice)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                break;
        }
    }
    while(choice != 8);

    return 0;
}