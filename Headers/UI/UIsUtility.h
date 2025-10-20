#pragma once

#include "../ProccessObjcts/PObictsIncludes.h"
#include "ScreenIO/Input.h"
#include "ScreenIO/Output.h"
#include "CrsrCtrl.h"

class UIsUtulity
{
public:
    enum FntColor {
        FntSkyly = 36, FntBlack = 30, FntBlue = 34, FntGreen = 32, FntRed = 31, 
        FntYallow = 33, FntWhite = 37, FntMagenta = 35, FntBrightBlack = 90,
        FntBrightRed = 91, FntBrightGreen = 92, FntBrightYellow = 93, FntBrightBlue = 94,
        FntBrightMagenta = 95, FntBrightCyan = 96, FntBrightWhite = 97
    };

    enum BgColor {
        BgSkyly = 46, BgBlack = 40, BgBlue = 44, BgGreen = 42, BgRed = 41, 
        BgYallow = 43, BgWhite = 47, BgBrightBlack = 100, BgBrightRed = 101,
        BgBrightGreen = 102, BgBrightYellow = 103, BgBrightBlue = 104,
        BgBrightMagenta = 105, BgBrightSkyly = 106, BgBrightWhite = 107
    };

    enum State { Ready, Wait };

    // --- Colors ---
    static void setFntColor(FntColor color)
    {
        Output::print("\033[" + std::to_string(color) + "m", false);
    }

    static void setBgColor(BgColor color)
    {
        Output::print("\033[" + std::to_string(color) + "m", false);
    }

    static void resetColors()
    {
        Output::print("\033[0m");
    }

    static std::string setTxtColor(const std::string& txt, FntColor color)
    {
        return "\033[" + std::to_string(color) + "m" + txt + "\033[0m";
    }

    static void setColors(BgColor bg_color, FntColor fnt_color)
    {
        setBgColor(bg_color);
        setFntColor(fnt_color);
    }

    static void setToDarkTheme() { setColors(BgBlack, FntWhite); }
    static void setToLightTheme() { setColors(BgWhite, FntBlack); }

    // --- Print info ---
    static void printClient(const Client& client)
    {
        Output::print("------------ I N F O ------------", true);
        Output::print(" First name     : " + client.getFirstName(), true);
        Output::print(" Last name      : " + client.getLastName(), true);
        Output::print(" Email          : " + client.getEmail(), true);
        Output::print(" Phone number   : " + client.getPhoneNumber(), true);
        Output::print(" Account number : " + client.getAccountNumber(), true);
        Output::print(" PIN code       : " + client.getPinCode(), true);
        Output::print(" Balance        : " + std::to_string(client.getBalance()), true);
    }

    static void printShortClientCard(const Client& client)
    {
        Output::print("------------ I N F O ------------", true);
        Output::print(" Full name      : " + client.getFirstName() + " " + client.getLastName(), true);
        Output::print(" Account number : " + client.getAccountNumber(), true);
        Output::print(" Balance        : " + std::to_string(client.getBalance()), true);
    }

    static void printCurrencyCard(const Currency& currency)
    {
        Output::print("Country : " + currency.getCountry(), true);
        Output::print("Code    : " + currency.getCode(), true);
        Output::print("Name    : " + currency.getName(), true);
        Output::print("Rate    : " + std::to_string(currency.getRate()), true);
    }

    static void printUser(const User& user)
    {
        Output::print("------------ I N F O ------------", true);
        Output::print(" First name   : " + user.getFirstName(), true);
        Output::print(" Last name    : " + user.getLastName(), true);
        Output::print(" Email        : " + user.getEmail(), true);
        Output::print(" Phone number : " + user.getPhoneNumber(), true);
        Output::print(" Username     : " + user.getUsername(), true);
        Output::print(" Password     : " + user.getPassword(), true);
        Output::print(" Permissions  : " + std::to_string(Permissions::permissionsVecToInt(user.getPermissions().getHasPermission())), true);
    }

    static void printErrState(ExcepAndErr::errState state)
    {
        setFntColor(FntRed);
        switch (state)
        {
        case ExcepAndErr::noErr:
            Output::print(setTxtColor("Note: Process completed successfully!", FntGreen));
            break;
        case ExcepAndErr::failedToOpenFile:
            Output::print("Error: Failed to open the file!");
            break;
        case ExcepAndErr::fileNotExist:
            Output::print("Error: File does not exist!");
            break;
        case ExcepAndErr::vectorOutOfRange:
            Output::print("Error: Vector out of range!");
            break;
        case ExcepAndErr::invalideAccountNumber:
            Output::print("Error: Invalid account number!");
            break;
        case ExcepAndErr::invalideBalanceToSet:
            Output::print("Error: Invalid balance!");
            break;
        }
        resetColors();
    }

    // --- Read user input ---
    static std::string readValidAccNum(const Bank& bank, const std::string& request_txt)
    {
        const Client* cPtr = nullptr;
        std::string accNum = "";

        while (cPtr == nullptr && accNum != "exit")
        {
            accNum = Input::read<std::string>(request_txt, "Err: please enter valid text!");
            cPtr = bank.findClient(accNum);
            if (!cPtr)
                Output::print(setTxtColor("No client with this account number. Try another or type 'exit'.", FntRed), true);
        }
        return accNum;
    }

    static int readPermissions() 
    { 
        std::string errMessage = "Err: please enter (y) or (n)"; std::vector<std::string> requestMessages { 
            "\n add client permission (y)/(n) : ", 
            "\n delet client permission (y)/(n) : ", 
            "\n update client permission (y)/(n) : ", 
            "\n access clients list permission (y)/(n) : ", 
            "\n find client permission (y)/(n) : ", 
            "\n client transaction permission (y)/(n) : ", 
            "\n manage users permission (y)/(n) : "
        }; 
        
        std::vector<Permissions::PermissionTypes> permissionsTypes{ 
            Permissions::PermissionTypes::AddClient, 
            Permissions::PermissionTypes::DeleteClient, 
            Permissions::PermissionTypes::UpdateClient, 
            Permissions::PermissionTypes::ClientsList, 
            Permissions::PermissionTypes::FindClient, 
            Permissions::PermissionTypes::Transaction, 
            Permissions::PermissionTypes::ManageUsers
        }; 
            
        int permissions = 0; 
        if (std::tolower((unsigned char)Input::read<char>("\ngive all access (y)/(n) : ",errMessage)) == 'y') 
            return Permissions::getAllPermissions();
            
        for (int i = 0; i< requestMessages.size();i++) 
        { 
            if (std::tolower((unsigned char)Input::read<char>(requestMessages[i],errMessage)) == 'y') permissions |= (int)permissionsTypes[i];
        } 
        return permissions; 
    }

    static Client readValideClientFromUser(const Bank &bank,const bool read_account_number = true,const bool unique_account_number = true)
    {
        const std::string firstName = Input::read<std::string>("\n first name : ","\nErr : please enter valide string !."); 
        const std::string lastName = Input::read<std::string>("\n last name : ","\nErr : please enter valide string !."); 
        const std::string email = Input::read<std::string>("\n email: ","\nErr : please enter valide string !."); 
        const std::string phoneNumber = Input::read<std::string>("\n phone number : ","\nErr : please enter valide string !."); 
        std::string accountNumber = ""; 
        
        if (read_account_number) 
        {
            accountNumber = Input::read<std::string>("\n account number : ","\nErr : please enter valide string !.");
            while (bank.findClient(accountNumber,false,"") && unique_account_number) 
            { 
                Output::print(UIsUtulity::setTxtColor("Err :client account with this number already exist,try another one.",UIsUtulity::FntRed),true);
                accountNumber = Input::read<std::string>("\n account number : ","\nErr : please enter valide string !.");
            } 
        }

        const std::string PIN_CODE = Input::read<std::string>("\n PIN code : ","\nErr : please enter valide string !.");
        const float BALANCE = Input::read<float>("\n balance : ","\nErr : please enter valide number !."); 
        
        return Client(firstName,lastName,email,phoneNumber,accountNumber,PIN_CODE,BALANCE); 
    } 

    static User readValideUserFromUser(const Bank &bank,const bool read_username = true,const bool unique_username = true) 
    { 
        const std::string firstName = Input::read<std::string>("\n first name : ","\nErr : please enter valide string !."); 
        const std::string lastName = Input::read<std::string>("\n last name : ","\nErr : please enter valide string !."); 
        const std::string email = Input::read<std::string>("\n email: ","\nErr : please enter valide string !."); 
        const std::string phoneNumber = Input::read<std::string>("\n phone number : ","\nErr : please enter valide string !."); 
        std::string username = ""; 
        
        if (read_username) 
        { 
            username = Input::read<std::string>("\n username : ","\nErr : please enter valide string !.");
            
            while (bank.findUser(username,false,"") != nullptr && unique_username) 
            { 
                Output::print(UIsUtulity::setTxtColor("Err :user with this name already exist,try another one.",UIsUtulity::FntRed),true); 
                username = Input::read<std::string>("\n username : ","\nErr : please enter valide string !.");
            }
        } 
        const std::string password = Input::read<std::string>("\n password : ","\nErr : please enter valide string !."); 
        Output::print("USER PERMISSION",true); 
        const Permissions permissions = Permissions(readPermissions()); 
        return User(firstName,lastName,email,phoneNumber,username,password,permissions);
    } 
    
    // --- User cursor ---
    static void printUserCursor(State state, bool newLine = true)
    {
        if (newLine) Output::print("\n", false);
        if (state == Ready) Output::print("\\" + setTxtColor("ready>", FntGreen), false);
        else if (state == Wait) Output::print("\\" + setTxtColor("wait>", FntYallow), false);
    }

    static void printUserCursor(State state,CursorCtrl &crsrCntrl ,bool newLine = true)
    {
        if (newLine) crsrCntrl.output("\n");
        if (state == Ready) crsrCntrl.output("\\" + setTxtColor("ready>", FntGreen));
        else if (state == Wait) crsrCntrl.output("\\" + setTxtColor("wait>", FntYallow));
    }

    static std::string getUserCursor(State state, bool newLine = true)
    {
        std::string cursor = "";
        if (newLine) cursor += "\n";
        if (state == Ready) cursor += setTxtColor("\\ready>", FntGreen);
        else if (state == Wait) cursor += setTxtColor("\\wait>", FntYallow);
        return cursor;
    }

    static void showAccessDeclineScreen()
    {
        Output::clearScreen();
        Output::print("YOU DON'T HAVE ACCESS TO THIS SCREEN");
        Output::pressAnyKeyToContinue();
    }
};
