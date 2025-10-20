#pragma once

#include "../ProccessObjcts/User.h"
#include "../ProccessObjcts/Loger.h"

class currentUser
{
    static User * usrPtr;

public:
    static currentUser &instance()
    {
        static currentUser currentUser;
        return currentUser;
    }

    void setUser(User * usr_ptr)
    {
        usrPtr = usr_ptr;
        if (usrPtr) loger::registerUser(*usr_ptr);
    }

    User &getUser()
    {
        return *usrPtr;
    }

    User *getUserPtr()
    {
        return usrPtr;
    }
};

User* currentUser::usrPtr = nullptr;