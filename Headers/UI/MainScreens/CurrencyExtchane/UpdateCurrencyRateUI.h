#include "../../UI.h"
#include "../../ScreenIO/Output.h"
#include "../../ScreenIO/Input.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../UIsUtility.h"

class UpdateCurrencyRateUI : UI
{
private:
    Bank &bank;

    Currency::Identifier readIdType()
    {
        return (Currency::Identifier)(Input::read<short>(1,2,"\nplease select search methode : [1] code - [2] country","\nErr : please enter number only","\nErr: 1 or 2"));
    }

    std::string readId(Currency::Identifier idType, Currency * &currencyPtr)
    {
        std::string id;
        do 
        {
            id = ((idType == Currency::Identifier::Code) ? Input::read<std::string>("\nenter code :","\nchaaracters only") : Input::read<std::string>("\nenter country :","\nchaaracters only"));
            currencyPtr = bank.findCurrency(idType,id);
            if (currencyPtr == nullptr && id != "exit") Output::print(UIsUtulity::setTxtColor("\nNo currency with this id try another one ",UIsUtulity::FntRed)+",or enter \"exit\" to exit the proccess.",true);
        } while (currencyPtr == nullptr && id != "exit");
        return id;
    }

    void printCurrencyRate(const Currency * const currencyPtr)
    {
        float rate = currencyPtr->getRate();
        std::string txt = "current rate : "+UIsUtulity::setTxtColor(std::to_string(rate),UIsUtulity::FntGreen);
        Output::print(txt,true);
    }

    float readNewRate()
    {
        float newRate;
        do
        {
            newRate = Input::read<short>("\n enter new rate :","Err : please enter valide numbers");
            if (newRate<0)Output::print("enter positif only");
        } while (newRate < 0);
        return newRate;
    }

public:
    UpdateCurrencyRateUI(Bank &bank) : bank(bank){}

    void show()
    {
        char confirm = 'y';
        std::string identifier;
        Currency * currencyPtr;
        short newRate;
        Currency::Identifier idType;
        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();

            printScreenHeader("UPDATE CURRENCY RATE","",'-',50);

            idType = readIdType();

            identifier = readId(idType,currencyPtr);

            if (currencyPtr == nullptr) break;

            printCurrencyRate(currencyPtr);

            newRate = readNewRate();

            bank.updateCurrencyRate(idType,identifier,newRate);

            printCurrencyRate(currencyPtr);

            confirm = Input::read<char>("\nupdate another currency rate (y)/(n) : ","Err :please enter \'y\' or \'n\' ");
        }
        Output::pressAnyKeyToContinue();
    }
};