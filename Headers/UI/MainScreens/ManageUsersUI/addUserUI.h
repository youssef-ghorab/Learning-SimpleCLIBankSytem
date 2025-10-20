#pragma once

#include "../../UI.h"
#include "../../UIsUtility.h"

class AddUserUI : public UI
{
private:
    Bank &bank;

public:
    AddUserUI(Bank &bank) : bank(bank){}

    void show() 
    {
        User newUser = User();//hello 
        ExcepAndErr::errState addClientPreoccesState;
        char confirm;

        confirm = 'y';

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("add new user",UIsUtulity::BgBlack,UIsUtulity::FntGreen,UIsUtulity::FntWhite,'-',screen_width);
            Output::print<std::string>("Please enter new user info ",true);

            newUser = UIsUtulity::readValideUserFromUser(bank);

            addClientPreoccesState = bank.addUser(newUser,true);

            UIsUtulity::printErrState(addClientPreoccesState);

            confirm = Input::read<char>("\nAdd another user (y)/(n) ? :","Err:please enter \'y\' or \'n\'");
        }
        Output::pressAnyKeyToContinue();
    }

};