#pragma once

#include "cls_screen.h"

class cls_currency_calculator_screen : protected cls_screen
{
private:
	static cls_currency _get_currency(string question_message, string currencies_file, string separator)
	{
		cout << question_message;
		string currency_code;
		cin >> currency_code;
		cls_currency currency = cls_currency::find_by_code(currency_code, currencies_file, separator);
		while (currency.is_empty())
		{
			cout << "\nCurrency Was not Found :-(\n";
			cout << "\nEnter another currency code: ";
			cin >> currency_code;
			currency = cls_currency::find_by_code(currency_code, currencies_file, separator);
		}
		return currency;
	}

	static void _print_currency(cls_currency currency)
	{
		cout << "\n_____________________________\n";
		cout << "\nCountry    : " << currency.country;
		cout << "\nCode       : " << currency.currency_code;
		cout << "\nName       : " << currency.currency_name;
		cout << "\nRate(1$) = : " << currency.rate;
		cout << "\n_____________________________\n";
	}

	static void _exchange_currency_amount_to_USD(float exchange_amount, cls_currency currency1)
	{
		cout << "\nConvert From:";
		_print_currency(currency1);
		float exchange_index = 1 / currency1.rate;
		cout << '\n' << exchange_amount << ' ' + currency1.currency_code + " = " << exchange_amount * exchange_index << " USD" << endl;
	}

	static void _exchange_currency_amount(float exchange_amount, cls_currency currency1, cls_currency currency2)
	{
		cout << "\nConverting From USD To:";
		_print_currency(currency2);
		float exchange_index = currency2.rate / currency1.rate;
		cout << '\n' << exchange_amount << ' ' + currency1.currency_code + " = " << exchange_amount * exchange_index << ' ' + currency2.currency_code << endl;
	}

public:
	static void currency_calculator(string currencies_file, string separator, cls_bank_user user)
	{
		char answer;
		do
		{
			system("cls");
			_draw_screen_header("\t  Currency Calculator", "", user);
			cls_currency currency1 = _get_currency("\nPlease, Enter Currency1 Code: ", currencies_file, separator);
			cls_currency currency2 = _get_currency("\nPlease, Enter Currency2 Code: ", currencies_file, separator);
			cout << "\nEnter Amount to Exchange: ";
			float exchange_amount;
			cin >> exchange_amount;
			_exchange_currency_amount_to_USD(exchange_amount, currency1);
			if (currency2.currency_code != "USD")
				_exchange_currency_amount(exchange_amount, currency1, currency2);
			cout << "\nDo you want to perform another calculation? y/n? ";
			cin >> answer;
		} while (answer == 'y' || answer == 'Y');
	}
};