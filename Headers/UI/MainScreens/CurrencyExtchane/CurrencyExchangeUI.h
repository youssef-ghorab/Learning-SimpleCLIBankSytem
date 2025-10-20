#pragma once

#include "../../UI.h"
#include "../../../ProccessObjcts/Client.h"
#include "../../../ProccessObjcts/Bank.h"
#include "../../ScreenIO/Input.h"
#include "../../ScreenIO/Output.h"

#include "../../UIsUtility.h"

#include "CurrencyTableUI.h"
#include "CurrencyCalculatorUI.h"
#include "UpdateCurrencyRateUI.h"

class CurrencyExchangeUI : public UI
{
private:
    enum class choses{CurrenciesList = 1 , UpdateCurrencyRate ,CurrencyCalculator,Exit};

    Bank &bank;
    CurrencyTableUI currencyTableUI;
    UpdateCurrencyRateUI updateCurrencyRateUI;
    CurrencyCalculatorUI currencyCalculatorUI;

    void performeUserChocie(const choses choice) 
    {
        switch (choice)
        {
            case choses::CurrenciesList:
            {
                currencyTableUI.show();
                break;
            }
            case choses::UpdateCurrencyRate:
            {
                updateCurrencyRateUI.show();
                break;
            }    
            case choses::CurrencyCalculator:
            {
                currencyCalculatorUI.show();
                break;
            }   
        }
    }

public:
    CurrencyExchangeUI(Bank &bank)
    : bank(bank),
    currencyTableUI(bank),
    updateCurrencyRateUI(bank),
    currencyCalculatorUI(bank)
    {}

    void show()
    {
        choses userChocie;
        while (userChocie != choses::Exit)
        {
            Output::clearScreen();
            printScreenHeader("transaction menu",UIsUtulity::BgBlack,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'-',50);

            Output::print(UIsUtulity::setTxtColor("\n\n\n->Please select a chocie :",UIsUtulity::FntWhite));

            Output::print(UIsUtulity::setTxtColor("\n [1]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Currencies list ",UIsUtulity::FntYallow));
            Output::print(UIsUtulity::setTxtColor("\n [2]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Update currency rate ",UIsUtulity::FntGreen));
            Output::print(UIsUtulity::setTxtColor("\n [3]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Currency calculaor",UIsUtulity::FntSkyly));
            Output::print(UIsUtulity::setTxtColor("\n [4]",UIsUtulity::FntWhite)+UIsUtulity::setTxtColor(" Exit",UIsUtulity::FntRed));

            userChocie = (choses)Input::read<int>(1,4,"","please enter a valid number :","\nplease enter number (1 to 4) :");

            performeUserChocie(userChocie);
        }
        Output::pressAnyKeyToContinue();
    }
};