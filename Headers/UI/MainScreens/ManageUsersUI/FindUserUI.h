#pragma once

#include "../../UI.h"
#include "../../UIsUtility.h"

class FindUserUI : public UI
{
private:
    const Bank &bank;

public:
    FindUserUI(const Bank &bank) : bank(bank)
    {
    }

    void show() 
    {
        std::string username; 
        char confirm;
        const User * userPtr;

        confirm = 'y';

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("FIND USER",UIsUtulity::BgBlack,UIsUtulity::FntBlue,UIsUtulity::FntWhite,'-',screen_width) ;
            username = Input::read<std::string>("\nEnter username :","\nErr :please enter a text :");

            userPtr = bank.findUser(username,false,"");

            while ((userPtr == nullptr))
            {
                Output::print<std::string>(UIsUtulity::setTxtColor("No user account with this name ! enter \"exite\" to exite ",UIsUtulity::FntRed),true);

                username = Input::read<std::string>("\nEnter username :","\nErr :please enter a text :");
                if (username == "exit") break;

                userPtr = bank.findUser(username,false,"");
            }

            if (userPtr != nullptr) UIsUtulity::printUser(*userPtr);
            else Output::print(UIsUtulity::setTxtColor("Err : user not founded or you exite search process !",UIsUtulity::FntRed));

            confirm = Input::read<char>("\nFind another user (y)/(n) ? :","\nErr :please enter \'y\' or \'n\'");
        }
        Output::pressAnyKeyToContinue();
    }

};