#include "../../UI.h"
#include "../../ScreenIO/Output.h"
#include "../../ScreenIO/Input.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../UIsUtility.h"

class DepositU : UI
{
private:
    Bank &bank;
public:
    DepositU(Bank &bank) : bank(bank){}

    void show()
    {
        char confirm = 'y';
        std::string accountNumber;
        Client * clientFoundedPtr;
        float amount;

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("DEPOSIT","",'-',50);

            accountNumber = Input::read<std::string>("\nplease enter account number : ","\nErr : please enter text");
            clientFoundedPtr = bank.findClient(accountNumber,false,"");

            while (clientFoundedPtr == nullptr && accountNumber != "exit")
            {
                Output::print(UIsUtulity::setTxtColor("\nNo client with this accout number try another one ",UIsUtulity::FntRed)+",or enter \"exit\" to exit the proccess.",true);
                accountNumber = Input::read<std::string>("\nplease enter account number : ","\nErr : please enter text");
                clientFoundedPtr = bank.findClient(accountNumber,false,"");
            }
            if (accountNumber == "exit" || clientFoundedPtr == nullptr) break;

            Output::print("current amount : "+UIsUtulity::setTxtColor(std::to_string(clientFoundedPtr->getBalance()),UIsUtulity::FntGreen),true);
            amount = Input::read<float>("\nenter amonut :","Err : please enter valide numbers");
            UIsUtulity::printErrState(bank.makeClientBalanceProcess(accountNumber,amount));
            Output::print("current amount : "+UIsUtulity::setTxtColor(std::to_string(clientFoundedPtr->getBalance()),UIsUtulity::FntGreen),true);

            confirm = Input::read<char>("\nmake another deposit (y)/(n) : ","Err :please enter \'y\' or \'n\' ");
        }
        Output::pressAnyKeyToContinue();
    }
};