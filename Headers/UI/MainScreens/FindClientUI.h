#pragma once

#include "../UI.h"
#include "../UIsUtility.h"
#include "../Global.h"

class FindClientUI : public UI
{
private:
    const Bank &bank;

public:
    FindClientUI(const Bank &bank) : bank(bank){}

    void show() 
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::FindClient))
        {
            UIsUtulity::showAccessDeclineScreen();
            return;
        } 

        std::string accountNumber; 
        char confirm;
        const Client * clientPtr;

        confirm = 'y';

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("FIND CLIENT",UIsUtulity::BgBlack,UIsUtulity::FntBlue,UIsUtulity::FntWhite,'-',screen_width) ;
            accountNumber = Input::read<std::string>("\nEnter account number :","\nErr :please enter a text :");

            clientPtr = bank.findClient(accountNumber,false,"");

            while ((clientPtr == nullptr))
            {
                Output::print<std::string>(UIsUtulity::setTxtColor("No client account with this number ! enter \"exite\" to exite ",UIsUtulity::FntRed),true);

                accountNumber = Input::read<std::string>("\nEnter account number :","\nErr :please enter a text :");
                if (accountNumber == "exit") break;

                clientPtr = bank.findClient(accountNumber,false,"");
            }

            if (clientPtr != nullptr) UIsUtulity::printClient(*clientPtr);
            else Output::print(UIsUtulity::setTxtColor("Err : client not founded or you exite search process !",UIsUtulity::FntRed));

            confirm = Input::read<char>("\nFind another client (y)/(n) ? :","\nErr :please enter \'y\' or \'n\'");
        }
        Output::pressAnyKeyToContinue();
    }

};