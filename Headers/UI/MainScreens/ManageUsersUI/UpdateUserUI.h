#include "../../UI.h"
#include "../../ScreenIO/Output.h"
#include "../../ScreenIO/Input.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../UIsUtility.h"

class UpdateUserUI : UI
{
private:
    Bank &bank;
public:
    UpdateUserUI(Bank &bank) : bank(bank){}

    void show()
    {
        char confirm = 'y';
        std::string username;
        User * userFoundedPtr;
        User newUserData = User();

        while (std::tolower(confirm) == 'y')
        {
            Output::clearScreen();
            printScreenHeader("UPDATE USER","",'-',screen_width);
            username = Input::read<std::string>("\nplease enter username : ","\nErr : please enter text");

            while (!bank.findUser(username,false,"") && username != "exit")
            {
                username = Input::read<std::string>("\nno client account with this number , try another one ore enteer \'exit\' to exit : ","\nErr : please enter text");
            }
            if (username == "exit") break;

            userFoundedPtr = bank.findUser(username,false,"");
            
            if (userFoundedPtr != nullptr) 
            {
                Output::print("USER info",true);
                UIsUtulity::printUser(*userFoundedPtr);
                Output::print("\nNEW INFO",true);
                newUserData = UIsUtulity::readValideUserFromUser(bank,false,false);
                UIsUtulity::printErrState(bank.updateUser(username,newUserData));
            }else 
            {
                Output::print("user with name ("+username+") not found !",true);
                continue;
            }
            confirm = Input::read<char>("\nupdate another user (y)/(n) : ","Err :please enter \'y\' or \'n\' ");
        }
        Output::pressAnyKeyToContinue();
    }
};