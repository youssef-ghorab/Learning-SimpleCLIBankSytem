#include <fstream>
#include <string>
#include "../ExcepAndErr/ExcepAndErr.h"
#include "../ProccessObjcts/Client.h"
#include "../utility/Crypte.h"

#include <vector>

class DataFile
{
private:   
    enum openMode{ read, rewrite ,app};

    std::string dataDelimiter;
    std::string filePath;
    std::fstream file;
    bool contentEncrypt;

    ExcepAndErr::errState openTo(const std::ios::openmode open_mode)
    {
        file.open(filePath,open_mode);
        if(!file.is_open()) return ExcepAndErr::failedToOpenFile;
        return ExcepAndErr::noErr;
    }

    ExcepAndErr::errState openInMode(const openMode open_mode)
    {
        switch (open_mode)
        {
        case read:
            return openTo(std::ios::in);
        case rewrite:
            return openTo(std::ios::out);
        case app:
            return openTo(std::ios::app | std::ios::out);
        }
        return ExcepAndErr::noErr;
    }

    bool isDataDelimiterValid(const std::string &s)
    {
        if (s.empty()) return false;
        for (const char &c : s)
        {
            if (c == ' ') return false;
        }
        return true;
    }

public:
    DataFile(const std::string &file_path,const std::string &data_delimiter,const bool content_encrypt)
    {
        if (!isDataDelimiterValid(data_delimiter)) ExcepAndErr::throwRunTimeExcep("data layer :dataDelimiter invalide.");

        filePath = file_path;
        dataDelimiter = data_delimiter; 
        contentEncrypt = content_encrypt;
    };

    ~DataFile()
    {
        if (file.is_open()) file.close(); 
    }

    template <typename T> ExcepAndErr::errState add(const std::vector <T> &objects)
    {
        ExcepAndErr::errState state = openInMode(app);
        if (state != ExcepAndErr::noErr) return state;

        std::string line;

        for (const T &object : objects)
        {
            line = object.toLine(dataDelimiter);
            if (contentEncrypt) line = Crypt::encryptText(line);
            file << line << "\n";
        }
        file.close();
        return ExcepAndErr::noErr;
    }

    template <typename T> ExcepAndErr::errState add(const T &object)
    {
        ExcepAndErr::errState state = openInMode(app);
        if (state != ExcepAndErr::noErr) return state;
        std::string line = object.toLine(dataDelimiter);

        if (contentEncrypt) line = Crypt::encryptText(line);

        file << line << "\n";

        file.close();
        return ExcepAndErr::noErr;
    }

    template <typename T> ExcepAndErr::errState save(const std::vector <T> &objects)
    {
        ExcepAndErr::errState state = openInMode(rewrite);
        if (state != ExcepAndErr::noErr) return state;
        
        std::string line;

        for (const T &object : objects)
        {
            line = object.toLine(dataDelimiter);
            if (contentEncrypt) line = Crypt::encryptText(line);
            file << line << "\n";
        }

        file.close();
        return ExcepAndErr::noErr;
    }

    template <typename T> ExcepAndErr::errState load(std::vector <T> &objects)
    {
        ExcepAndErr::errState state = openInMode(read);
        if (state != ExcepAndErr::noErr) return state;

        objects.clear();

        std::string line;
        while(std::getline(file,line))
        {
            if (contentEncrypt) line = Crypt::decryptText(line);
            objects.push_back(T::lineToSelf(line,dataDelimiter));
        }

        file.close();
        return ExcepAndErr::noErr;
    }
};