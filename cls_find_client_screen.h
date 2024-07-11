#pragma once

#include "cls_bank_client.h"
#include "cls_screen.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"

class cls_find_client_screen : protected cls_screen
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

public:
    static void find_client(string clients_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\tFind Client Screen", "", user);
        string account_number;
        cout << "\nPlease Enter Account Number: ";
        account_number = cls_input_validate::read_string();
        while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
        {
            cout << "\nAccount number is not found, choose another one: ";
            account_number = cls_input_validate::read_string();
        }
        cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
        if (!client.is_empty())
            cout << "\nClient Found :-)\n";
        else
            cout << "\nClient Was not Found :-(\n";
        _print_client(client);
    }
};