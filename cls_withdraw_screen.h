#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include "cls_bank_user.h"
#include "cls_input_validate.h"

class cls_withdraw_screen : protected cls_screen
{
private:
    static void _print_client(cls_bank_client client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.first_name;
        cout << "\nLastName    : " << client.last_name;
        cout << "\nFull Name   : " << client.full_name();
        cout << "\nEmail       : " << client.email;
        cout << "\nPhone       : " << client.phone;
        cout << "\nAcc. Number : " << client.account_number;
        cout << "\nPassword    : " << client.PIN_code;
        cout << "\nBalance     : " << client.account_balance;
        cout << "\n___________________\n";
    }

    static string _read_account_number()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    static void withdraw(string clients_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t   Withdraw Screen", "", user);
        string account_number = _read_account_number();
        while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
        {
            cout << "\nClient with [" << account_number << "] does not exist.\n";
            account_number = _read_account_number();
        }
        cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
        _print_client(client);
        float withdraw_amount;
        cout << "\nPlease enter Withdraw amount? ";
        withdraw_amount = cls_input_validate::read_number<float>();
        while (withdraw_amount <= 0)
        {
            cout << "\nInvalid withdraw amount! please, enter correct one: ";
            withdraw_amount = cls_input_validate::read_number<float>();
        }
        cout << "\nAre you sure you want to perform this transaction? ";
        char answer;
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            if (client.account_balance >= withdraw_amount)
            {
                client.account_balance -= withdraw_amount;
                client.save(clients_file, separator);
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << client.account_balance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << withdraw_amount;
                cout << "\nYour Balance Is: " << client.account_balance;
            }
        }
        else cout << "\nOperation was cancelled.\n";
    }
};