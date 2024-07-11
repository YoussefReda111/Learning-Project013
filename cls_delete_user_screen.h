#pragma once

#include "cls_bank_user.h"
#include "cls_screen.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"

class cls_delete_user_screen : protected cls_screen
{
private:
    static void _print_user(cls_bank_user user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.first_name;
        cout << "\nLastName    : " << user.last_name;
        cout << "\nFull Name   : " << user.full_name();
        cout << "\nEmail       : " << user.email;
        cout << "\nPhone       : " << user.phone;
        cout << "\nUser Name   : " << user.user_name;
        cout << "\nPassword    : " << user.password;
        cout << "\nPermissions : " << user.permissions;
        cout << "\n___________________\n";
    }

public:
    static void delete_user(string users_file, string separator, cls_bank_user logined_user)
    {
        _draw_screen_header("\tDelete User Screen", "", logined_user);
        string user_name;
        cout << "\nPlease Enter UserName: ";
        user_name = cls_input_validate::read_string();
        while (!cls_bank_user::is_user_exist(user_name, users_file, separator))
        {
            cout << "\nUser is not found, choose another one: ";
            user_name = cls_input_validate::read_string();
        }
        cls_bank_user user = cls_bank_user::find(user_name, users_file, separator);
        _print_user(user);
        cout << "\nAre you sure you want to delete this User y/n? ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            cout << "\nUser Deleted Successfully :-)\n";
            user.get_delete_user_object();
            user.save(users_file, separator);
            _print_user(user);
        }
        else cout << "\nUser Was not Deleted\n";
    }
};