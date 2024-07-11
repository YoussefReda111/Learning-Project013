#pragma once

#include <vector>
#include "cls_person.h"
#include "cls_string.h"
#include <fstream>
#include "cls_utility.h"

class cls_bank_user : public cls_person
{
private:
	enum en_mode
	{
		empty_mode, update_mode, add_mode, delete_mode
	};
	en_mode _mode;
	string _user_name, _password;
	short _permissions;

	static cls_bank_user _convert_line_to_user_object(string line, string separator)
	{
		vector <string> vec_user_data;
		vec_user_data = cls_string::split(line, separator);
		return cls_bank_user(en_mode::update_mode, vec_user_data[0], vec_user_data[1], vec_user_data[2], vec_user_data[3], vec_user_data[4], cls_utility::decrypt_string(vec_user_data[5], 10), stoi(vec_user_data[6]));
	}

	static string _convert_user_object_to_line(cls_bank_user user, string separator)
	{
		string user_line;
		user_line += user.first_name + separator;
		user_line += user.last_name + separator;
		user_line += user.email + separator;
		user_line += user.phone + separator;
		user_line += user.user_name + separator;
		user_line += cls_utility::encrypt_string(user.password, 10) + separator;
		user_line += to_string(user.permissions);
		return user_line;
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

	void _update(string users_file, string separator)
	{
		vector <string> vec_users_lines;
		_load_data_from_file_to_vector(users_file, vec_users_lines);
		for (string& user_line : vec_users_lines)
		{
			cls_bank_user user = _convert_line_to_user_object(user_line, separator);
			if (user.user_name == user_name)
			{
				user_line = _convert_user_object_to_line(*this, separator);
				break;
			}
		}
		_save_vector_to_file(users_file, vec_users_lines);
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

	void _add(string users_file, string separator)
	{
		_add_line_to_file(users_file, _convert_user_object_to_line(*this, separator));
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

	void _delete(string users_file, string separator)
	{
		vector <string> vec_users_lines;
		_load_data_from_file_to_vector(users_file, vec_users_lines);
		for (string& user_line : vec_users_lines)
		{
			cls_bank_user user = _convert_line_to_user_object(user_line, separator);
			if (user.user_name == user_name)
			{
				_delete_record_from_file(users_file, user_line);
				*this = get_empty_user_object();
				break;
			}
		}
	}

public:
	static const short SHOW_CLIENTS_LIST = 0b000000001
		, ADD_NEW_CLIENT = 0b000000010
		, DELETE_CLIENT = 0b000000100
		, UPDATE_CLIENT = 0b000001000
		, FIND_CLIENT = 0b000010000
		, TRANSACTIONS = 0b000100000
		, MANAGE_USERS = 0b001000000
		, LOGIN_REGISTER = 0b010000000
		, CURRENCY_EXCHANGE = 0b100000000;

	struct st_login_register
	{
		string date_and_time, user_name, password, permissions;
	};

	cls_bank_user(en_mode mode, string first_name, string last_name, string email, string phone, string user_name, string password, short permissions)
		: cls_person(first_name, last_name, email, phone)
	{
		_mode = mode;
		_user_name = user_name;
		_password = password;
		_permissions = permissions;
	}

	static cls_bank_user get_empty_user_object()
	{
		return cls_bank_user(en_mode::empty_mode, "", "", "", "", "", "", 0);
	}

	bool is_empty()
	{
		return (_mode == en_mode::empty_mode);
	}

	string get_user_name()
	{
		return _user_name;
	}

	void set_user_name(string user_name)
	{
		_user_name = user_name;
	}

	__declspec(property(get = get_user_name, put = set_user_name)) string user_name;

	string get_password()
	{
		return _password;
	}

	void set_password(string password)
	{
		_password = password;
	}

	__declspec(property(get = get_password, put = set_password)) string password;

	short get_permissions()
	{
		return _permissions;
	}

	void set_permissions(short permissions)
	{
		_permissions = permissions;
	}

	__declspec(property(get = get_permissions, put = set_permissions)) short permissions;

	static cls_bank_user find(string user_name, string users_file, string separator)
	{
		vector <string> vec_users_lines;
		_load_data_from_file_to_vector(users_file, vec_users_lines);
		for (string& user_line : vec_users_lines)
		{
			cls_bank_user user = _convert_line_to_user_object(user_line, separator);
			if (user.user_name == user_name) return user;
		}
		return get_empty_user_object();
	}

	static cls_bank_user find(string user_name, string password, string users_file, string separator)
	{
		vector <string> vec_users_lines;
		_load_data_from_file_to_vector(users_file, vec_users_lines);
		for (string& user_line : vec_users_lines)
		{
			cls_bank_user user = _convert_line_to_user_object(user_line, separator);
			if (user.user_name == user_name && user.password == password) return user;
		}
		return get_empty_user_object();
	}

	enum en_saving_results
	{
		failed_empty_object, succeeded, failed_user_name_exist
	};

	static bool is_user_exist(string user_name, string users_file, string separator)
	{
		cls_bank_user user = cls_bank_user::find(user_name, users_file, separator);
		return !(user.is_empty());
	}

	en_saving_results save(string users_file, string separator)
	{
		switch (_mode)
		{
		case en_mode::empty_mode:
			return en_saving_results::failed_empty_object;
		case en_mode::update_mode:
			_update(users_file, separator);
			return en_saving_results::succeeded;
		case en_mode::add_mode:
			if (is_user_exist(_user_name, users_file, separator))
				return en_saving_results::failed_user_name_exist;
			else
			{
				_add(users_file, separator);
				_mode = en_mode::update_mode;
				return en_saving_results::succeeded;
			}
		case en_mode::delete_mode:
			_delete(users_file, separator);
			_mode = en_mode::update_mode;
			return en_saving_results::succeeded;
		}
	}

	void get_delete_user_object()
	{
		_mode = en_mode::delete_mode;
	}

	static cls_bank_user get_add_user_object(string user_name)
	{
		return cls_bank_user(en_mode::add_mode, "", "", "", "", user_name, "", 0);
	}

	static vector <cls_bank_user> get_users_list(string users_file, string separator)
	{
		vector <string> vec_users_lines;
		vector <cls_bank_user> vec_users;
		_load_data_from_file_to_vector(users_file, vec_users_lines);
		for (string& user_line : vec_users_lines)
			vec_users.push_back(_convert_line_to_user_object(user_line, separator));
		return vec_users;
	}
};