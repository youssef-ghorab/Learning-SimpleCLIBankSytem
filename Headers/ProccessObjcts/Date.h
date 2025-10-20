#pragma once

#include <string>
#include <ctime>

class Date
{
public:
    long long year;
    short month;
    short day;
    short hour=0;
    short minute=0;
    short seconds=0;

private:
    static std::string ReplaceWorldInTxt(std::string Txt, const std::string &WORD_TARGET, const std::string REPLACE_TO)
    {
        short Pos ;
       std::string TxtModified = "";

        Pos = Txt.find(WORD_TARGET,0);

        while (Pos != Txt.npos)
        {
            TxtModified += Txt.substr(0,Pos) + REPLACE_TO;
            Txt.erase(0,Pos+WORD_TARGET.length());
            Pos = Txt.find(WORD_TARGET);
        }

        if (!Txt.empty()) TxtModified += Txt;

        return TxtModified;
    }

public:
    static std::string DateToStrFormat(const Date date, const std::string FORMAT = "dd/mm/yyyy")
    {
        std::string Txt;

        Txt = ReplaceWorldInTxt(FORMAT,"dd",std::to_string(date.day));
        Txt = ReplaceWorldInTxt(Txt,"mm",std::to_string(date.month));
        Txt = ReplaceWorldInTxt(Txt,"yyyy",std::to_string(date.year));
    
        Txt = ReplaceWorldInTxt(Txt,"hh",std::to_string(date.hour));
        Txt = ReplaceWorldInTxt(Txt,"mn",std::to_string(date.minute));
        Txt = ReplaceWorldInTxt(Txt,"ss",std::to_string(date.seconds));

        return Txt;
    }
    
    static Date GetSysLocalDate()
    {
        Date SysLocalDate;

        time_t Time = time(0);
        tm* TimeNow = localtime(&Time);

        SysLocalDate.year = TimeNow->tm_year+1900;
        SysLocalDate.month = TimeNow->tm_mon+1;
        SysLocalDate.day = TimeNow->tm_mday;
        SysLocalDate.hour = TimeNow->tm_hour;
        SysLocalDate.minute = TimeNow->tm_min;
        SysLocalDate.seconds = TimeNow->tm_sec;

        return SysLocalDate;
    }
};