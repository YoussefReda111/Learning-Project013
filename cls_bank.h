#pragma once

#include "cls_main_screen.h"
#include "cls_login_screen.h"

class cls_bank
{
public:
	static void bank_program(string clients_file, string users_file, string logins_file, string transfers_file, string currencies_file, string separator)
	{
		do
		{
			cls_bank_user user = cls_bank_user::get_empty_user_object();
			if (cls_login_screen::login(users_file, separator, user, logins_file)) return;
			else
			{
				system("cls");
				cls_main_screen::main_menue(clients_file, users_file, logins_file, transfers_file, currencies_file, separator, user);
			}
		} while (true);
	}
};