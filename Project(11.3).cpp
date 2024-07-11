#include "cls_bank.h"

using namespace std;

int main()
{
    cls_bank::bank_program("clients.txt", "users.txt", "logins.txt", "transfers.txt", "currencies.txt", "#//#");
}