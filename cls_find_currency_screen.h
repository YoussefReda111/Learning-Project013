#pragma once

#include "cls_screen.h"
#include "cls_currency.h"

class cls_find_currency_screen : protected cls_screen
{
private:
    static void _print_currency(cls_currency currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "\n_____________________________\n";
        cout << "\nCountry    : " << currency.country;
        cout << "\nCode       : " << currency.currency_code;
        cout << "\nName       : " << currency.currency_name;
        cout << "\nRate(1$) = : " << currency.rate;
        cout << "\n_____________________________\n";
    }

    static void _show_results(cls_currency currency)
    {
        if (!currency.is_empty())
        {
            cout << "\nCurrency Found :-)\n";
            _print_currency(currency);
        }
        else cout << "\nCurrency Was not Found :-(\n";
    }

public:
    static void find_currency(string currencies_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t  Find Currency Screen", "", user);
        short answer;
        cout << "\nFind By: [1] Code or [2] Country ? ";
        cin >> answer;
        while (answer != 1 && answer != 2)
        {
            cout << "\nInvalid input, Enter valid one: ";
            cin >> answer;
        }
        if (answer == 1)
        {
            cout << "\nPlease, Enter currency code: ";
            string currency_code = cls_input_validate::read_string();
            cls_currency currency = cls_currency::find_by_code(currency_code, currencies_file, separator);
            _show_results(currency);
        }
        else
        {
            cout << "\nPlease, Enter country: ";
            string country = cls_input_validate::read_string();
            cls_currency currency = cls_currency::find_by_country(country, currencies_file, separator);
            _show_results(currency);
        }
    }
};