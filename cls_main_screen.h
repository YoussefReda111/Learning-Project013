#pragma once

#include <iostream>
#include "cls_screen.h"
#include "cls_input_validate.h"
#include "cls_client_list_screen.h"
#include <iomanip>
#include "cls_add_client_screen.h"
#include "cls_delete_client_screen.h"
#include "cls_update_client_screen.h"
#include "cls_find_client_screen.h"
#include "cls_transactions_screen.h"
#include "cls_manage_users_screen.h"
#include "cls_login_register_screen.h"
#include "cls_currency_exchange_screen.h"

using namespace std;

class cls_main_screen : protected cls_screen
{
private:
	enum en_main_menue_options
	{
		en_list_clients = 1,
		en_add_new_client,
		en_delete_client,
		en_update_client,
		en_find_client,
		en_transactions,
		en_manage_users,
		en_login_register,
		en_currency_exchange
	};

	static void _read_main_menue_option(short& option_number)
	{
		cout << "\nChoose what do you want to do? [1 to 10]? ";
		cin >> option_number;
	}

	static void _show_main_menue()
	{
		cout << "==============================================================";
		cout << "\n\t\t\tMain Menue Screen";
		cout << "\n==============================================================";
		cout << "\n\t[1] Show Client List.";
		cout << "\n\t[2] Add New Client.";
		cout << "\n\t[3] Delete Client.";
		cout << "\n\t[4] Update Client Info.";
		cout << "\n\t[5] Find Client.";
		cout << "\n\t[6] Transactions.";
		cout << "\n\t[7] Manage Users.";
		cout << "\n\t[8] Login Register.";
		cout << "\n\t[9] Currency Exchange.";
		cout << "\n\t[10] Logout.";
		cout << "\n==============================================================";
	}

	static void _show_clients_list(string clients_file, string separator, cls_bank_user user)
	{
		cls_client_list_screen::show_clients_list(clients_file, separator, user);
	}

	static void _add_new_client(string clients_file, string separator, cls_bank_user user)
	{
		cls_add_client_screen::add_client(clients_file, separator, user);
	}

	static void _delete_client(string clients_file, string separator, cls_bank_user user)
	{
		cls_delete_client_screen::delete_client(clients_file, separator, user);
	}

	static void _update_client_info(string clients_file, string separator, cls_bank_user user)
	{
		cls_update_client_screen::update_client(clients_file, separator, user);
	}

	static void _find_client(string clients_file, string separator, cls_bank_user user)
	{
		cls_find_client_screen::find_client(clients_file, separator, user);
	}

	static void _transactions(string clients_file, string transfers_file, string separator, cls_bank_user user)
	{
		cls_transactions_screen::transactions(clients_file, transfers_file, separator, user);
	}

	static void _manage_users(string users_file, string separator, cls_bank_user user)
	{
		cls_manage_users_screen::manage_users(users_file, separator, user);
	}

	static void _login_register(string logins_file, string separator, cls_bank_user user)
	{
		cls_login_register_screen::login_register(logins_file, separator, user);
	}

	static void _currency_exchange(string currencies_file, string separator, cls_bank_user user)
	{
		cls_currency_exchange_screen::currency_exchange(currencies_file, separator, user);
	}

	static void _show_access_denied_message()
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
		cout << "\n\t\t\t\t\t______________________________________\n\n";
	}

public:
	static void main_menue(string clients_file, string users_file, string logins_file, string transfers_file, string currencies_file, string separator, cls_bank_user user)
	{
		short option_number;
		do
		{
			_draw_screen_header("\t\tMain Screen", "", user);
			_show_main_menue();
			_read_main_menue_option(option_number);
			system("cls");
			if ((option_number >= 1 && option_number <= 5) || option_number == 8)
			{
				switch (option_number)
				{
				case en_main_menue_options::en_list_clients:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::SHOW_CLIENTS_LIST))
						_show_clients_list(clients_file, separator, user);
					else _show_access_denied_message();
					break;
				case en_main_menue_options::en_add_new_client:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::ADD_NEW_CLIENT))
						_add_new_client(clients_file, separator, user);
					else _show_access_denied_message();
					break;
				case en_main_menue_options::en_delete_client:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::DELETE_CLIENT))
						_delete_client(clients_file, separator, user);
					else _show_access_denied_message();
					break;
				case en_main_menue_options::en_update_client:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::UPDATE_CLIENT))
						_update_client_info(clients_file, separator, user);
					else _show_access_denied_message();
					break;
				case en_main_menue_options::en_find_client:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::FIND_CLIENT))
						_find_client(clients_file, separator, user);
					else _show_access_denied_message();
					break;
				case en_main_menue_options::en_login_register:
					if (user.permissions == -1 || (user.permissions & cls_bank_user::LOGIN_REGISTER))
						_login_register(logins_file, separator, user);
					else _show_access_denied_message();
				}
				cout << "\nPress any key to go back to main menue...";
				system("pause>0");
				system("cls");
			}
			else if (option_number == en_main_menue_options::en_transactions)
			{
				if (user.permissions == -1 || (user.permissions & cls_bank_user::TRANSACTIONS))
					_transactions(clients_file, transfers_file, separator, user);
				else
				{
					_show_access_denied_message();
					cout << "\nPress any key to go back to main menue...";
					system("pause>0");
					system("cls");
				}
			}
			else if (option_number == en_main_menue_options::en_manage_users)
			{
				if (user.permissions == -1 || (user.permissions & cls_bank_user::MANAGE_USERS)) 
					_manage_users(users_file, separator, user);
				else
				{
					_show_access_denied_message();
					cout << "\nPress any key to go back to main menue...";
					system("pause>0");
					system("cls");
				}
			}
			else if (option_number == en_main_menue_options::en_currency_exchange)
			{
				if (user.permissions == -1 || (user.permissions & cls_bank_user::CURRENCY_EXCHANGE))
					_currency_exchange(currencies_file, separator, user);
				else
				{
					_show_access_denied_message();
					cout << "\nPress any key to go back to main menue...";
					system("pause>0");
					system("cls");
				}
			}
		} while (option_number != 10);
	}
};