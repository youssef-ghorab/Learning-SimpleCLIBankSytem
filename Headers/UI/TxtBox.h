#pragma once

#include "CrsrCtrl.h"
#include <string>
#include "../utility/clsString.h"
#include "../IO/IOIncludes.h"

class TxtBox
{
private:
    //value of initialtxt and value
    std::string initialTxt="";
    std::string value="";

    //indexs of saved pos in cursor list,this poss is the pos of value and initialtxt and flag to acces
    int beginOfValuePosIndex=-1;
    int nextOfValuePosIndex=-1;
    int isCurrentFlagPosIndex=-1;

    //boolea value is_current to set flag 
    bool isCurrent= false;
    bool firstPrint = true;
    bool isUsingInitialTxt=true;

    //ptr to cursor , use it for update and reprint initialtxt,value,is_current flag
    CursorCtrl * cursorPtr;

    //width of cells (initialtxt and value)
    int baseBoxWidth;

    //colors
    UIsUtulity::BgColor initialtxtBgColor;    
    UIsUtulity::FntColor initialtxtColor;

    UIsUtulity::BgColor valueBgColor;    
    UIsUtulity::FntColor valueColor;

    UIsUtulity::BgColor isCurrentFlagBgColor;    
    UIsUtulity::FntColor isCurrentFlagColor;

    //ancher
    Output::posType initialtxtAncher;
    Output::posType valueAncher;

    //is_current flag symbole
    std::string isCurrrentFlagSymbole = "<";

    //spaces btw txtbow and iscurrent flag
    int spacesBtwCursorAndFlag=1;


public:
    TxtBox(const int box_width,const std::string &initial_txt,UIsUtulity::BgColor initial_txt_bg_color ,UIsUtulity::FntColor initial_txt_color, Output::posType initial_txt_ancher ,const std::string&value,UIsUtulity::BgColor value_bg_color,UIsUtulity::FntColor value_color,Output::posType value_ancher,const int spaces_btw_flag_and_txt_box,const std::string &is_current_flag_symbole,UIsUtulity::BgColor is_current_flag_bg_color, UIsUtulity::FntColor is_current_flag_color,CursorCtrl * cursor) :
    baseBoxWidth(box_width),
    initialTxt(initial_txt),
    initialtxtBgColor(initial_txt_bg_color),
    initialtxtColor(initial_txt_color),
    initialtxtAncher(initial_txt_ancher),
    value(value),
    valueBgColor(value_bg_color),
    valueColor(value_color),
    valueAncher(value_ancher),
    isCurrrentFlagSymbole(is_current_flag_symbole),
    isCurrentFlagBgColor(is_current_flag_bg_color),
    isCurrentFlagColor(is_current_flag_color),
    spacesBtwCursorAndFlag(spaces_btw_flag_and_txt_box),
    cursorPtr(cursor)
    {}

    void displayOnScreen(const int new_lines = 0, const int tabs = 0)
    {     
        //print new line 
        if (new_lines) cursorPtr->output(std::string(new_lines,'\n'));
        //print tabs
        if (tabs) cursorPtr->output(std::string(tabs,'\t'));

        //remaind 
        int remaindSpacesNumber;

        //SET COLORS
        if (isUsingInitialTxt) UIsUtulity::setColors(initialtxtBgColor,initialtxtColor);
        else UIsUtulity::setColors(valueBgColor,valueColor);

        //SAVE/UPDATE BEGIN POS
        if (beginOfValuePosIndex==-1) beginOfValuePosIndex = cursorPtr->saveCurrentCursorPos();
        else cursorPtr->updateSavedPos(beginOfValuePosIndex,cursorPtr->getPos());

        //PRINT BOX TXT
        if (isUsingInitialTxt) cursorPtr->output(Output::getValideInPosAndReturnRemainderSpaces(baseBoxWidth,initialTxt,initialtxtAncher,remaindSpacesNumber));
        else cursorPtr->output(Output::getValideInPosAndReturnRemainderSpaces(baseBoxWidth,value,valueAncher,remaindSpacesNumber));

        //SAVE UPDATE NEXT POS
        if (nextOfValuePosIndex==-1) nextOfValuePosIndex = cursorPtr->saveCurrentCursorPos();
        else cursorPtr->updateSavedPos(nextOfValuePosIndex,cursorPtr->getPos());

        //PRINT SPACES BTW TXT AND END
        cursorPtr->output(std::string(remaindSpacesNumber,' '));

        //RESET COLORS
        UIsUtulity::resetColors();

        //PRINT SPACES BTW TXTBOX AND FLAG
        cursorPtr->output(std::string(spacesBtwCursorAndFlag,' '));

        //SAVE/UPDATE FLAG POS
        if (isCurrentFlagPosIndex==-1) isCurrentFlagPosIndex = cursorPtr->saveCurrentCursorPos();//save current pos as pos of is_current flag
        else cursorPtr->updateSavedPos(isCurrentFlagPosIndex,cursorPtr->getPos());
        
        //set colors to flag clolors
        UIsUtulity::setColors(isCurrentFlagBgColor,isCurrentFlagColor);

        //print flag if is_current is true ELSE SPACES
        if (isCurrent) cursorPtr->output(isCurrrentFlagSymbole);
        else cursorPtr->output(std::string(isCurrrentFlagSymbole.length(),' '));

        //rESET COLORS
        UIsUtulity::resetColors();

        if (isUsingInitialTxt)cursorPtr->updateSavedPos(nextOfValuePosIndex,cursorPtr->getSavedPoses()[beginOfValuePosIndex]);

        firstPrint = false;
    };

    //getters
    bool getIsCurrent() const 
    {
        return isCurrent;
    }

    std::string getInitialTxt()const
    {
        return initialTxt;
    }
    
    virtual std::string getValue()const
    {
        return value;
    }

    int getBaseBoxWidth()const
    {return baseBoxWidth;}

    CursorCtrl * getCursorPtr()
    {
        return cursorPtr;
    }

    int getBeginOfValuePosIndex()const
    {
        return beginOfValuePosIndex;
    }

    UIsUtulity::BgColor getInitialTxtBgColor()const
    {
        return initialtxtBgColor;
    }

    UIsUtulity::FntColor getInitialTxtColor()const
    {
        return initialtxtColor;
    }

    Output::posType getInitialTxtAncher()const
    {return initialtxtAncher;}

    UIsUtulity::BgColor getValueBgColor()const
    {
        return valueBgColor;
    }

    UIsUtulity::FntColor getValueColor()const
    {
        return valueColor;
    }

    Output::posType getValueAncher()const
    {return valueAncher;}

    std::string getIsCurrentFlagSymbole()const
    {return isCurrrentFlagSymbole;}

    UIsUtulity::BgColor getIsCurrentFlagBgColor()const
    {return isCurrentFlagBgColor;}

    UIsUtulity::FntColor getIsCurrentFlagColor()const
    {return isCurrentFlagColor;}

    int getSpacesBtwTxtBoxAndFlag() const
    {return spacesBtwCursorAndFlag;}

    bool getFirstPrint()
    {return firstPrint;}

    //setters
    void setInitialTxt(const std::string &new_val)
    {
        initialTxt = new_val;
    }

    void setBaseBoxWidth(const int new_val)
    {
        baseBoxWidth = new_val;
    }

    void setValue(const std::string &new_val,const bool update_on_screen=false)
    {
        value = new_val;        
        if (!new_val.empty()) isUsingInitialTxt = false;
        else 
        {
            isUsingInitialTxt = true;
        }
        if (update_on_screen) updateOnscreen();
    }

    void setIsCurrent(const bool &new_val)
    {
        isCurrent = new_val;

        if (firstPrint) return;//return because the txtbox not print yet and isCurrentFlagPosIndex net setted yet

        if (isCurrent)
        {
            cursorPtr->moveToSavedPos(isCurrentFlagPosIndex);
            UIsUtulity::setColors(isCurrentFlagBgColor,isCurrentFlagColor);
            cursorPtr->output(isCurrrentFlagSymbole);
            cursorPtr->moveToSavedPos(nextOfValuePosIndex);
        }else 
        {
            cursorPtr->moveToSavedPos(isCurrentFlagPosIndex);
            cursorPtr->output(std::string(isCurrrentFlagSymbole.length(),' '));
        }
    }

    void setBeginOfValuePosIndex(const int new_val)
    {
        beginOfValuePosIndex = new_val;
    }

    void setCursor(CursorCtrl * new_val)
    {
        cursorPtr = new_val;
    }

    void setInitialTxtBgColor(UIsUtulity::BgColor new_val)
    {
        initialtxtBgColor = new_val;
    }

    void setInitialTxtColor(UIsUtulity::FntColor new_val)
    {
        initialtxtColor = new_val;
    }

    void setValueBgColor(UIsUtulity::BgColor new_val)
    {
        valueBgColor = new_val;
    }

    void setValueColor(UIsUtulity::FntColor new_val)
    {
        valueColor = new_val;
    }

    void setInitialTxtAncher(const Output::posType ancher)
    {initialtxtAncher = ancher;}

    void setValueAncher(const Output::posType ancher)
    {valueAncher = ancher;}

    void setIsCurrentFlagSymbole(const std::string& new_val)
    {isCurrrentFlagSymbole = new_val;}

    void setIsCurrentFlagBgColor(const UIsUtulity::BgColor new_val)
    {isCurrentFlagBgColor = new_val;}

    void setIsCurrentFlagColor(const UIsUtulity::FntColor new_val)
    {isCurrentFlagColor = new_val;}

    void setSpacesBtwTxtBoxAndFlag(const int new_val)
    {spacesBtwCursorAndFlag = new_val;}

    void setFirstPrint(const bool new_val)
    {firstPrint = new_val;}

    //mthods
    void updateOnscreen()
    {
        cursorPtr->moveToSavedPos(beginOfValuePosIndex);
        if (isUsingInitialTxt)
        {
            UIsUtulity::setColors(initialtxtBgColor,initialtxtColor);
            int remaindSpacesNumber;
            cursorPtr->output(Output::getValideInPosAndReturnRemainderSpaces(baseBoxWidth,initialTxt,initialtxtAncher,remaindSpacesNumber));
            cursorPtr->updateSavedPos(nextOfValuePosIndex,cursorPtr->getPos());
            cursorPtr->output(std::string(remaindSpacesNumber,' '));
            UIsUtulity::resetColors();
            cursorPtr->moveToSavedPos(beginOfValuePosIndex);
        }
        else 
        {
            UIsUtulity::setColors(valueBgColor,valueColor);
            int remaindSpacesNumber;
            cursorPtr->output(Output::getValideInPosAndReturnRemainderSpaces(baseBoxWidth,value,valueAncher,remaindSpacesNumber));
            cursorPtr->updateSavedPos(nextOfValuePosIndex,cursorPtr->getPos());
            cursorPtr->output(std::string(remaindSpacesNumber,' '));
            UIsUtulity::resetColors();
            cursorPtr->moveToSavedPos(nextOfValuePosIndex);
        }

    }

    virtual void valuePush(const char &c,bool update_on_screen =false)
    {
        if (c == '\b' || c == 127)
        {
            valuePop(update_on_screen);
            return;
        }

        if (value.length() == baseBoxWidth) return; 
        if (isUsingInitialTxt) 
        {
            value.clear();
            isUsingInitialTxt = false;
        }
        value += c;
        if (update_on_screen) updateOnscreen();
    }

    void valuePush(const std::string &s,const bool update_on_screen)
    {
        if (s.empty()) return;
        for (int i = 0 ; i < s.length()-1;i++)
        {
            valuePush(s[i]);
        }
        valuePush(s[s.length()-1],update_on_screen);
    }

    virtual void valuePop(bool update_on_screen = false)
    {
        if (!value.empty())
        {
            value.pop_back();
            if (value.empty()) 
            {
                isUsingInitialTxt=true;
            }
            if (update_on_screen) updateOnscreen();  
        }

    }

    void resetInitialTxt()
    {
        initialTxt = "";
    }

    void resetValue()
    {
        value = "";
    }

    void resetValues()
    {
        resetInitialTxt();
        resetValue();
    }

    virtual void stdReset()
    {
        isCurrent=false;
        firstPrint= true;
        beginOfValuePosIndex=0;
        isCurrentFlagPosIndex=0;
        value = "";
        isUsingInitialTxt = true;
    }

    KeyboardInput::Key startStdCapturingMode(const std::vector<KeyboardInput::Key> keys_to_exit)
    {
        setIsCurrent(true);
        KeyboardInput::Key keyPressed;
        cursorPtr->moveToSavedPos(nextOfValuePosIndex);

        while (true)
        {
            keyPressed = KeyboardInput::waitToPressUnSpecialOrAnyOf(keys_to_exit);

            if (KeyboardInput::isExist(keyPressed,keys_to_exit)) break;

            valuePush(keyPressed,true);
        }
        cursorPtr->moveToSavedPos(isCurrentFlagPosIndex);

        setIsCurrent(false);
        return keyPressed;//return key pressed to exit
    }

};
