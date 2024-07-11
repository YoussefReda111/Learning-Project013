#pragma once

#include "cls_screen.h"
#include "cls_bank_user.h"
#include "cls_currencies_list_screen.h"
#include "cls_find_currency_screen.h"
#include "cls_update_currency_rate_screen.h"
#include "cls_currency_calculator_screen.h"

class cls_currency_exchange_screen : protected cls_screen
{
private:
	enum en_currency_exchange_menue_options
	{
		list_currencies = 1,
		find_currency,
		update_rate,
		currency_calculator,
	};

	static void _read_currency_exchange_menue_option(short& option_number)
	{
		cout << "\nChoose what do you want to do? [1 to 5]? ";
		cin >> option_number;
	}

	static void _show_currency_exchange_menue()
	{
		cout << "===========================================\n";
		cout << "\t   Currency Exhange Menue\n";
		cout << "===========================================\n";
		cout << "\t[1] List Currencies.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Rate.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] Main Menue.\n";
		cout << "===========================================\n";
	}

	static void _show_currencies_list(string currencies_file, string separator, cls_bank_user user)
	{
		cls_currencies_list_screen::currencies_list(currencies_file, separator, user);
	}

	static void _find_currency(string currencies_file, string separator, cls_bank_user user)
	{
		cls_find_currency_screen::find_currency(currencies_file, separator, user);
	}

	static void _update_rate(string currencies_file, string separator, cls_bank_user user)
	{
		cls_update_currency_rate_screen::update_rate(currencies_file, separator, user);
	}

	static void _currency_calculator(string currencies_file, string separator, cls_bank_user user)
	{
		cls_currency_calculator_screen::currency_calculator(currencies_file, separator, user);
	}

public:
	static void currency_exchange(string currencies_file, string separator, cls_bank_user user)
	{
		short option_number;
		do
		{
			_draw_screen_header("    Currancy Exhange Main Screen", "", user);
			_show_currency_exchange_menue();
			_read_currency_exchange_menue_option(option_number);
			system("cls");
			if (option_number >= 1 && option_number <= 4)
			{
				switch (option_number)
				{
				case en_currency_exchange_menue_options::list_currencies:
					_show_currencies_list(currencies_file, separator, user); break;
				case en_currency_exchange_menue_options::find_currency:
					_find_currency(currencies_file, separator, user); break;
				case en_currency_exchange_menue_options::update_rate:
					_update_rate(currencies_file, separator, user); break;
				case en_currency_exchange_menue_options::currency_calculator:
					_currency_calculator(currencies_file, separator, user);
				}
				cout << "\nPress any key to go back to currency exchange menue...";
				system("pause>0");
				system("cls");
			}
		} while (option_number != 5);
	}
};