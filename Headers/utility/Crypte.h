#include <string>
#include "../ProccessObjcts/Date.h"
#include <vector>


class Crypt
{
private:
    static const int key = 3;

public:

    static std::string encryptText(const std::string &org_txt)
    {
        std::string encryptedTxt;

        for (char c : org_txt) encryptedTxt.push_back(c + key);

        return encryptedTxt;
    }

    static std::string decryptText(const std::string &org_txt)
    {
        std::string decryptedTxt;

        for (char c : org_txt) decryptedTxt.push_back(c - key);

        return decryptedTxt;
    }

};
