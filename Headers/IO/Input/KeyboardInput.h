#pragma once

#include "../../StdIncludes.h"
#include "Input.h"

class KeyboardInput : public DevicesInput
{
private:

public:
    enum Key{ ArrLeft=75 , ArrRight=77 , ArrUp=72 , ArrDown=80 ,
              Enter=13 , Esc=27 , Backspace=8 , Tab=9 , Space= 32 ,Home   = 71,End    = 79,PgUp   = 73,PgDn   = 81,Insert = 82,Delete = 83,
              F1  = 59,F2  = 60,F3  = 61,F4  = 62,F5  = 63,F6  = 64,F7  = 65,F8  = 66,F9  = 67,F10 = 68,F11 = 133,F12 = 134,
              Num0 = '0', Num1 = '1',Num2 = '2',Num3 = '3',Num4 = '4',Num5 = '5',Num6 = '6',Num7 = '7',Num8 = '8',Num9 = '9',
              A = 'A',B = 'B',C = 'C',D = 'D',E = 'E',F = 'F',G = 'G',H = 'H',I = 'I',J = 'J',K = 'K',L = 'L',M = 'M',N = 'N',O = 'O',P = 'P',Q = 'Q',R = 'R',S = 'S',T = 'T',U = 'U',V = 'V',W = 'W',X = 'X',Y = 'Y',Z = 'Z',
              a = 'a',b = 'b',c = 'c',d = 'd',e = 'e',f = 'f',g = 'g',h = 'h',i = 'i',j = 'j',k = 'k',l = 'l',m = 'm',n = 'n',o = 'o',p = 'p',q = 'q',r = 'r',s = 's',t = 't',u = 'u',v = 'v',w = 'w',x = 'x',y = 'y',z = 'z',
              None = -1
            };

    static bool isExist(const Key key,const std::vector <Key> keys)
    {
        for (const Key k : keys)
        {
            if (k == key) return true;
        }
        return false;
    }

    static Key getKeyPressed()
    {
        int pressed = getch();
        if (pressed == 224 || pressed == 0)
        {
            return (Key)getch();
        }
        return (Key)pressed;
    }

    static bool isPress(Key key)
    {
        return key == getKeyPressed();
    }

    static bool isPressAnyOf(const std::vector <Key> wait_for_press_keys)
    {
        return isExist(getKeyPressed(),wait_for_press_keys);
    }

    static void waitToPress(const Key wait_for_press_key)
    {
        Key key=None;
        while (key != wait_for_press_key)
        {
            key = getKeyPressed();
        }
    }

    static Key waitToPressAnyOf(const std::vector<Key> wait_for_press_keys)
    {
        Key key=None;
        while (!isExist(key,wait_for_press_keys))
        {
            key = getKeyPressed();
        }
        return key;
    }

    static Key waitToPressAnyKey()
    {
        Key keyPressed = None;
        while (keyPressed == None)
        {
            keyPressed = getKeyPressed();
        }
        return keyPressed;
    }

    static bool isToPressAnyKey()
    {
        return getKeyPressed() != None;
    }

    static Key waitToPressUnSpecialKey()
    {
        int key;
        key = getch();
        while (key == 0 or key == 224)
        {
            getch();
            key=getch();
        }
        return Key(key);
    }

    static Key waitToPressUnSpecialOrAnyOf(const std::vector <Key> keys)
    {
        int key;
        key = getch();
        while (key == 0 or key == 224)
        {
            key = getch();
            if (isExist((Key)key,keys)) return (Key)key;

            key = getch();
        }
        return Key(key);
    }

};