#pragma once

#include "cls_bank_user.h"
#include "cls_screen.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"

class cls_find_user_screen : protected cls_screen
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
    static void find_user(string users_file, string separator, cls_bank_user logined_user)
    {
        _draw_screen_header("\t   Find User Screen", "", logined_user);
        string user_name;
        cout << "\nPlease Enter UserName: ";
        user_name = cls_input_validate::read_string();
        while (!cls_bank_user::is_user_exist(user_name, users_file, separator))
        {
            cout << "\nUser is not found, choose another one: ";
            user_name = cls_input_validate::read_string();
        }
        cls_bank_user user = cls_bank_user::find(user_name, users_file, separator);
        if (!user.is_empty()) cout << "\nUser Found :-)\n";
        else cout << "\nUser Was not Found :-(\n";
        _print_user(user);
    }
};