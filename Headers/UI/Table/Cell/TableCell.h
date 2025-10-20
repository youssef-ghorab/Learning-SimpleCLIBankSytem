#pragma once

#include "../../UIsUtility.h"
#include <string>
#include "../../ScreenIO/Input.h"
#include "../../CrsrCtrl.h"

class TableCell
{
private:
    std::string txt;
    UIsUtulity::FntColor txtColor;
    UIsUtulity::BgColor bgColor;
    int width;
    Output::posType txtPos;

public:
    //enum Modes{SameTxt,sameBgColor,SameTxtColor,SameWidth, SameTxtPos,SameCurrentBgColor,SameCurrentFntColor};

    TableCell(const std::string &txt,const UIsUtulity::FntColor txt_color,const UIsUtulity::BgColor bg_color,const int width,const Output::posType txt_pos)
    : txt(txt),txtColor(txt_color),bgColor(bg_color),width(width),txtPos(txt_pos) {}

    TableCell()
    : txt("empty"),txtColor(UIsUtulity::FntWhite),bgColor(UIsUtulity::BgBlack),width(10),txtPos(Output::Center){}

    void print() const
    {
        UIsUtulity::setBgColor(bgColor);
        UIsUtulity::setFntColor(txtColor);
        Output::printInPos(width,txt,txtPos);
        UIsUtulity::resetColors();
    }

    void print( UIsUtulity::BgColor &current_bg_color, UIsUtulity::FntColor &current_fnt_color) const
    {
        if (current_bg_color!=bgColor) 
        {
            UIsUtulity::setBgColor(bgColor);
            current_bg_color = bgColor;
        }
        if (current_fnt_color!=txtColor) 
        {
            UIsUtulity::setFntColor(txtColor);
            current_fnt_color = txtColor;
        }
        Output::printInPos(width,txt,txtPos);
    }

    void print( UIsUtulity::BgColor &current_bg_color, UIsUtulity::FntColor &current_fnt_color,CursorCtrl &crsrCntrl) const
    {
        if (current_bg_color!=bgColor) 
        {
            UIsUtulity::setBgColor(bgColor);
            current_bg_color = bgColor;
        }
        if (current_fnt_color!=txtColor) 
        {
            UIsUtulity::setFntColor(txtColor);
            current_fnt_color = txtColor;
        }
        crsrCntrl.output(Output::getInPos(width,txt,txtPos));
    }

    void setTxt( const std::string &txt)
    {
        this->txt = txt;
    }

    void setBgColor(UIsUtulity::BgColor bg_color)
    {
        bgColor = bg_color;
    }

    void setTxtColor(UIsUtulity::FntColor txt_color)
    {
        txtColor = txt_color;
    }

    void setWidth(const int width)
    {
        this->width = width;
    }

    void setTxtPos(Output::posType txt_pos)
    {
        txtPos = txt_pos;
    }

    //getters
    const std::string &getTxt() const
    {return txt;}

    UIsUtulity::BgColor getBgColor() const
    {return bgColor;}

    UIsUtulity::FntColor getTxtColor() const
    {return txtColor;}

    int getWidth() const
    {return width;}

    Output::posType getTxtPos() const
    {return txtPos;}

};