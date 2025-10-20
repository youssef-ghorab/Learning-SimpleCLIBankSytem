#include "../UI.h"
#include "../ScreenIO/Output.h"
#include "../ScreenIO/Input.h"
#include "../../ProccessObjcts/PObictsIncludes.h"
#include "../UIsUtility.h"
#include "../Global.h"

class UpdateClientUI : UI
{
private:
    Bank &bank;
public:
    UpdateClientUI(Bank &bank) : bank(bank){}

    void show()
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::UpdateClient))
        {
            UIsUtulity::showAccessDeclineScreen();
            return;
        } 

        char confirm = 'y';
        std::string accountNumber;
        Client * clientFoundedPtr;
        Client newClientData = Client::creatEmptyClient();

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("UPDATE CLIENT","",'-',screen_width);
            accountNumber = Input::read<std::string>("\nplease enter account number : ","\nErr : please enter text");

            while (!bank.findClient(accountNumber,false,"") && accountNumber != "exit")
            {
                accountNumber = Input::read<std::string>("\nno client account with this number , try another one ore enteer \'exit\' to exit : ","\nErr : please enter text");
            }
            if (accountNumber == "exit") break;

            clientFoundedPtr = bank.findClient(accountNumber,false,"");
            
            if (clientFoundedPtr != nullptr) 
            {
                Output::print("CLIENT info",true);
                UIsUtulity::printClient(*clientFoundedPtr);
                Output::print("\nNEW INFO",true);
                newClientData = UIsUtulity::readValideClientFromUser(bank,false,false);
                newClientData.setAccountNumber(accountNumber);

                UIsUtulity::printErrState(bank.updateClient(accountNumber,newClientData));
            }else 
            {
                Output::print("client with number ("+accountNumber+") not found !",true);
                continue;
            }
            confirm = Input::read<char>("\nupdate another client (y)/(n) : ","Err :please enter \'y\' or \'n\' ");
        }
        Output::pressAnyKeyToContinue();
    }
};