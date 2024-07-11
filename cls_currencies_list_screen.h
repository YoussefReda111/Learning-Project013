#pragma once

#include "cls_screen.h"
#include "cls_currency.h"

class cls_currencies_list_screen : protected cls_screen
{
public:
    static void currencies_list(string currencies_file, string separator, cls_bank_user user)
    {
        vector <cls_currency> vec_currencies = cls_currency::get_currencies_list(currencies_file, separator);
        string title = "\t  Currencies List Screen";
        string sub_title = "\t    (" + to_string(vec_currencies.size()) + ") Currency.";
        _draw_screen_header(title, sub_title, user);
        cout << "\n______________________________________________________________________________________________________\n" << endl;
        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << "\n______________________________________________________________________________________________________\n" << endl;
        if (vec_currencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else
            for (cls_currency currency : vec_currencies)
            {
                cout << "| " << setw(30) << left << currency.country;
                cout << "| " << setw(8) << left << currency.currency_code;
                cout << "| " << setw(45) << left << currency.currency_name;
                cout << "| " << setw(10) << left << currency.rate << endl;
            }
        cout << "\n______________________________________________________________________________________________________\n" << endl;
    }
};