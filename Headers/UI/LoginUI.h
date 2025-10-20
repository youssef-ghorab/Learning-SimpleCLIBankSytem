#include "UI.h"
#include "MainScreens/MainUI.h"
#include "ScreenIO/Output.h"
#include "ScreenIO/Input.h"
#include "../ProccessObjcts/Bank.h"
#include "../IO/IOIncludes.h"
#include "CrsrCtrl.h"
#include "TxtBox.h"
#include "HidedTxtBox.h"
#include "TxtBox.h"
#include  "Global.h"

#include <string>

class LoginUI : public UI
{
private:
    Bank &bank;
    MainUI mainUI;

    TxtBox * current = nullptr;
    CursorCtrl cursorCntrl;

    KeyboardInput::Key keyPressed;
    std::vector<KeyboardInput::Key> specialAllowedKeys {KeyboardInput::Enter,KeyboardInput::ArrUp,KeyboardInput::ArrDown,KeyboardInput::Backspace};

    TxtBox usernameTxtBox;
    HidedTxtBoxV2 passwordTxtBox;
    TxtBox notes;

    bool isLoginSuccessefully=false;

    int trailsRemaind = 3;

    void tryToLogin()
    {
        if (checkLoginData(usernameTxtBox.getValue(),passwordTxtBox.getValue()))
        {
            isLoginSuccessefully=true;
            currentUser::instance().setUser(bank.findUser(usernameTxtBox.getValue(),true,passwordTxtBox.getValue()));
            mainUI.show(); 
        }else
        {
            trailsRemaind--;
            updateNotesBox();
        }
    }

    void setCurrentUp()
    {
        if (current == &passwordTxtBox) 
        {
            passwordTxtBox.setIsCurrent(false);
            current = &usernameTxtBox;
            current->setIsCurrent(true);
        }
    }

    void setCurrentDown()
    {
        if (current == &usernameTxtBox) 
        {
            usernameTxtBox.setIsCurrent(false);
            current = &passwordTxtBox;
            current->setIsCurrent(true);
        }
    }

    void popLetterFromCurrent()
    {
        current->valuePop(true);
    }

    void pushLetterToCurrent()
    {
        current->valuePush((char)((int)keyPressed),true);
    }

    void setCurrent()
    {
        current = &usernameTxtBox;
        usernameTxtBox.setIsCurrent(true);
        passwordTxtBox.setIsCurrent(false);
    }

    void performKeyAction()
    {
        switch (keyPressed)
        {
            case KeyboardInput::Enter: tryToLogin(); break;
            case KeyboardInput::ArrUp: setCurrentUp(); break;
            case KeyboardInput::ArrDown: setCurrentDown(); break;
            case KeyboardInput::Backspace: popLetterFromCurrent(); break;
            default: pushLetterToCurrent(); break;
        }
    }

    void printElmnts()
    {
        usernameTxtBox.displayOnScreen(5,4);
        passwordTxtBox.displayOnScreen(2,4);
        notes.displayOnScreen(5,4);
    }

    bool checkLoginData(const std::string &usrnm,const std::string &psswrd)
    {
        return bank.findUser(usrnm,true,psswrd);
    }

    void updateNotesBox()
    {
        if (trailsRemaind == 3) notes.setValue("trails remaind ("+std::to_string(trailsRemaind)+")",true);
        else if (trailsRemaind > 0)
        {
            if (notes.getValueColor() != UIsUtulity::FntRed) notes.setValueColor(UIsUtulity::FntRed);
            notes.setValue("incorrect username/password,trails remaind (" + std::to_string(trailsRemaind)+")",true);
        }else
        {
            passwordTxtBox.setValueBgColor(UIsUtulity::BgRed);
            passwordTxtBox.setInitialTxtBgColor(UIsUtulity::BgRed);
            passwordTxtBox.updateOnscreen();
            usernameTxtBox.setValueBgColor(UIsUtulity::BgRed);
            usernameTxtBox.setInitialTxtBgColor(UIsUtulity::BgRed);
            usernameTxtBox.updateOnscreen();
            notes.setValue("Your account locked (press enter to exit)",true);
        }
    }

    void initialize()
    {
        setCurrent();

        trailsRemaind = 3;

        setCurrent();

        printElmnts();

        updateNotesBox();
    }

public:
    LoginUI(Bank &b) : 
    bank(b),
    mainUI(b),
    usernameTxtBox(50,"username",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Left,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Left,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursorCntrl),
    passwordTxtBox(50,"password",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Left,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Left,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursorCntrl,true),
    notes(50,"",UIsUtulity::BgBlack,UIsUtulity::FntYallow,Output::Center,"",UIsUtulity::BgBlack,UIsUtulity::FntYallow,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntYallow,&cursorCntrl),
    current(&usernameTxtBox) 
    {}

    void show() override
    {
        Output::clearScreen();

        printScreenHeader("LOGIN SCREEN","",'-',120);

        initialize();

        do 
        {
            keyPressed = KeyboardInput::waitToPressUnSpecialOrAnyOf(specialAllowedKeys);
            performKeyAction();
        } while (!isLoginSuccessefully && trailsRemaind > 0);

        isLoginSuccessefully = false;

        if (trailsRemaind == 0)
        {
            updateNotesBox();
            KeyboardInput::waitToPress(KeyboardInput::Key::Enter);
        }
    }

};