#pragma once

#include <string>
#include "../utility/clsString.h"
#include <exception>

class Currency 
{
private:
    std::string country;
    std::string code;
    std::string name;
    float rate;

public:
    enum class Identifier{Code=1 , Country};

    Currency(const std::string &country,const std::string& code ,const std::string &name , const float rate)
    : country(country),code(code),name(name),rate(rate)
    {}

    Currency() //EMPTY
    : country(""),code(""),name(""),rate(0.0f)
    {}

    std::string getCountry() const
    {return country;}

    std::string getCode() const
    {return code;}

    std::string getName() const
    {return name;}

    bool setRate(const float new_rate)
    {
        if (new_rate < 0) return false;
        rate = new_rate;
        return true;
    }

    float getRate() const
    {return rate;}

    std::string toLine(const std::string& delimiter) const
    {
        std::string line = "";

        line += country + delimiter;
        line += code + delimiter;
        line += name + delimiter;
        line += std::to_string(rate);

        return line;
    }

    static Currency lineToSelf(const std::string& line ,const std::string& delimiter)
    {
        std::vector<std::string> parts = clsString::Split(line,delimiter);

        std::cout << "Line read: [" << line << "]\n";
        if (parts.size() != 4) throw std::invalid_argument("invalide line to convert to currency (func -> Currency::lineToSelf) : line parts size != 4");

        return Currency(parts[0],parts[1],parts[2],std::stof(parts[3]));
    }

    bool isEmpty() const
    {
        return country.empty() && code.empty() && name.empty() && rate == 0.0f;
    }

    const std::string &getId(Identifier id)
    {
        switch (id)
        {
        case Identifier::Code: return code;
        case Identifier::Country: return country;
        
        default:
            break;
        }
    }
};