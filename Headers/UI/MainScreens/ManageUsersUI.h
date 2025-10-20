#pragma once

#include "../../UI.h"
#include "../../../ProccessObjcts/Client.h"
#include "../../../ProccessObjcts/Bank.h"
#include "../../ScreenIO/Input.h"
#include "../../ScreenIO/Output.h"

#include "../../UIsUtility.h"
#include "addUserUI.h"
#include "deleteUserUI.h"
#include "FindUserUI.h"
#include "UpdateUserUI.h"
#include "UsersListUI.h"
#include "../Global.h"

class ManageUsersUI : public UI
{
private:
    enum choses{AddUser=1 ,DeleteUser ,FindUser ,UpdateUser ,UsersList ,Exit};

    Bank &bank;
    AddUserUI addUserUI;;
    DeletUserUI deleteUserUI;
    FindUserUI findUserUI;
    UpdateUserUI updateUserUI;
    UsersListUI usersListUI;

    void performeUserChocie(const choses choice) 
    {
        switch (choice)
        {
            case AddUser:
            {
                addUserUI.show();
                break;
            }
            case DeleteUser:
            {
                deleteUserUI.show();
                break;
            }    
            case FindUser:
            {
                findUserUI.show();
                break;
            }    
            case UpdateUser:
            {
                updateUserUI.show();
                break;
            } 
            case UsersList:
            {
                usersListUI.show();
                break;
            } 
            case Exit:
            {
                break;
            } 
        }
    }

public:
    ManageUsersUI(Bank &bank)
    : bank(bank),
    addUserUI(bank),
    deleteUserUI(bank),
    findUserUI(bank),
    updateUserUI(bank),
    usersListUI(bank) {}

    void show()
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::ManageUsers))
        {
            UIsUtulity::showAccesDeclineScreen();
            return;
        } 

        choses userChocie;
        while (userChocie != Exit)
        {
            Output::clearScreen();
            printScreenHeader("MANAGE USERS",UIsUtulity::BgBlack,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'-',screen_width);

            Output::print(UIsUtulity::setTxtColor("\n\n\n->Please select a chocie :",UIsUtulity::FntWhite));

            Output::print(UIsUtulity::setTxtColor("\n [1]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" add user ",UIsUtulity::FntYallow));
            Output::print(UIsUtulity::setTxtColor("\n [2]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" delete user ",UIsUtulity::FntGreen));
            Output::print(UIsUtulity::setTxtColor("\n [3]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" find user",UIsUtulity::FntSkyly));
            Output::print(UIsUtulity::setTxtColor("\n [4]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" update user ",UIsUtulity::FntRed));
            Output::print(UIsUtulity::setTxtColor("\n [5]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" users list ",UIsUtulity::FntRed));
            Output::print(UIsUtulity::setTxtColor("\n [6]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" exit ",UIsUtulity::FntRed));

            userChocie = (choses)Input::read<int>(1,6,"","please enter a valid number :","\nplease enter number (1 to 6) :");

            performeUserChocie(userChocie);
        }
        Output::pressAnyKeyToContinue();
    }
};