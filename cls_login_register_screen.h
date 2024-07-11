#pragma once

#include "cls_screen.h"
#include "cls_bank_user.h"
#include "cls_string.h"

class cls_login_register_screen : protected cls_screen
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

	static cls_bank_user::st_login_register _get_login_register_list(string login_line, string separator)
	{
		vector <string> vec_login_record = cls_string::split(login_line, separator);
		cls_bank_user::st_login_register login_record;
		login_record.date_and_time = vec_login_record[0];
		login_record.user_name = vec_login_record[1];
		login_record.password = vec_login_record[2];
		login_record.permissions = vec_login_record[3];
		return login_record;
	}

public:
	static void login_register(string logins_file, string separator, cls_bank_user user)
	{
		vector <string> vec_logins;
		_load_data_from_file_to_vector(logins_file, vec_logins);
		string title = "\tLogin Register List Screen";
		string sub_title = "\t     (" + to_string(vec_logins.size()) + ") Record(s).";
		_draw_screen_header(title, sub_title, user);
		cout << "\n________________________________________________________________________________________________\n" << endl;
		cout << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << "\n________________________________________________________________________________________________\n" << endl;
		if (vec_logins.size() == 0)
			cout << "\t\t\t\tNo Logins Available In the System!";
		else
		{
			for (string& login_line : vec_logins)
			{
				cls_bank_user::st_login_register login_record = _get_login_register_list(login_line, separator);
				cout << "| " << setw(35) << left << login_record.date_and_time;
				cout << "| " << setw(20) << left << login_record.user_name;
				cout << "| " << setw(20) << left << login_record.password;
				cout << "| " << setw(10) << left << login_record.permissions << endl;
			}
			cout << "\n________________________________________________________________________________________________\n" << endl;
		}
	}
};