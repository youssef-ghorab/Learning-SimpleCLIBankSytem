#pragma once

#include "../../UI.h"
#include "../../UIsUtility.h"
#include "../../ScreenIO/Input.h"
#include "../../ScreenIO/Output.h"

class DeletUserUI : public UI
{
private:
    Bank &bank;

public:
    DeletUserUI(Bank &bank) : bank(bank)
    {
    }

    void show() 
    {
        std::string username; 
        ExcepAndErr::errState deleteUserProccesState;
        const User * userPtr;
        char confirm;

        confirm = 'y';

        while(std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("DELETE USER",UIsUtulity::BgBlack,UIsUtulity::FntRed,UIsUtulity::FntWhite,'-',screen_width) ;
            username = Input::read<std::string>("\nEnter usename :","\nErr :please enter a text :");

            userPtr = bank.findUser(username,false ,"");

            while ((userPtr == nullptr))
            {
                Output::print<std::string>(UIsUtulity::setTxtColor("No user with this name !",UIsUtulity::FntRed),true);

                username = Input::read<std::string>("\nEnter username :","\nErr :please enter a text :");

                userPtr = bank.findUser(username,false,"");
            }
            Output::print<std::string>("The following user will be deleted: ",true);
            UIsUtulity::printUser(*userPtr);

            confirm = Input::read<char>(UIsUtulity::setTxtColor("\nAre you sure (y)/(n) :",UIsUtulity::FntRed),"\nErr :please enter \'y\' or \'n\'");

            if (std::tolower(confirm) != 'y') break;

            deleteUserProccesState=bank.deleteUser(username,true);
            UIsUtulity::printErrState(deleteUserProccesState);

            confirm = Input::read<char>("\nDo you want to delete another user (y)/(n) ? :","\nErr :please enter \'y\' or \'n\'");
        }

        Output::pressAnyKeyToContinue();
    }
};