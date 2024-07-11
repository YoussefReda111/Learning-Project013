#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include "cls_input_validate.h"
#include "cls_date.h"

class cls_transfer_screen : protected cls_screen
{
private:
	static void _print_client(cls_bank_client client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << client.full_name();
		cout << "\nAcc. Number : " << client.account_number;
		cout << "\nBalance     : " << client.account_balance;
		cout << "\n___________________\n";
	}

	static cls_bank_client _get_client_data(string clients_file, string separator)
	{
		string account_number = cls_input_validate::read_string();
		while (!cls_bank_client::is_user_exist(account_number, clients_file, separator))
		{
			cout << "\nAccount number is not found, choose another one: ";
			account_number = cls_input_validate::read_string();
		}
		cls_bank_client client = cls_bank_client::find(account_number, clients_file, separator);
		_print_client(client);
		return client;
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

	static void _update_line_in_file(string file_name, string line, string update_to)
	{
		vector <string> vec_file_content;
		_load_data_from_file_to_vector(file_name, vec_file_content);
		for (string& file_line : vec_file_content)
			if (file_line == line)
				file_line = update_to;
		_save_vector_to_file(file_name, vec_file_content);
	}

	static void _add_line_to_file(string file_name, string line)
	{
		fstream my_file;
		my_file.open(file_name, ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << line << endl;
			my_file.close();
		}
	}
	
	static void _transfer(string clients_file, string separator, cls_bank_client& transfer_from_client, cls_bank_client& transfer_to_client, float transfer_amount)
	{
		string transfer_from_client_string = _convert_client_object_to_line(transfer_from_client, separator);
		string transfer_to_client_string = _convert_client_object_to_line(transfer_to_client, separator);
		transfer_from_client.account_balance -= transfer_amount;
		transfer_to_client.account_balance += transfer_amount;
		string new_transfer_from_client_string = _convert_client_object_to_line(transfer_from_client, separator);
		string new_transfer_to_client_string = _convert_client_object_to_line(transfer_to_client, separator);
		_update_line_in_file(clients_file, transfer_from_client_string, new_transfer_from_client_string);
		_update_line_in_file(clients_file, transfer_to_client_string, new_transfer_to_client_string);
	}

	static string _get_transfer_record(cls_bank_client transfer_from_client, cls_bank_client transfer_to_client, float transfer_amount, cls_bank_user user, string separator)
	{
		string transfer_record;
		string date = cls_date::from_date_to_string(cls_date::get_system_date());
		string time = cls_date::get_system_time_string();
		transfer_record += date + " - " + time + separator;
		transfer_record += transfer_from_client.account_number + separator;
		transfer_record += transfer_to_client.account_number + separator;
		transfer_record += to_string(transfer_amount) + separator;
		transfer_record += to_string(transfer_from_client.account_balance) + separator;
		transfer_record += to_string(transfer_to_client.account_balance) + separator;
		transfer_record += user.user_name;
		return transfer_record;
	}

public:
	static void transfer(string clients_file, string transfers_file, string separator, cls_bank_user user)
	{
		_draw_screen_header("\t    Transfer Screen", "", user);
		cout << "\nPlease, Enter Account Number to transfer from: ";
		cls_bank_client transfer_from_client = _get_client_data(clients_file, separator);
		cout << "\nPlease, Enter Account Number to transfer to: ";
		cls_bank_client transfer_to_client = _get_client_data(clients_file, separator);
		if (transfer_to_client.account_number == transfer_from_client.account_number)
		{
			cout << "\nYou cannot trasnfer money between the same client account.\n";
			return;
		}
		float transfer_amount;
		cout << "\nEnter Transfer Amount: ";
		cin >> transfer_amount;
		while (transfer_amount > transfer_from_client.account_balance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount: ";
			cin >> transfer_amount;
		}
		while (transfer_amount <= 0)
		{
			cout << "\nAmount is invalid, Enter a positive one: ";
			cin >> transfer_amount;
		}
		char answer;
		cout << "\nAre you sure you want t perform this opration? (Y/N)? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			_transfer(clients_file, separator, transfer_from_client, transfer_to_client, transfer_amount);
			string transfer_record = _get_transfer_record(transfer_from_client, transfer_to_client, transfer_amount, user, separator);
			_add_line_to_file(transfers_file, transfer_record);
			cout << "\nTransfer done successfully.\n";
		}
		else cout << "\nTransfer has not done.\n";
		_print_client(transfer_from_client);
		_print_client(transfer_to_client);
	}
};