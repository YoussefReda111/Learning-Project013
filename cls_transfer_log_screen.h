#pragma once

#include "cls_screen.h"
#include "cls_bank_client.h"
#include "cls_string.h"

class cls_transfer_log_screen : protected cls_screen
{
private:
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

	static cls_bank_client::st_transfers_log _get_transfer_log_list(string transfer_line, string separator)
	{
		vector <string> vec_transfer_record = cls_string::split(transfer_line, separator);
		cls_bank_client::st_transfers_log transfer_record;
		transfer_record.date_and_time = vec_transfer_record[0];
		transfer_record.from_client_acc_number = vec_transfer_record[1];
		transfer_record.to_client_acc_number = vec_transfer_record[2];
		transfer_record.transfer_amount = vec_transfer_record[3];
		transfer_record.from_client_acc_balance = vec_transfer_record[4];
		transfer_record.to_client_acc_balance = vec_transfer_record[5];
		transfer_record.user_name = vec_transfer_record[6];
		return transfer_record;
	}

public:
	static void transfer_log(string transfers_file, string separator, cls_bank_user user)
	{
		vector <string> vec_transfers;
		_load_data_from_file_to_vector(transfers_file, vec_transfers);
		string title = "\tTransfer Log List Screen";
		string sub_title = "\t    (" + to_string(vec_transfers.size()) + ") Record(s).";
		_draw_screen_header(title, sub_title, user);
		cout << "\n________________________________________________________________________________________________\n" << endl;
		cout << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(11) << "Amount";
		cout << "| " << left << setw(12) << "s.Balance";
		cout << "| " << left << setw(12) << "d.Balance";
		cout << "| " << left << setw(8) << "User";
		cout << "\n________________________________________________________________________________________________\n" << endl;
		if (vec_transfers.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else
			for (string& transfer_line : vec_transfers)
			{
				cls_bank_client::st_transfers_log transfer_record = _get_transfer_log_list(transfer_line, separator);
				cout << "| " << setw(23) << left << transfer_record.date_and_time;
				cout << "| " << setw(8) << left << transfer_record.from_client_acc_number;
				cout << "| " << setw(8) << left << transfer_record.to_client_acc_number;
				cout << "| " << setw(11) << left << transfer_record.transfer_amount;
				cout << "| " << setw(12) << left << transfer_record.from_client_acc_balance;
				cout << "| " << setw(12) << left << transfer_record.to_client_acc_balance;
				cout << "| " << setw(8) << left << transfer_record.user_name;
			}
		cout << "\n________________________________________________________________________________________________\n" << endl;
	}
};