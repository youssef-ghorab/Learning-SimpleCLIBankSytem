#pragma once

#include "../UI.h"
#include "../UIsUtility.h"
#include "../ScreenIO/Input.h"
#include "../ScreenIO/Output.h"
#include "../Global.h"

class DeletClientUI : public UI
{
private:
    Bank &bank;

public:
    DeletClientUI(Bank &bank) : bank(bank)
    {
    }

    void show() 
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::DeleteClient))
        {
            UIsUtulity::showAccessDeclineScreen();
            return;
        } 

        std::string accountNumber; 
        ExcepAndErr::errState deleteClientProccesState;
        const Client * clientPtr;
        char confirm;

        confirm = 'y';

        while(std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("DELETE CLIENT",UIsUtulity::BgBlack,UIsUtulity::FntRed,UIsUtulity::FntWhite,'-',screen_width) ;
            accountNumber = Input::read<std::string>("\nEnter account number :","\nErr :please enter a text :");

            clientPtr = bank.findClient(accountNumber,false ,"");

            while ((clientPtr == nullptr))
            {
                Output::print<std::string>(UIsUtulity::setTxtColor("No client with this accoutn number !",UIsUtulity::FntRed),true);

                accountNumber = Input::read<std::string>("\nEnter account number :","\nErr :please enter a text :");

                clientPtr = bank.findClient(accountNumber,false,"");
            }
            Output::print<std::string>("The following client will be deleted: ",true);
            UIsUtulity::printClient(*clientPtr);

            confirm = Input::read<char>(UIsUtulity::setTxtColor("\nAre you sure (y)/(n) :",UIsUtulity::FntRed),"\nErr :please enter \'y\' or \'n\'");

            if (std::tolower(confirm) != 'y') break;

            deleteClientProccesState=bank.deleteClient(accountNumber,true);
            UIsUtulity::printErrState(deleteClientProccesState);

            confirm = Input::read<char>("\nDo you want to delete another client (y)/(n) ? :","\nErr :please enter \'y\' or \'n\'");
        }

        Output::pressAnyKeyToContinue();
    }
};