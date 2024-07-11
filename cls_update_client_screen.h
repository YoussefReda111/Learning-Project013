#pragma once

#include "cls_bank_client.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"
#include "cls_screen.h"

using namespace std;

class cls_update_client_screen : protected cls_screen
{
private:
    static void _read_client_info(cls_bank_client& client)
    {
        cout << "\nEnter first name: ";
        client.first_name = cls_input_validate::read_string();
        cout << "\nEnter last name: ";
        client.last_name = cls_input_validate::read_string();
        cout << "\nEnter email: ";
        client.email = cls_input_validate::read_string();
        cout << "\nEnter phone: ";
        client.phone = cls_input_validate::read_string();
        cout << "\nEnter PIN code: ";
        client.PIN_code = cls_input_validate::read_string();
        cout << "\nEnter account balance: ";
        client.account_balance = cls_input_validate::read_double();
    }

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
    static void update_client(string clients_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t Update Client Screen", "", user);
        string account_number;
        cout << "\nPlease enter client account number: ";
        account_number = cls_input_validate::read_string();
        while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
        {
            cout << "\nAccount number is not found, choose another one: ";
            account_number = cls_input_validate::read_string();
        }
        cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
        _print_client(client);
        cout << "\n\nUpdate client info:";
        cout << "\n____________________\n";
        _read_client_info(client);
        cls_bank_client::en_saving_results save_result;
        save_result = client.save(clients_file, separator);
        switch (save_result)
        {
        case  cls_bank_client::en_saving_results::succeeded:
        {
            cout << "\nAccount updated successfully :-)\n";
            _print_client(client);
            break;
        }
        case cls_bank_client::en_saving_results::failed_empty_object:
        {
            cout << "\nError account was not saved because it's Empty :-(";
        }
        }
    }
};