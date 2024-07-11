#pragma once

#include <iostream>
#include "cls_bank_user.h"
#include "cls_date.h"

using namespace std;

class cls_screen
{
protected:
    static void _draw_screen_header(string title, string sub_title = "", cls_bank_user user = cls_bank_user::get_empty_user_object())
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;
        if (sub_title != "")
        {
            cout << "\n\t\t\t\t\t  " << sub_title;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tUser: " << user.user_name;
        cout << "\n\t\t\t\t\tDate: " << cls_date::from_date_to_string(cls_date::get_system_date()) << "\n\n";
    }
};