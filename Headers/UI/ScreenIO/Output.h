#pragma once

#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>

#include "../../IO/Input/KeyboardInput.h"

class Output
{
public:
    enum posType{Left , Right , Center};

    template <typename T> static void print(const T &output,bool inNewLine = false)
    {
        if (inNewLine) std::cout << "\n";
        std::cout << output;
    }

    static void clearScreen()
    {
        system("cls");
        //std::cout << "\033[H\033[J";
    }

    static void pressAnyKeyToContinue()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\npress any key to continue...";
        KeyboardInput::waitToPressAnyKey();
    }

    static void printInPos(short width,const std::string &txt,const posType pos)
    {
        if (txt.length() >= width) 
        {
            std::cout << txt.substr(0,width);
            return;
        }

        switch (pos)
        {
            case Left:
            {
                std::cout << std::setw(width) << std::left << txt;
                break;
            }
            case Right:
            {
                std::cout << std::setw(width) << std::right << txt;
                break;
            }
            case Center:
            {
                int spaces = width - txt.length();
                int leftSpaces = spaces/2;
                int rightSpaces = spaces-leftSpaces;

                std::cout 
                << std::string(leftSpaces, ' ')  
                << txt 
                << std::string(rightSpaces, ' ');
                
                break;
            }
            
            

        }
    }

    static std::string getInPos(short width,const std::string &txt,const posType pos)
    {
        if (txt.length() > width) return txt.substr(0,width);
        switch (pos)
        {
            case Left:
            {
                return txt + std::string(width-txt.length(),' ');
            }
            case Right:
            {
                return std::string(width-txt.length(), ' ') + txt ;
            }
            case Center:
            {
                int spaces = width - txt.length();
                int leftSpaces = spaces/2;
                int rightSpaces = spaces-leftSpaces;

                return std::string(leftSpaces, ' ') + txt + std::string(rightSpaces, ' ');
            }
            default:
                return txt;
        }
        return txt;
    }

    static std::string getValideInPosAndReturnRemainderSpaces(short width,const std::string &txt,const posType pos,int &remaind_spaces_number)
    {
        if (txt.length() >= width) 
        {
            remaind_spaces_number =0;
            return txt.substr(0,width);
        }

        switch (pos)
        {
            case Left:
            {
                remaind_spaces_number = width - txt.length();
                return txt;
            }
            case Right:
            {
                remaind_spaces_number= 0;
                return std::string(width-txt.length(),' ') + txt;
            }
            case Center:
            {
                int spaces = width - txt.length();
                int leftSpaces = spaces/2;
                int rightSpaces = spaces-leftSpaces;
                
                remaind_spaces_number = rightSpaces;
                return std::string(leftSpaces, ' ')  + txt ;
                
            }
        }
        remaind_spaces_number= 0;
        return txt;
    }

    static void printFor(const std::string &s,const int amount)
    {
        for (int i = 0 ; i < amount;i++) std::cout << s;
    }

    static std::string getFor(const std::string &s,const int amount)
    {
        std::string fullS ="";
        for (int i = 0 ; i < amount;i++) fullS += s;
        return fullS;
    }

};