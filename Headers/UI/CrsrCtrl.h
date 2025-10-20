#pragma once

#include "UI.h"
#include <vector>
#include <iostream>
#include "../IO/IOIncludes.h"

class CursorCtrl 
{
private:
    struct Pos 
    {
        int x = 1;
        int y = 1;
        Pos() = default;
        Pos(int x, int y) : x(x), y(y) {}
    };

    Pos cursorPos;
    std::vector<Pos> savedPoss;

public:
    CursorCtrl() : cursorPos(1,1){}

    void removeSavedPos(const int pos_index)
    { 
        if (pos_index < 0 || pos_index >= savedPoss.size()) return;
        savedPoss.erase(savedPoss.begin()+pos_index);
    }

    int saveCurrentCursorPos()
    {
        savedPoss.push_back(Pos(cursorPos.x,cursorPos.y));
        return savedPoss.size()-1;
    }

    int savePos(const int x,const int y)
    {
        savedPoss.push_back(Pos(x,y));
        return savedPoss.size()-1;
    }

    void moveUp(const int distance = 1)
    {
        cursorPos.y -= distance;
        std::cout << ("\033[" + std::to_string(distance) + "A");
    }

    void moveDown(const int distance = 1)
    {
        cursorPos.y += distance;
        std::cout << ("\033[" + std::to_string(distance) + "B");
    }

    void moveRight(const int distance = 1)
    {
        cursorPos.x += distance;
        std::cout << ("\033[" + std::to_string(distance) + "C");
    }

    void moveLeft(const int distance = 1)
    {
        cursorPos.x -= distance;
        std::cout << ("\033[" + std::to_string(distance) + "D");
    }

    void reset()
    {
        savedPoss.clear();
        cursorPos = Pos();
    }

    void moveTo(const int x,const int y)
    {
        Pos target = Pos(x,y);

        //move to target line
        while (cursorPos.y < target.y) moveDown();
        while (cursorPos.y > target.y) moveUp();

        //move to target colon
        while (cursorPos.x < target.x) moveRight();
        while (cursorPos.x > target.x) moveLeft();
    }

    void moveTo(Pos target)
    {
        //move to target line
        while (cursorPos.y < target.y) moveDown();
        while (cursorPos.y > target.y) moveUp();

        //move to target colon
        while (cursorPos.x < target.x) moveRight();
        while (cursorPos.x > target.x) moveLeft();
    }

    void anlyzeInput(const std::string &input)
    {
        for (const char &c : input)
        {
            if (c == '\n') 
            {
                cursorPos.y++;
                cursorPos.x=1;
            }else if (c == '\t')
            {
                cursorPos.x+=4;
            }
            else
            {
                cursorPos.x++;
            }
        }
    }

    void output(const std::string &s)
    {
        anlyzeInput(s);
        std::cout << s;
    }

    void moveToSavedPos(const int saved_pos_index)
    {
        if (saved_pos_index >= savedPoss.size()) return;
        moveTo(savedPoss[saved_pos_index]);
    }

    int getPosX()
    {return cursorPos.x;}

    int getPosY()
    {return cursorPos.y;}

    std::vector<Pos>& getSavedPoses()
    {return savedPoss;}

    void updateSavedPos(const int index,const Pos new_val)
    {
        savedPoss[index] = new_val;
    }

    void updateSavedPos(const int index,const int x, const int y)
    {
        updateSavedPos(index,Pos(x,y));
    }

    Pos getPos()
    {
        return cursorPos;
    }

};