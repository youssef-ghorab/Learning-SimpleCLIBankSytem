#pragma once

#include "../UI.h"
#include "../UIsUtility.h"
#include "../../ProccessObjcts/PObictsIncludes.h"
#include "../Global.h"

class AddClientUI : public UI
{
private:
    Bank &bank;

public:
    AddClientUI(Bank &bank) : bank(bank){}

    void show() 
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::AddClient))
        {
            UIsUtulity::showAccessDeclineScreen();
            return;
        } 

        Client newClient = Client::creatEmptyClient();
        ExcepAndErr::errState addUserPreoccesState;
        char confirm;

        confirm = 'y';

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("ADD CLIENT",UIsUtulity::BgBlack,UIsUtulity::FntGreen,UIsUtulity::FntWhite,'-',screen_width);

            Output::print<std::string>("Please enter new client info ",true);
            newClient = UIsUtulity::readValideClientFromUser(bank);

            addUserPreoccesState = bank.addClient(newClient);
            UIsUtulity::printErrState(addUserPreoccesState);

            confirm = Input::read<char>("\nAdd another client (y)/(n) ? :","Err:please enter \'y\' or \'n\'");
        }
        Output::pressAnyKeyToContinue();
    }

};