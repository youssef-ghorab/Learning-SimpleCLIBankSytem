#pragma once

#include <string>
#include "ScreenIO/Output.h"
#include "UIsUtility.h"

class ColorManager
{
private:
    UIsUtulity::BgColor consolBgColor;
    UIsUtulity::FntColor consolFntColor;

public:
    //statics
    void setFntColor(UIsUtulity::FntColor color)
    {
        Output::print("\033["+std::to_string(color)+"m",false);
        consolFntColor = color;
    }

    void setBgColor(UIsUtulity::BgColor color)
    {
        Output::print("\033["+std::to_string(color)+"m",false);
        consolBgColor = color;
    }

    void resetColors()
    {
        Output::print("\033[0m");
        consolBgColor = UIsUtulity::BgBlack;
        consolFntColor = UIsUtulity::FntWhite;
    }

    static std::string setTxtColor(const std::string &txt,const UIsUtulity::FntColor color)
    {
        return "\033["+std::to_string(color)+"m" + txt + "\033[0m";
    }// 

    void setColors(const UIsUtulity::BgColor bg_color,const UIsUtulity::FntColor fnt_color)
    {
        setBgColor(bg_color);
        setFntColor(fnt_color);

        consolBgColor=bg_color;
        consolFntColor=fnt_color;
    }

    void setToDarkThem()
    {
        setColors(UIsUtulity::BgBlack,UIsUtulity::FntWhite);
    }

    void setToLightThem()
    {
        setColors(UIsUtulity::BgWhite,UIsUtulity::FntBlack);
    }
};