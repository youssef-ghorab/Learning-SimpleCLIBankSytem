#pragma once

#include "../../UI.h"
#include "../../../ProccessObjcts/Client.h"
#include "../../../ProccessObjcts/Bank.h"
#include "../../ScreenIO/Input.h"
#include "../../ScreenIO/Output.h"

#include "../../UIsUtility.h"
#include "DepositUI.h"
#include "WithdrawUI.h"
#include "TotalBalancesUI.h"
#include "TransferUI.h"
#include "TransferLogUI.h"

class TransactionUI : public UI
{
private:
    enum choses{Desposit=1 , Withdraw ,BalancesTable ,Transfer ,TransferLog,Exit};

    Bank &bank;
    DepositU depositUI;
    WithdrawUI withdrawUI;
    TransferUI transferUI;
    TotalBalancesUI balancesTable;
    TransferLogUI transferLogUI;

    void performeUserChocie(const choses choice) 
    {
        switch (choice)
        {
            case Desposit:
            {
                depositUI.show();
                break;
            }
            case Withdraw:
            {
                withdrawUI.show();
                break;
            }    
            case BalancesTable:
            {
                balancesTable.show();
                break;
            }    
            case Transfer:
            {
                transferUI.show();
                break;
            }  
            case TransferLog:
            {
                transferLogUI.show();
                break;
            }  
        }
    }

public:
    TransactionUI(Bank &bank)
    : bank(bank),
    depositUI(bank),
    withdrawUI(bank),
    transferUI(bank),
    balancesTable(bank) {}

    void show()
    {
        choses userChocie;
        while (userChocie != Exit)
        {
            Output::clearScreen();
            printScreenHeader("transaction menu",UIsUtulity::BgBlack,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'-',50);

            Output::print(UIsUtulity::setTxtColor("\n\n\n->Please select a chocie :",UIsUtulity::FntWhite));

            Output::print(UIsUtulity::setTxtColor("\n [1]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" deposit ",UIsUtulity::FntYallow));
            Output::print(UIsUtulity::setTxtColor("\n [2]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" withdraw ",UIsUtulity::FntGreen));
            Output::print(UIsUtulity::setTxtColor("\n [3]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" balances list",UIsUtulity::FntSkyly));
            Output::print(UIsUtulity::setTxtColor("\n [4]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" transfer",UIsUtulity::FntBrightRed));
            Output::print(UIsUtulity::setTxtColor("\n [5]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" transfer log ",UIsUtulity::FntBrightGreen));
            Output::print(UIsUtulity::setTxtColor("\n [6]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" exit ",UIsUtulity::FntRed));

            userChocie = (choses)Input::read<int>(1,6,"","please enter a valid number :","\nplease enter number (1 to 6) :");

            performeUserChocie(userChocie);
        }
        Output::pressAnyKeyToContinue();
    }
};