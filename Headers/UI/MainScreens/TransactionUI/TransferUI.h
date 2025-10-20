#include "../../UI.h"
#include "../../ScreenIO/Output.h"
#include "../../ScreenIO/Input.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../UIsUtility.h"
#include "../../../ProccessObjcts/Loger.h"
#include "../../Global.h"

class TransferUI : public UI
{
private:
    Bank &bank;

    void printShortCards(const Client * firstClientPtr, const Client * secondClientPtr)
    {
        Output::print("\nSender");
        UIsUtulity::printShortClientCard(*firstClientPtr);

        Output::print("\nReciever");
        UIsUtulity::printShortClientCard(*secondClientPtr);
    }

    void readAndGetClientsPtr( Client * &firstClientPtr, Client * &secondclientPtr)
    {
        std::string firstClientAccNum;
        std::string secondClentAccNum;

        while (true)
        {
            firstClientAccNum = UIsUtulity::readValidAccNum(bank,"\nenter client number to transfer (from)");
            if (firstClientAccNum == "exit") return;

            secondClentAccNum = UIsUtulity::readValidAccNum(bank,"\nenter client number to transfer (to)");
            if (secondClentAccNum == "exit") return;

            if (firstClientAccNum != secondClentAccNum) break;

            Output::print(UIsUtulity::setTxtColor("\nyou cant send and receive from same account !",UIsUtulity::FntBrightRed),true);
        }

        firstClientPtr = bank.findClient(firstClientAccNum,false,"");
        secondclientPtr = bank.findClient(secondClentAccNum,false,"");
    }

    float readAmount(const float senderBalance)
    {
        const std::string requestText = "\nenter amount";
        const std::string inputTypeErrText = "\nErr : numbers only";
        const std::string outOfRangeErrText = "invalide amount enter number betwen 0 and "+std::to_string(senderBalance);

        return Input::read<float>(0,senderBalance,requestText,inputTypeErrText,outOfRangeErrText);
    }

    ExcepAndErr::errState transfer(std::string acc_num1, std::string acc_num2,const float amount)
    {

        Output::print("transfering ...",true);
        return bank.transfer(acc_num1,acc_num2,amount);
    }

public:
    TransferUI(Bank &bank) : bank(bank){}

    void show()
    {
        char confirm = 'y';

        Client * senderPtr;

        Client * receiverPtr;

        float amount;

        ExcepAndErr::errState proccessState;

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();

            printScreenHeader("TRANSFER","",'-',50);

            readAndGetClientsPtr(senderPtr,receiverPtr);
            
            if (!senderPtr || !receiverPtr) break;

            printShortCards(senderPtr,receiverPtr);

            amount = readAmount(senderPtr->getBalance());

            confirm = Input::read<char>("are you sure to transfer ("+ std::to_string(amount) +") from [" + senderPtr->getAccountNumber() + "] to [" + receiverPtr->getAccountNumber() + "] (y)/(n) ? :","please enter y or n");
            if (std::tolower(confirm) != 'y') break;

            proccessState = transfer(senderPtr->getAccountNumber(),receiverPtr->getAccountNumber(),amount);

            UIsUtulity::printErrState(proccessState);

            printShortCards(senderPtr,receiverPtr);

            confirm = Input::read<char>("\nmake another transfer (y)/(n) : ","Err :please enter \'y\' or \'n\' ");
        }
        Output::pressAnyKeyToContinue();
    }
};