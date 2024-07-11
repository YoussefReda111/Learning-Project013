#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include "cls_bank_user.h"
#include <iomanip>

class cls_client_list_screen : protected cls_screen
{
public:
    static void show_clients_list(string clients_file, string separator, cls_bank_user user)
    {
        vector <cls_bank_client> vec_clients_data = cls_bank_client::get_users_list(clients_file, separator);
        string title = "\t  Client List Screen";
        string sub_title = "\t    (" + to_string(vec_clients_data.size()) + ") Client(s).";
        _draw_screen_header(title, sub_title, user);
        cout << "\n__________________________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n__________________________________________________________________________________________________\n" << endl;
        if (vec_clients_data.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (cls_bank_client client : vec_clients_data)
            {
                cout << "| " << setw(15) << left << client.account_number;
                cout << "| " << setw(20) << left << client.full_name();
                cout << "| " << setw(12) << left << client.phone;
                cout << "| " << setw(20) << left << client.email;
                cout << "| " << setw(10) << left << client.PIN_code;
                cout << "| " << setw(12) << left << client.account_balance << endl;
            }
        cout << "\n__________________________________________________________________________________________________\n" << endl;
    }
};