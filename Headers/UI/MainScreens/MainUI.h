#pragma once

#include "../UI.h"
#include "../../ProccessObjcts/Client.h"
#include "../../ProccessObjcts/Bank.h"
#include "../ScreenIO/Input.h"
#include "../ScreenIO/Output.h"

#include "addClientUI.h"
#include "deleteClientUI.h"
#include "FindClientUI.h"
#include "ClientsListUI.h"
#include "UpdateClientUI.h"
#include "TransactionUI/TransactionUI.h"
#include "ManageUsersUI/ManageUsersUI.h"
#include "CurrencyExtchane/CurrencyExchangeUI.h"

#include "../UIsUtility.h"
#include "../Global.h"

class MainUI : public UI
{
private:
    enum choses{addClient=1 , findClient ,deleteClient ,clientsList,updateClient,transaction, manageUsers,CurrencyExhange,Logout};

    Bank &bank;
    AddClientUI addClientUI;
    FindClientUI findClientUI;
    DeletClientUI deletClientUI;
    ClientsListUI clientsListUI;
    UpdateClientUI updateClientUI;
    TransactionUI transactionUI;
    ManageUsersUI manageUsersUI;
    CurrencyExchangeUI currencyExchangeUI;

    void performeUserChocie(const choses choice) 
    {
        switch (choice)
        {
            case addClient:
            {
                addClientUI.show();
                break;
            }
            case findClient:
            {
                findClientUI.show();
                break;
            }    
            case deleteClient:
            {
                deletClientUI.show();
                break;
            }    
            case clientsList:
            {
                clientsListUI.show();
                break;
            }  
            case updateClient:
            {
                updateClientUI.show();
                break;
            }  
            case transaction:
            {
                transactionUI.show();
                break;
            }  
            case manageUsers:
            {
                manageUsersUI.show();
                break;
            }  
            case CurrencyExhange:
            {
                currencyExchangeUI.show();
                break;
            }  
        }
    }

public:
    MainUI(Bank &bank)
     : addClientUI(bank),
      findClientUI(bank),
      deletClientUI(bank),
      clientsListUI(bank),
      bank(bank),
      updateClientUI(bank),
      transactionUI(bank),
      manageUsersUI(bank),
      currencyExchangeUI(bank)
      {}

    void show()
    {
        choses userChocie;
        while (userChocie != Logout)
        {
            Output::clearScreen();
            printScreenHeader("main menu",UIsUtulity::BgBlack,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'-',screen_width);

            Output::print(UIsUtulity::setTxtColor("\n\n\n->Please select a chocie :",UIsUtulity::FntWhite));

            Output::print(UIsUtulity::setTxtColor("\n [1]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" add client",UIsUtulity::FntGreen));
            Output::print(UIsUtulity::setTxtColor("\n [2]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" find client",UIsUtulity::FntBlue));
            Output::print(UIsUtulity::setTxtColor("\n [3]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" delete client",UIsUtulity::FntMagenta));
            Output::print(UIsUtulity::setTxtColor("\n [4]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" clients list",UIsUtulity::FntYallow));
            Output::print(UIsUtulity::setTxtColor("\n [5]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" update client",UIsUtulity::FntWhite));
            Output::print(UIsUtulity::setTxtColor("\n [6]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" transaction",UIsUtulity::FntSkyly));
            Output::print(UIsUtulity::setTxtColor("\n [7]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" manage users",UIsUtulity::FntBrightCyan));
            Output::print(UIsUtulity::setTxtColor("\n [8]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Currency exchanger",UIsUtulity::FntBrightWhite));
            Output::print(UIsUtulity::setTxtColor("\n [9]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Logout",UIsUtulity::FntRed));

            userChocie = (choses)Input::read<int>(1,9,"","please enter a valid number :","\nplease enter number (1 to 9) :");

            performeUserChocie(userChocie);
        }
        currentUser::instance().setUser(nullptr);
        Output::print("\nlogout proccess complete seccussefully !");
        Output::pressAnyKeyToContinue();
    }
};