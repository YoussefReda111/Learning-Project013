#pragma once

#include "cls_screen.h"
#include "cls_deposit_screen.h"
#include "cls_withdraw_screen.h"
#include "cls_total_balances_screen.h"
#include "cls_bank_user.h"
#include "cls_transfer_screen.h"
#include "cls_transfer_log_screen.h"

class cls_transactions_screen : protected cls_screen
{
private:
	enum en_trans_menue_options
	{
		en_deposit = 1,
		en_withdraw,
		en_total_balances,
		en_transfer,
		en_transfer_log
	};

	static void _read_transactions_menue_options(short& option_number)
	{
		cout << "\nChoose what do you want to do? [1 to 6]? ";
		cin >> option_number;
	}

	static void _deposit(string clients_file, string separator, cls_bank_user user)
	{
		cls_deposit_screen::deposit(clients_file ,separator, user);
	}

	static void _withdraw(string clients_file, string separator, cls_bank_user user)
	{
		cls_withdraw_screen::withdraw(clients_file, separator, user);
	}

	static void _show_total_balances(string clients_file, string separator, cls_bank_user user)
	{
		cls_total_balances_screen::total_balances(clients_file, separator, user);
	}

	static void _transfer(string clients_file, string transfers_file, string separator, cls_bank_user user)
	{
		cls_transfer_screen::transfer(clients_file, transfers_file, separator, user);
	}

	static void _transfer_log(string transfers_file, string separator, cls_bank_user user)
	{
		cls_transfer_log_screen::transfer_log(transfers_file, separator, user);
	}

	static void _show_transactions_menue()
	{
		cout << "==============================================================";
		cout << "\n\t\tTransactions Menue Screen\t\t\t";
		cout << "\n==============================================================";
		cout << "\n\t[1] Deposit.";
		cout << "\n\t[2] Withdraw.";
		cout << "\n\t[3] Total Balances.";
		cout << "\n\t[4] Transfer.";
		cout << "\n\t[5] Transfer Log.";
		cout << "\n\t[6] Main Menue.";
		cout << "\n==============================================================";
	}

public:
	static void transactions(string clients_file, string transfers_file, string separator, cls_bank_user user)
	{
		short option_number;
		do
		{
			_draw_screen_header("\t Transactions Screen", "", user);
			_show_transactions_menue();
			_read_transactions_menue_options(option_number);
			system("cls");
			if (option_number >= 1 && option_number <= 5)
			{
				switch (option_number)
				{
				case en_trans_menue_options::en_deposit: _deposit(clients_file, separator, user); break;
				case en_trans_menue_options::en_withdraw: _withdraw(clients_file, separator, user); break;
				case en_trans_menue_options::en_total_balances: _show_total_balances(clients_file, separator, user); break;
				case en_trans_menue_options::en_transfer: _transfer(clients_file, transfers_file, separator, user); break;
				case en_trans_menue_options::en_transfer_log: _transfer_log(transfers_file, separator, user);
				}
				cout << "\nPress any key to go back to transactions menue...";
				system("pause>0");
				system("cls");
			}
		} while (option_number != 6);
	}
};