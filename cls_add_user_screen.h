#pragma once

#include "cls_screen.h"
#include "cls_bank_user.h"
#include "cls_input_validate.h"
#include "cls_bank_user.h"

class cls_add_user_screen : protected cls_screen
{
private:
    static void _print_user(cls_bank_user user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.first_name;
        cout << "\nLastName    : " << user.last_name;
        cout << "\nFull Name   : " << user.full_name();
        cout << "\nEmail       : " << user.email;
        cout << "\nPhone       : " << user.phone;
        cout << "\nUser Name   : " << user.user_name;
        cout << "\nPassword    : " << user.password;
        cout << "\nPermissions : " << user.permissions;
        cout << "\n___________________\n";
    }

    static short _read_permissions()
    {
        short permissions = 0;
        char answer;
        cout << "\nDo you want to give full access? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') return -1;
        cout << "\nDo you want to give access to : \n ";
        cout << "\nShow Client List? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::SHOW_CLIENTS_LIST;
        cout << "\nAdd New Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::ADD_NEW_CLIENT;
        cout << "\nDelete Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::DELETE_CLIENT;
        cout << "\nUpdate Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::UPDATE_CLIENT;
        cout << "\nFind Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::FIND_CLIENT;
        cout << "\nTransactions? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::TRANSACTIONS;
        cout << "\nManage Users? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::MANAGE_USERS;
        cout << "\nLogin Register? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') permissions |= cls_bank_user::LOGIN_REGISTER;
        return permissions;
    }

    static void _read_user_info(cls_bank_user& user)
    {
        cout << "\nEnter FirstName: ";
        user.first_name = cls_input_validate::read_string();
        cout << "\nEnter LastName: ";
        user.last_name = cls_input_validate::read_string();
        cout << "\nEnter Email: ";
        user.email = cls_input_validate::read_string();
        cout << "\nEnter Phone: ";
        user.phone = cls_input_validate::read_string();
        cout << "\nEnter Password: ";
        user.password = cls_input_validate::read_string();
        cout << "\nEnter Permission: ";
        user.permissions = _read_permissions();
    }

public:
    static void add_user(string users_file, string separator, cls_bank_user user)
    {
        _draw_screen_header("\t  Add New User Screen", "", user);
        string user_name;
        cout << "\nPlease Enter UserName: ";
        user_name = cls_input_validate::read_string();
        while (cls_bank_user::is_user_exist(user_name, users_file, separator))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            user_name = cls_input_validate::read_string();
        }
        cls_bank_user new_user = cls_bank_user::get_add_user_object(user_name);
        _read_user_info(new_user);
        cls_bank_user::en_saving_results save_result;
        save_result = new_user.save(users_file, separator);
        switch (save_result)
        {
        case  cls_bank_user::en_saving_results::succeeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _print_user(new_user);
            break;
        }
        case cls_bank_user::en_saving_results::failed_empty_object:
        {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case cls_bank_user::en_saving_results::failed_user_name_exist:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        }
    }
};