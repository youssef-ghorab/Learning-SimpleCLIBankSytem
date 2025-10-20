#pragma once

#include "UIsUtility.h"
#include "Global.h"
#include "../ProccessObjcts/Date.h"

class UI
{
private:

    static void printUsername(const std::string &label,const std::string value, const int spaces)
    {
        UIsUtulity::setFntColor(UIsUtulity::FntWhite); 
        Output::print(label);
        UIsUtulity::setFntColor(currentUser::instance().getUserPtr() ? UIsUtulity::FntGreen: UIsUtulity::FntRed);
        Output::print(value);
        if (spaces <= 0) return;
        Output::print(std::string(spaces,' '));
    }

    static void printDate(const std::string &label,const std::string value, const int spaces)
    {
        if (spaces > 0) Output::print(std::string(spaces,' '));       
        UIsUtulity::setFntColor(UIsUtulity::FntWhite); 
        Output::print(label);
        UIsUtulity::setFntColor(UIsUtulity::FntYallow);
        Output::print(value);
    }

    static void printTitle(const int border_width,const char border,const std::string &title,const std::string &sub_title)
    {
        Output::print(std::string(border_width,border),false);
        Output::print("",true);
        Output::printInPos(border_width,title,Output::Center);
        Output::printInPos(border_width,sub_title,Output::Center);
    }

    static void printInfo(const int border_width)
    {
        std::string label,value;
        int spaces;

        UIsUtulity::resetColors();

        label = "\nUsername : ";
        value = (currentUser::instance().getUserPtr() ? currentUser::instance().getUserPtr()->getUsername() : "NOT LOGIN YET");
        spaces = (border_width/2)-(label.length()+value.length());

        printUsername(label,value,spaces);

        label = "Date : ";
        value = Date::DateToStrFormat(Date::GetSysLocalDate(),"dd/mm/yyyy");
        spaces = (border_width/2)-(label.length()+value.length());

        printDate(label,value,spaces);
        
        UIsUtulity::resetColors();
    }

public:
    static const int screen_width = 120;

    static void printScreenHeader(const std::string screen_name, UIsUtulity::BgColor bg_color ,const UIsUtulity::FntColor name_color,const UIsUtulity::FntColor border_color,const char border,int border_width)
    {
        UIsUtulity::setFntColor(border_color);
        Output::print(std::string(border_width,border),false);
        Output::print("",true);
        UIsUtulity::setFntColor(name_color);
        Output::printInPos(border_width,screen_name,Output::Center);
        printInfo(border_width);
        UIsUtulity::setFntColor(border_color);
        Output::print(std::string(border_width,border),true);
    }

    static void printScreenHeader(const std::string &title,const std::string &sub_title,const char border,int border_width)
    {
        printTitle(border_width,border,title,sub_title);

        printInfo(border_width);

        Output::print(std::string(border_width,border),true);
    }

    virtual void show() = 0;
};