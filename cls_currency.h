#pragma once

#include<iostream>
#include<string>
#include "cls_string.h"
#include <vector>
#include <fstream>

class cls_currency
{
private:
	enum en_mode { empty_mode, update_mode };
	en_mode _mode;
	string _country, _currency_code, _currency_name;
	float _rate;

	static void _load_data_from_file_to_vector(string file_name, vector <string>& vec_file_content)
	{
		fstream my_file;
		my_file.open(file_name, ios::in);
		if (my_file.is_open())
		{
			string line;
			while (getline(my_file, line))
				vec_file_content.push_back(line);
		}
		my_file.close();
	}

	static cls_currency _convert_line_to_currency_object(string line, string separator)
	{
		vector <string> vec_currency_data;
		vec_currency_data = cls_string::split(line, separator);
		return cls_currency(en_mode::update_mode, vec_currency_data[0], vec_currency_data[1], vec_currency_data[2], stof(vec_currency_data[3]));
	}

	static string _convert_currency_object_to_line(cls_currency currency, string separator)
	{
		string currency_record;
		currency_record += currency.country + separator;
		currency_record += currency.currency_code + separator;
		currency_record += currency.currency_name + separator;
		currency_record += to_string(currency.rate);
		return currency_record;
	}

	static void _save_vector_to_file(string file_name, vector <string>& vec_file_content)
	{
		fstream my_file;
		my_file.open(file_name, ios::out);
		if (my_file.is_open())
		{
			for (string& line : vec_file_content)
				if (line != "")
					my_file << line << endl;
		}
		my_file.close();
	}

	static cls_currency _get_empty_currency_object()
	{
		return cls_currency(en_mode::empty_mode, "", "", "", 0);
	}

public:
	cls_currency(en_mode mode, string country, string currency_code, string currency_name, float rate)
	{
		_mode = mode;
		_country = country;
		_currency_code = currency_code;
		_currency_name = currency_name;
		_rate = rate;
	}

	static vector <cls_currency> load_data_from_file_to_currency_vector(string currencies_file, string separator)
	{
		vector <string> vec_currencies_lines;
		vector <cls_currency> vec_currencies_data;
		_load_data_from_file_to_vector(currencies_file, vec_currencies_lines);
		for (string& currency_line : vec_currencies_lines)
			vec_currencies_data.push_back(_convert_line_to_currency_object(currency_line, separator));
		return vec_currencies_data;
	}

	bool is_empty()
	{
		return (_mode == en_mode::empty_mode);
	}

	string get_country()
	{
		return _country;
	}

	__declspec(property(get = get_country)) string country;

	string get_currency_code()
	{
		return _currency_code;
	}

	__declspec(property(get = get_currency_code)) string currency_code;

	string get_currency_name()
	{
		return _currency_name;
	}

	__declspec(property(get = get_currency_name)) string currency_name;

	void set_rate(float rate)
	{
		_rate = rate;
	}

	float get_rate()
	{
		return _rate;
	}

	__declspec(property(put = set_rate, get = get_rate)) float rate;

	static void save_currency_vector_to_file(string currencies_file, string separator, vector <cls_currency>& vec_currencies_data)
	{
		vector <string> vec_currencies_lines;
		for (cls_currency& currency_data : vec_currencies_data)
			vec_currencies_lines.push_back(_convert_currency_object_to_line(currency_data, separator));
		_save_vector_to_file(currencies_file, vec_currencies_lines);
	}

	static cls_currency find_by_code(string currency_code, string currencies_file, string separator)
	{
		vector <cls_currency> vec_currencies_data = load_data_from_file_to_currency_vector(currencies_file, separator);
		for (cls_currency& currency_data : vec_currencies_data)
			if (currency_data.currency_code == cls_string::upper_all_string(currency_code)) return currency_data;
		return _get_empty_currency_object();
	}

	static cls_currency find_by_country(string country, string currencies_file, string separator)
	{
		vector <cls_currency> vec_currencies_data = load_data_from_file_to_currency_vector(currencies_file, separator);
		for (cls_currency& currency_data : vec_currencies_data)
			if (cls_string::upper_all_string(currency_data.country) == cls_string::upper_all_string(country)) return currency_data;
		return _get_empty_currency_object();
	}

	static bool is_currency_exist(string currency_code, string currencies_file, string separator)
	{
		cls_currency currency = cls_currency::find_by_code(currency_code, currencies_file, separator);
		return !(currency.is_empty());
	}

	static vector <cls_currency> get_currencies_list(string currencies_file, string separator)
	{
		return load_data_from_file_to_currency_vector(currencies_file, separator);
	}

	void update_rate(float new_rate, string currencies_file, string separator)
	{
		vector <string> vec_currencies_lines;
		_load_data_from_file_to_vector(currencies_file, vec_currencies_lines);
		for (string& currency_line : vec_currencies_lines)
		{
			cls_currency currency = _convert_line_to_currency_object(currency_line, separator);
			if (currency.currency_code == currency_code)
			{
				this->rate = new_rate;
				currency_line = _convert_currency_object_to_line(*this, separator);
				break;
			}
		}
		_save_vector_to_file(currencies_file, vec_currencies_lines);
	}
};