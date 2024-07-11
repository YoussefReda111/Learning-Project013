#pragma once

#include "cls_screen.h"
#include "cls_bank_user.h"
#include "cls_date.h"

class cls_login_screen : protected cls_screen
{
private:
	static void _get_user_info(string users_file, string separator, cls_bank_user& user)
	{
		string user_name, password;
		cout << "\nEnter Username: ";
		cin >> user_name;
		cout << "Enter Password: ";
		cin >> password;
		user = cls_bank_user::find(user_name, password, users_file, separator);
	}

	static string _get_login_record(cls_bank_user user, string separator)
	{
		string login_record;
		string date = cls_date::from_date_to_string(cls_date::get_system_date());
		string time = cls_date::get_system_time_string();
		login_record += date + " - " + time + separator;
		login_record += user.user_name + separator;
		login_record += user.password + separator;
		login_record += to_string(user.permissions);
		return login_record;
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

public:
	static bool login(string users_file, string separator, cls_bank_user& user, string logins_file)
	{
		_draw_screen_header("\t     Login Screen", "", user);
		_get_user_info(users_file, separator, user);
		short login_counter = 3;
		bool is_locked;
		while (user.is_empty())
		{
			cout << "\nInvlaid Username/Password!\n";
			login_counter--;
			cout << "You have " << login_counter << " Trials to login.\n\n";
			if (login_counter == 0)
			{
				cout << "\nYou Are Locked after 3 Failed Trials";
				return is_locked = true;
			}
			else _get_user_info(users_file, separator, user);
		}
		string login_record = _get_login_record(user, separator);
		_add_line_to_file(logins_file, login_record);
		return is_locked = false;
	}
};