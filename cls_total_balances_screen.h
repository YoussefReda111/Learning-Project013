#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include <iomanip>
#include "cls_utility.h"
#include "cls_bank_user.h"

class cls_total_balances_screen : protected cls_screen
{
public:
    static void total_balances(string clients_file, string separator, cls_bank_user user)
    {
        vector <cls_bank_client> vec_clients_data = cls_bank_client::get_users_list(clients_file, separator);
        string title = "\t  Balances List Screen";
        string sub_title = "\t    (" + to_string(vec_clients_data.size()) + ") Client(s).";
        _draw_screen_header(title, sub_title, user);
        cout << "\n_________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_________________________________________________________________________________\n" << endl;
        float total_balances = cls_bank_client::get_total_balances(clients_file, separator);
        if (vec_clients_data.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (cls_bank_client client_data : vec_clients_data)
            {
                cout << "| " << setw(15) << left << client_data.account_number;
                cout << "| " << setw(40) << left << client_data.full_name();
                cout << "| " << setw(12) << left << client_data.account_balance << endl;
            }
        cout << setw(25) << left << "" << "\n_________________________________________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t     Total Balances = " << total_balances << endl;
        cout << setw(8) << left << "" << "\t\t\t  ( " << cls_utility::convert_number_to_text(total_balances) << ")";
    }
};