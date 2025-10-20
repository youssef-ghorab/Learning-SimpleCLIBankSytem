#pragma once

#include <string>
#include "../ProccessObjcts/User.h"
#include "../ProccessObjcts/Date.h"
#include <fstream>
#include "../utility/clsString.h"
#include "../ExcepAndErr/ExcepAndErr.h"

class loger
{
private:
    static const std::string dateFormat;

public:    
    enum class LogStructState{Empty, Filled};

    static const std::string delimiter;
    static const std::string loginLogFileName;
    static const std::string transferLogFileName;

    static const int loginLogPartsNumber = 3;
    static const int TransferLogPartsNumber = 7;

    struct LoginLog
    {
        std::string time;
        std::string userAccNum;
        std::string permissioons;
        LogStructState state = LogStructState::Empty;
    };

    struct TransferLog
    {
        std::string time;
        std::string senderAccNum;
        std::string receiverAccNum;
        std::string amount;
        std::string sndrBlncAftrTrnsfr;
        std::string rcvrBlncAftrTrnsfr;
        std::string username;
        LogStructState state = LogStructState::Empty;
    };


private:
    static ExcepAndErr::errState addLineToLogFile(const std::string &line,const std::string LogFileName)
    {
        fstream logFile;

        logFile.open(LogFileName,std::ios::app);

        if (!logFile.is_open()) return ExcepAndErr::failedToOpenFile;

        logFile << line << std::endl;

        logFile.close();
        return ExcepAndErr::noErr;
    }

    static std::string userToLoginLogLine(const User &usr)
    {
        std::string logLine;
        int perms; 
        
        logLine = "";
        perms = Permissions::permissionsVecToInt(usr.getPermissions().getHasPermission());

        logLine += Date::DateToStrFormat(Date::GetSysLocalDate(),dateFormat);
        logLine += delimiter + usr.getUsername();
        logLine += delimiter + std::to_string(perms);

        return logLine;
    }

public:    

    static string logToString(const TransferLog &log)
    {
        string s = "";
        s += log.time + delimiter;
        s += log.senderAccNum + delimiter;
        s += log.receiverAccNum + delimiter;
        s += log.amount + delimiter;
        s += log.sndrBlncAftrTrnsfr + delimiter;
        s += log.rcvrBlncAftrTrnsfr + delimiter;
        s += log.username;

        return s;
    }

    static string logToString(const LoginLog&log)
    {
        string s = "";
        s += log.time + delimiter;
        s += log.userAccNum + delimiter;
        s += log.permissioons + delimiter;

        return s;
    }

    static LoginLog stringToLoginLog(const std::string &s)
    {
        LoginLog log;
        std::vector<std::string> parts = clsString::Split(s,delimiter);
        if (parts.size() != loginLogPartsNumber) return log;

        log.time = parts[0];
        log.userAccNum = parts[1];
        log.permissioons = parts[2];
        log.state = LogStructState::Filled;

        return log;
    }

    static TransferLog stringToTransferLog(const std::string &s)
    {
        TransferLog log;
        std::vector<std::string> parts = clsString::Split(s,delimiter);
        if (parts.size() != TransferLogPartsNumber) return log;

        log.time = parts[0];
        log.senderAccNum = parts[1];
        log.receiverAccNum = parts[2];
        log.amount = parts[3];
        log.sndrBlncAftrTrnsfr = parts[4];
        log.rcvrBlncAftrTrnsfr = parts[5];
        log.username = parts[6];
        log.state = LogStructState::Filled;

        return log;
    }

    static void registerUser(const User &usr)
    {
        std::string logLine = userToLoginLogLine(usr);
        addLineToLogFile(logLine,loginLogFileName);
    }

    static ExcepAndErr::errState registerTransfer(const Client * const c1, const Client * const c2,const float amount,const std::string &username)
    {
        if (c1 == nullptr || c2 == nullptr) return ExcepAndErr::invalidePtr;

        TransferLog log;

        log.time = Date::DateToStrFormat(Date::GetSysLocalDate(),dateFormat);
        log.senderAccNum = c1->getAccountNumber();
        log.receiverAccNum = c2->getAccountNumber();
        log.amount = std::to_string(amount);
        log.sndrBlncAftrTrnsfr = std::to_string(c1->getBalance());
        log.rcvrBlncAftrTrnsfr = std::to_string(c2->getBalance());
        log.username = username;
        log.state = LogStructState::Filled;

        return addLineToLogFile(logToString(log),transferLogFileName);
    }

    static std::vector<std::string> getLog(const std::string &file_name)
    {
        fstream logFile;
        std::vector<std::string> log ;        
        logFile.open(file_name,std::ios::in);

        if (!logFile.is_open()) return log;

        std::string line= "";

        while(std::getline(logFile,line)){ log.push_back(line) ; }

        return log;
    }

};

const std::string loger::delimiter = "*//*";
const std::string loger::loginLogFileName = "Logs/LoginLog.txt";
const std::string loger::transferLogFileName = "Logs/TransferLog.txt";
const std::string loger::dateFormat = "dd/mm/yyyy-hh:mn:ss";