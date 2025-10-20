#pragma once

#include "Person.h"
#include "../Utility/clsString.h"
#include "../ExcepAndErr/ExcepAndErr.h"

class Client : public Person<Client>
{
private:
    std::string accountNumber;
    std::string pinCode;
    float balance;

public:
    //constractor
    Client(const std::string &first_name,const std::string &last_name,const std::string &email,const std::string &phone_number,const std::string &account_number,const std::string &pin_code,const float balance) : Person(first_name,last_name,email,phone_number) , accountNumber(account_number) , pinCode(pin_code) , balance(balance)
    {
    }

    //copy constractor
    Client(const Client &client) : Person(client.getFirstName(),client.getLastName(),client.getEmail(),client.getPhoneNumber())
    {
        accountNumber = client.getAccountNumber();
        pinCode = client.getPinCode();
        balance = client.getBalance();
    }

    //setters
    void setAccountNumber(const std::string &account_number)
    {
        accountNumber = account_number;
    }

    void setPinCode(const std::string &pin_code)
    {
        pinCode = pin_code;
    }

    ExcepAndErr::errState setBalance(const float &balance) 
    {
        if (balance < 0) return ExcepAndErr::invalideBalanceToSet;
        this->balance = balance;
        return ExcepAndErr::noErr;
    }

    //getters
    const std::string &getAccountNumber() const
    {
        return accountNumber;
    }

    const std::string &getPinCode() const
    {
        return pinCode;
    }

    const float getBalance() const
    {
        return balance;
    }

    //methods
    static bool isSameAccountNumberAndPinCode(const Client &client1,const Client &client2)
    {
        return (client1.getAccountNumber() == client2.getAccountNumber() && client1.getPinCode() == client2.getPinCode());
    }

    bool isSameAccountNumberAndPinCodeOf(const Client &client)
    {
        return isSameAccountNumberAndPinCode(*this,client);
    }

    static TypeId getTypeId()
    {return TypeId::Client;} 

    //statics
    static Client creatEmptyClient()
    {
        return Client("","","","","","",0);
    }
    
    static Client lineToSelf(const std::string &line,const std::string &delimiter)
    {
        std::vector <std::string> clientParts = clsString::Split(line,delimiter);
        
        if (clientParts.size() != 7) ExcepAndErr::throwOutOfRangExcep("clients part size =! 7 !");

        Client client = creatEmptyClient();

        client.setFirstName(clientParts[0]);
        client.setLastName(clientParts[1]);
        client.setEmail(clientParts[2]);
        client.setPhoneNumber(clientParts[3]);
        client.setAccountNumber(clientParts[4]);
        client.setPinCode(clientParts[5]);
        client.setBalance(std::stof(clientParts[6]));

        return client;
    }

    static std::string selfToLine(const Client &C,const std::string &delimier)
    {
        return Person::personToLine((Person)C,delimier) + delimier + C.getAccountNumber() + delimier + C.getPinCode() + delimier + std::to_string(C.getBalance());
    }

    std::string toLine(const std::string &delimiter) const override
    {
        return Person::toLine(delimiter) + delimiter + accountNumber + delimiter + pinCode + delimiter + std::to_string(balance);
    }

    std::string getIdentifier() const
    {
        return accountNumber;
    }

    std::string getPassword() const
    {return pinCode;}

    void setIdentifier(const std::string &new_val)
    {
        accountNumber = new_val;
    }

};
