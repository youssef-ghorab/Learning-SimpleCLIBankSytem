#include <iostream>
#include "Headers/UI/LoginUI.h"
#include "Headers/UI/TxtBox.h"

int main()
{
    Bank bank("Data/Clients.txt",true,"Data/Users.txt",true,"Data/Currencies.txt",false,"#//#");
    while (true)
    {
        LoginUI loginUI(bank);
        loginUI.show();  
    }
    return 0;
}
