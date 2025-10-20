#pragma once

#include "CrsrCtrl.h"
#include <string>
#include "../utility/clsString.h"
#include "TxtBox.h"

class EdtblTxtBox : public TxtBox
{
private:
    //value of initialtxt and value
    std::string initialTxt="";

    //indexs of saved pos in cursor list,this poss is the pos of value and initialtxt and flag to acces
    int nextOfValuePosIndex;

    //boolea value is_current to set flag 
    bool isUsingInitialTxt=true;

    //colors 
    UIsUtulity::FntColor initialtxtColor;

    //ancher
    Output::posType initialtxtAncher;



public:
    EdtblTxtBox(const int box_width,const UIsUtulity::BgColor box_color,const std::string&value,UIsUtulity::FntColor value_color,Output::posType value_ancher,const int left_margin, const int righ_margin,CursorCtrl * cursor,const std::string &initial_txt) :
    TxtBox(box_width,box_color,value,value_color,value_ancher,left_margin,righ_margin,cursor)
    {
        if (value.empty())
        {
            setValue(initialTxt);
            isUsingInitialTxt = true;
        }else isUsingInitialTxt = false;
    }

    void print(const int new_lines,const int tabs) override
    {
        TxtBox::displayOnScreen(new_lines,tabs);
        if (getFirstPrint()) nextOfValuePosIndex = getBeginOfValuePosIndex();
    }    

    //getters
    std::string getInitialTxt()const
    {
        return initialTxt;
    }

    UIsUtulity::FntColor getInitialTxtColor()const
    {
        return initialtxtColor;
    }

    Output::posType getInitialTxtAncher()const
    {return initialtxtAncher;}

    //setters
    void setInitialTxt(const std::string &new_val)
    {
        initialTxt = new_val;
    }

    void setInitialTxtColor(UIsUtulity::FntColor new_val)
    {
        initialtxtColor = new_val;
    }

    void setInitialTxtAncher(const Output::posType ancher)
    {initialtxtAncher = ancher;}

    //mthods
    void valuePush(const char &c,bool update_on_screen =false) 
    {
        if (getValue().length() == getTxtBoxWidth()) return;
        if (isUsingInitialTxt)
        {
            setValue("");
            setValueAncher(getValueAncher());
            setValueColor(getValueColor());
            isUsingInitialTxt=false;
            increaseCursorNextPosByChar();
        }
        TxtBox::valuePush(c,update_on_screen);
    }

    void valuePop(bool update_on_screen = false) 
    {
        if (getValue().empty()) return;
        TxtBox::valuePop(false);
        decreaseCursorNextPosByChar();
        if (getValue().empty())
        {
            setValueAncher(initialtxtAncher);
            setValueColor(initialtxtColor);
            setValue(initialTxt);
        }
        if (update_on_screen) updateValueOnScreen();
    }

    void increaseCursorNextPosByChar()
    {
        getCursorPtr()->updateSavedPos(nextOfValuePosIndex,getCursorPtr()->getPosX()+1,getCursorPtr()->getPosY());
    }

    void decreaseCursorNextPosByChar()
    {
        getCursorPtr()->updateSavedPos(nextOfValuePosIndex,getCursorPtr()->getPosX()-1,getCursorPtr()->getPosY());
    }

    void updateValueOnScreen() 
    {
        if (isUsingInitialTxt)
        {
            getCursorPtr()->moveToSavedPos(getBeginOfValuePosIndex());
            UIsUtulity::setColors(getTxtBoxColor(),initialtxtColor);
            getCursorPtr()->output(Output::getInPos(getTxtBoxWidth(),initialTxt,initialtxtAncher));
            UIsUtulity::resetColors();
            getCursorPtr()->moveToSavedPos(getBeginOfValuePosIndex());
        }else
        {
            TxtBox::updateOnscreen();
            getCursorPtr()->moveToSavedPos(nextOfValuePosIndex);
        }
    }
};
