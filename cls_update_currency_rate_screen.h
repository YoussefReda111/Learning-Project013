#pragma once

#include "cls_screen.h"
#include "cls_currency.h"
#include "cls_input_validate.h"

class cls_update_currency_rate_screen : protected cls_screen
{
private:
	static float _read_rate()
	{
		cout << "\nEnter New Rate: ";
		float new_rate;
		new_rate = cls_input_validate::read_number<float>();
		return new_rate;
	}

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

public:
	static void update_rate(string currencies_file, string separator, cls_bank_user user)
	{
		_draw_screen_header("    Update Currency Rate Screen", "", user);
		cout << "\nPlease Enter Currency Code: ";
		string currency_code = cls_input_validate::read_string();
		while (!cls_currency::is_currency_exist(currency_code, currencies_file, separator))
		{
			cout << "\nCurrency is not found, choose another one: ";
			currency_code = cls_input_validate::read_string();
		}
		cls_currency currency = cls_currency::find_by_code(currency_code, currencies_file, separator);
		_print_currency(currency);
		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
		char answer;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";
			currency.update_rate(_read_rate(), currencies_file, separator);
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_print_currency(currency);
		}
		else cout << "\nCurrency Rate hasn't Updated :-(\n";
	}
};