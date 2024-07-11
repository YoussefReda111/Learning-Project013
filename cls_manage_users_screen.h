#pragma once

#include "cls_screen.h"
#include "cls_users_list_screen.h"
#include "cls_add_user_screen.h"
#include "cls_delete_user_screen.h"
#include "cls_update_user_screen.h"
#include "cls_bank_user.h"
#include "cls_find_user_screen.h"

class cls_manage_users_screen : protected cls_screen
{
private:
	enum en_manage_users_options
	{
		en_list_users = 1,
		en_add_new_user,
		en_delete_user,
		en_update_user,
		en_find_user
	};

	static void _read_manage_users_menue_option(short& option_number)
	{
		cout << "\nChoose what do you want to do? [1 to 6]? ";
		cin >> option_number;
	}

    static void _show_users_list(string users_file, string separator, cls_bank_user user)
    {
		cls_users_list_screen::show_users_list(users_file, separator, user);
    }

    static void _add_new_user(string users_file, string separator, cls_bank_user user)
    {
		cls_add_user_screen::add_user(users_file, separator, user);
    }

    static void _delete_users(string users_file, string separator, cls_bank_user user)
    {
		cls_delete_user_screen::delete_user(users_file, separator, user);
    }

    static void _update_users(string users_file, string separator, cls_bank_user user)
    {
		cls_update_user_screen::update_user(users_file, separator, user);
    }

    static void _find_user(string users_file, string separator, cls_bank_user user)
    {
		cls_find_user_screen::find_user(users_file, separator, user);
    }

	static void _show_manage_users_screen()
	{
		cout << "==============================================================";
		cout << "\n\t\t\tManage Users Screen";
		cout << "\n==============================================================";
		cout << "\n\t[1] List Users.";
		cout << "\n\t[2] Add New User.";
		cout << "\n\t[3] Delete User.";
		cout << "\n\t[4] Update User.";
		cout << "\n\t[5] Find User.";
		cout << "\n\t[6] Main Menue.";
		cout << "\n==============================================================";
	}

public:
    static void manage_users(string users_file, string separator, cls_bank_user user)
	{
		short option_number;
		do
		{
			_draw_screen_header("\t Manage Users Screen", "", user);
			_show_manage_users_screen();
			_read_manage_users_menue_option(option_number);
			system("cls");
			if (option_number >= 1 && option_number <= 5)
			{
				switch (option_number)
				{
				case en_manage_users_options::en_list_users: _show_users_list(users_file, separator, user); break;
				case en_manage_users_options::en_add_new_user: _add_new_user(users_file, separator, user); break;
				case en_manage_users_options::en_delete_user: _delete_users(users_file, separator, user); break;
				case en_manage_users_options::en_update_user: _update_users(users_file, separator, user); break;
				case en_manage_users_options::en_find_user: _find_user(users_file, separator, user);
				}
				cout << "\nPress any key to go back to manage users screen...";
				system("pause>0");
				system("cls");
			}
		} while (option_number != 6);
	}
};