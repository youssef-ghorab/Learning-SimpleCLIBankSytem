#include "../../UI.h"
#include "../../ScreenIO/Output.h"
#include "../../ScreenIO/Input.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../UIsUtility.h"
#include "../../../ProccessObjcts/Loger.h"
#include "../../Global.h"
#include "../../TxtBox.h"

class CurrencyCalculatorUI : public UI
{
private:
    Bank &bank;

    TxtBox converFromTxtBx;
    TxtBox amountTxtBox;
    TxtBox converToTxtBx;
    TxtBox resultTxtBx;
    TxtBox errsTxtBx;

    CursorCtrl cursor;

    void printGuid()
    {
        Output::print("\n[ESC] to exit");
        Output::print("\n[ F ] to enter cuurency (convert from)");
        Output::print("\n[ T ] to enter currency ( convert to )");
        Output::print("\n[ A ] to enter amount ");
    }

    void printTxtBoxes()
    {
        converFromTxtBx.displayOnScreen(4,1);
        converToTxtBx.displayOnScreen(2,1);
        amountTxtBox.displayOnScreen(2,1);
        resultTxtBx.displayOnScreen(3,1);
        errsTxtBx.displayOnScreen(4,1);
    }

    void handleCnvrtFromTxtBxInput(Currency* &converFromCurrencyPtr,float &rateFrom)
    {
        converFromTxtBx.startStdCapturingMode({KeyboardInput::Enter});
        converFromCurrencyPtr = bank.findCurrency(Currency::Identifier::Code,converFromTxtBx.getValue());
        if (converFromCurrencyPtr) rateFrom = converFromCurrencyPtr->getRate();
        else rateFrom = -1;
    }

    void handleAmountTxtBxInput(float &amount)
    {
        amountTxtBox.startStdCapturingMode({KeyboardInput::Enter});
        amount = std::stof(amountTxtBox.getValue());
        if (amount < 0)
            amount = -1;
    }

    void handleCnvrtToTxtBxInput(Currency* &convertToCurrencyPtr,float &rateTo)
    {
        converToTxtBx.startStdCapturingMode({KeyboardInput::Enter});
        convertToCurrencyPtr = bank.findCurrency(Currency::Identifier::Code,converToTxtBx.getValue());
        if (convertToCurrencyPtr) rateTo = convertToCurrencyPtr->getRate();
        else rateTo = -1;
    }

    void handleErrs(const float rateFrom,const float amount, const float rateTo)
    {
        errsTxtBx.setValue("");

        if (rateFrom < 0)
            errsTxtBx.valuePush("invalide (from) code,",false);

        if (amount < 0)
            errsTxtBx.valuePush(" invalide (amount) ",false);

        if (rateTo < 0)
            errsTxtBx.valuePush(" invalide (to) code.",false);

        errsTxtBx.updateOnscreen();
    }

    void handleResult(float &result,const float amount,const float rateFrom,const float rateTo)
    {
        if (!errsTxtBx.getValue().empty()) return;
        result = (amount/rateFrom) * rateTo;
        resultTxtBx.setValue(std::to_string(result),true);
    }

    void performKeyPressed(const KeyboardInput::Key keyPressed,float &rateFrom,float &rateTo,float &amount,float &result,Currency * &currencyFromPtr,Currency * &currencyToPtr)
    {
        switch (keyPressed)
        {
        case KeyboardInput::Key::f:
        case KeyboardInput::Key::F:
            handleCnvrtFromTxtBxInput(currencyFromPtr,rateFrom);
            break;

        case KeyboardInput::Key::a:
        case KeyboardInput::Key::A:
            handleAmountTxtBxInput(amount);
            break;

        case KeyboardInput::Key::t:
        case KeyboardInput::Key::T:
            handleCnvrtToTxtBxInput(currencyToPtr,rateTo);
            break;
        
        default:
            break;
        }

        handleErrs(rateFrom,amount,rateTo);
        handleResult(result,amount,rateFrom,rateTo);
    }

public:
    CurrencyCalculatorUI(Bank &bank) 
    : bank(bank),
    converFromTxtBx(100,"enter currency code to convert from",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Center,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursor),
    amountTxtBox(100,"enter amount",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Center,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursor),
    converToTxtBx(100,"enter currency code to convert to",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Center,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursor),
    resultTxtBx(100,"result",UIsUtulity::BgBrightGreen,UIsUtulity::FntWhite,Output::Center,"",UIsUtulity::BgGreen,UIsUtulity::FntWhite,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursor),
    errsTxtBx(100,"no errs",UIsUtulity::BgBrightRed,UIsUtulity::FntWhite,Output::Center,"",UIsUtulity::BgRed,UIsUtulity::FntWhite,Output::Center,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursor)
    {}

    void show()
    {
        float rateFrom=-1;
        float rateTo  =-1;
        float amount  =-1;
        float result  =-1;

        Currency *converFromCurrencyPtr;
        Currency *convertToCurrencyPtr;

        KeyboardInput::Key keyPressed;

        std::vector <KeyboardInput::Key> keysAllowed{KeyboardInput::Key::F,KeyboardInput::Key::f,KeyboardInput::Key::T,KeyboardInput::Key::t,KeyboardInput::Key::Esc,KeyboardInput::Key::A,KeyboardInput::Key::a};

        do 
        {
            Output::clearScreen();

            printScreenHeader("UPDATE CURRENCY RATE","",'-',50);

            printGuid();

            printTxtBoxes();

            keyPressed = KeyboardInput::waitToPressAnyOf(keysAllowed);
            
            performKeyPressed(keyPressed,rateFrom,rateTo,amount,result,converFromCurrencyPtr,convertToCurrencyPtr);

        } while (keyPressed != KeyboardInput::Key::Esc);
        
        Output::pressAnyKeyToContinue();
    }
};