#pragma once

#include "cls_bank_client.h"
#include "cls_input_validate.h"
#include "cls_screen.h"
#include "cls_bank_user.h"

using namespace std;

class cls_delete_client_screen : protected cls_screen
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
    static void delete_client(string clients_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t Delete Client Screen", "", user);
        string account_number;
        cout << "\nPlease enter account number: ";
        account_number = cls_input_validate::read_string();
        while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
        {
            cout << "\nAccount number is not found, choose another one: ";
            account_number = cls_input_validate::read_string();
        }
        cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
        _print_client(client);
        cout << "\nAre you sure you want to delete this client y/n? ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            client.get_delete_user_object();
            client.save(clients_file, separator);
            _print_client(client);
        }
        else cout << "\nClient was not deleted\n";
    }
};