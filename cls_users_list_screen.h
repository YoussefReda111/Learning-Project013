#pragma once

#include "cls_bank_user.h"
#include "cls_screen.h"
#include "cls_bank_user.h"
#include <iomanip>

class cls_users_list_screen : protected cls_screen
{
public:
    static void show_users_list(string users_file, string separator, cls_bank_user user)
    {
        vector <cls_bank_user> vec_users = cls_bank_user::get_users_list(users_file, separator);
        string title = "\t  User List Screen";
        string sub_title = "\t    (" + to_string(vec_users.size()) + ") User(s).";
        _draw_screen_header(title, sub_title, user);
        cout << "\n________________________________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n________________________________________________________________________________________________________\n" << endl;
        if (vec_users.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
            for (cls_bank_user user : vec_users)
            {
                cout << "| " << setw(12) << left << user.user_name;
                cout << "| " << setw(25) << left << user.full_name();
                cout << "| " << setw(12) << left << user.phone;
                cout << "| " << setw(20) << left << user.email;
                cout << "| " << setw(10) << left << user.password;
                cout << "| " << setw(12) << left << user.permissions << endl;
            }
        cout << "\n________________________________________________________________________________________________________\n" << endl;
    }
};