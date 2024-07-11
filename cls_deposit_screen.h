#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"
#include "cls_bank_client.h"

class cls_deposit_screen : protected cls_screen
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
    static void deposit(string clients_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t   Deposit Screen", "", user);
        string account_number = _read_account_number();
        while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
        {
            cout << "\nClient with [" << account_number << "] does not exist.\n";
            account_number = _read_account_number();
        }
        cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
        _print_client(client);
        float deposit_amount;
        cout << "\nPlease enter deposit amount? ";
        deposit_amount = cls_input_validate::read_number<float>();
        while (deposit_amount <= 0)
        {
            cout << "\nInvalid deposit amount! please, enter correct one: ";
            deposit_amount = cls_input_validate::read_number<float>();
        }
        cout << "\nAre you sure you want to perform this transaction? ";
        char answer;
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            client.account_balance += deposit_amount;
            client.save(clients_file, separator);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << client.account_balance;
        }
        else cout << "\nOperation was cancelled.\n";
    }
};