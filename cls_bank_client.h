#pragma once

#include <iostream>
#include <string>
#include "cls_person.h"
#include "cls_string.h"
#include <vector>
#include <fstream>

class cls_bank_client : public cls_person
{
private:
	enum en_mode
	{
		empty_mode, update_mode, add_mode, delete_mode
	};
	en_mode _mode;
	string _account_number, _PIN_code;
	float _account_balance;

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

	static cls_bank_client _convert_line_to_client_object(string line, string separator)
	{
		vector <string> vec_client_data;
		vec_client_data = cls_string::split(line, separator);
		return cls_bank_client(en_mode::update_mode, vec_client_data[0], vec_client_data[1], vec_client_data[2], vec_client_data[3], vec_client_data[4], vec_client_data[5], stof(vec_client_data[6]));
	}

	static string _convert_client_object_to_line(cls_bank_client client, string separator)
	{
		string client_line;
		client_line += client.first_name + separator;
		client_line += client.last_name + separator;
		client_line += client.email + separator;
		client_line += client.phone + separator;
		client_line += client.account_number + separator;
		client_line += client.PIN_code + separator;
		client_line += to_string(client.account_balance);
		return client_line;
	}

	static cls_bank_client get_empty_user_object()
	{
		return cls_bank_client(en_mode::empty_mode, "", "", "", "", "", "", 0);
	}

	void _save_vector_to_file(string file_name, vector <string>& vec_file_content)
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

	void _update_line_in_file(string file_name, string line, string update_to)
	{
		vector <string> vec_file_content;
		_load_data_from_file_to_vector(file_name, vec_file_content);
		for (string& file_line : vec_file_content)
			if (file_line == line)
				file_line = update_to;
		_save_vector_to_file(file_name, vec_file_content);
	}

	void _update(string clients_file, string separator)
	{
		vector <string> vec_clients_lines;
		_load_data_from_file_to_vector(clients_file, vec_clients_lines);
		for (string& client_line : vec_clients_lines)
		{
			cls_bank_client client = _convert_line_to_client_object(client_line, separator);
			if (client.account_number == account_number)
			{
				client_line = _convert_client_object_to_line(*this, separator);
				break;
			}
		}
		_save_vector_to_file(clients_file, vec_clients_lines);
	}

	void _add_line_to_file(string file_name, string line)
	{
		fstream my_file;
		my_file.open(file_name, ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << line << endl;
			my_file.close();
		}
	}

	void _add(string clients_file, string separator)
	{
		_add_line_to_file(clients_file, _convert_client_object_to_line(*this, separator));
	}

	void _delete_record_from_file(string file_name, string record)
	{
		vector <string> vec_file_content;
		_load_data_from_file_to_vector(file_name, vec_file_content);
		for (string& line : vec_file_content)
			if (line == record)
				line = "";
		_save_vector_to_file(file_name, vec_file_content);
	}

	void _delete(string clients_file, string separator)
	{
		vector <string> vec_clients_lines;
		_load_data_from_file_to_vector(clients_file, vec_clients_lines);
		for (string& client_line : vec_clients_lines)
		{
			cls_bank_client client = _convert_line_to_client_object(client_line, separator);
			if (client.account_number == _account_number)
			{
				_delete_record_from_file(clients_file, client_line);
				*this = get_empty_user_object();
				break;
			}
		}
	}

public:
	cls_bank_client(en_mode mode, string first_name, string last_name, string email, string phone, string account_number, string PIN_code, float account_balance)
		: cls_person(first_name, last_name, email, phone)
	{
		_mode = mode;
		_account_number = account_number;
		_PIN_code = PIN_code;
		_account_balance = account_balance;
	}

	struct st_transfers_log
	{
		string date_and_time,
		from_client_acc_number,
		to_client_acc_number,
		transfer_amount,
		from_client_acc_balance,
		to_client_acc_balance,
		user_name;
	};

	bool is_empty()
	{
		return (_mode == en_mode::empty_mode);
	}

	string get_account_number()
	{
		return _account_number;
	}

	__declspec(property(get = get_account_number)) string account_number;

	void set_PIN_code(string PIN_code)
	{
		_PIN_code = PIN_code;
	}

	string get_PIN_code()
	{
		return _PIN_code;
	}

	__declspec(property(get = get_PIN_code, put = set_PIN_code)) string PIN_code;

	void set_account_balance(float account_balance)
	{
		_account_balance = account_balance;
	}

	float get_account_balance()
	{
		return _account_balance;
	}

	__declspec(property(get = get_account_balance, put = set_account_balance)) float account_balance;

	static cls_bank_client find(string account_number, string clients_file, string separator)
	{
		vector <string> vec_clients_lines;
		_load_data_from_file_to_vector(clients_file, vec_clients_lines);
		for (string& client_line : vec_clients_lines)
		{
			cls_bank_client client = _convert_line_to_client_object(client_line, separator);
			if (client.account_number == account_number)
				return client;
		}
		return get_empty_user_object();
	}

	static cls_bank_client find(string account_number, string PIN_code, string clients_file, string separator)
	{
		vector <string> vec_clients_lines;
		_load_data_from_file_to_vector(clients_file, vec_clients_lines);
		for (string& client_line : vec_clients_lines)
		{
			cls_bank_client client = _convert_line_to_client_object(client_line, separator);
			if (client.account_number == account_number && client.PIN_code == PIN_code)
				return client;
		}
		return get_empty_user_object();
	}

	static bool is_user_exist(string account_number, string clients_file, string separator)
	{
		cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
		return !(client.is_empty());
	}

	enum en_saving_results
	{
		failed_empty_object, succeeded, failed_account_number_exist
	};

	en_saving_results save(string clients_file, string separator)
	{
		switch (_mode)
		{
		case en_mode::empty_mode:
			return en_saving_results::failed_empty_object;
		case en_mode::update_mode:
			_update(clients_file, separator);
			return en_saving_results::succeeded;
		case en_mode::add_mode:
			if (is_user_exist(_account_number, clients_file, separator))
				return en_saving_results::failed_account_number_exist;
			else
			{
				_add(clients_file, separator);
				_mode = en_mode::update_mode;
				return en_saving_results::succeeded;
			}
		case en_mode::delete_mode:
			_delete(clients_file, separator);
			_mode = en_mode::update_mode;
			return en_saving_results::succeeded;
		}
	}

	static cls_bank_client get_add_user_object(string account_number)
	{
		return cls_bank_client(en_mode::add_mode, "", "", "", "", account_number, "", 0);
	}

	void get_delete_user_object()
	{
		_mode = en_mode::delete_mode;
	}

	static vector <cls_bank_client> get_users_list(string clients_file, string separator)
	{
		vector <string> vec_clients_lines;
		vector <cls_bank_client> vec_clients;
		_load_data_from_file_to_vector(clients_file, vec_clients_lines);
		for (string& client_line : vec_clients_lines)
			vec_clients.push_back(_convert_line_to_client_object(client_line, separator));
		return vec_clients;
	}

	static float get_total_balances(string clients_file, string separator)
	{
		vector <cls_bank_client> vec_clients_data = cls_bank_client::get_users_list(clients_file, separator);
		float total_balances = 0;
		for (cls_bank_client& client_data : vec_clients_data)
		{
			total_balances += client_data.account_balance;
		}
		return total_balances;
	}
};