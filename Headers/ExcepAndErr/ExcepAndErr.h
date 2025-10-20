#pragma once

#include <string>
#include <stdexcept>

class ExcepAndErr
{
public:
    enum errState{noErr,failedToOpenFile,vectorOutOfRange,fileNotExist,invalidePtr,invalideAccountNumber,invalideBalanceToSet,permissionNotExist,PermissionAlreadyExis};
    enum exceptionType{invalidArgument,outOfRange,runTimeErr};

    static void throwGenericExcep()
    {
        throw std::exception();
    }

    static void throwInvalideArgExcep(const std::string &execption_txt)
    {
        throw std::invalid_argument(execption_txt);
    }

    static void throwOutOfRangExcep(const std::string &execption_txt)
    {
        throw std::out_of_range(execption_txt);
    }

    static void throwIfStringEmpty(const std::string &string,const std::string &string_name)
    {
        if (string.empty())
        {
            throwInvalideArgExcep(string_name+" cannot be empty.");
        }
    }

    static void throwRunTimeExcep(const std::string &execption_txt)
    {
        throw std::runtime_error(execption_txt);
    }

    static void throwExcep(const exceptionType excep_type,const std::string &execption_txt)
    {
        switch (excep_type)
        {
        case invalidArgument:
            throwInvalideArgExcep(execption_txt);
        case outOfRange:
            throwOutOfRangExcep(execption_txt);
        default:
            throwGenericExcep();
        }
    }


};
