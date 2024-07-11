#pragma once

#include "cls_string.h"
#include "cls_date.h"

class cls_input_validate
{
public:
	static double read_double()
	{
		double input;
		cin >> input;
		return input;
	}

	static string read_string()
	{
		string input;
		getline(cin >> ws, input);
		return input;
	}

	template <typename type> static bool is_number_between(type number, type from, type to)
	{
		if (number >= from && number <= to)
			return true;
		else
			return false;
	}

	static bool is_date_between(cls_date date, cls_date from, cls_date to)
	{
		if ((cls_date::is_date1_after_date2(date, from) || cls_date::is_date1_equal_date2(date, from))
			&&
			(cls_date::is_date1_before_date2(date, to) || cls_date::is_date1_equal_date2(date, to))
			)
		{
			return true;
		}
		if ((cls_date::is_date1_after_date2(date, to) || cls_date::is_date1_equal_date2(date, to))
			&&
			(cls_date::is_date1_before_date2(date, from) || cls_date::is_date1_equal_date2(date, from))
			)
		{
			return true;
		}
		return false;
	}

	template <typename type> static type read_number(string error_message = "Invalid Number, Enter again\n")
	{
		type number;
		while (!(cin >> number)) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << error_message;
		}
		return number;
	}

	template <typename type> static type read_number_between(type from, type to, string error_message = "Number is not within range, Enter again:\n")
	{
		type number = read_number();
		while (!is_number_between(number, from, to))
		{
			cout << error_message;
			number = read_number();
		}
		return number;
	}

	static bool is_valid_date(cls_date date)
	{
		return	cls_date::is_valid_date(date);
	}
};