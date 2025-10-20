#pragma once

#include <vector>
#include <fstream>
#include <stdexcept>
#include "../ExcepAndErr/ExcepAndErr.h" 

#include "Client.h"
#include "User.h"
#include "Currency.h"
#include "../Data/Data.h"
#include "Loger.h"
#include "../UI/Global.h"

class Bank
{
private:
    std::vector<Client> clients;
    std::vector<User> users;
    std::vector<Currency> currencies;

    // لادارة ملفات 
    DataFile usersDataFile;
    DataFile clientsDataFile;
    DataFile currenciesDataFile;

public:

    // --- getters ---
    std::vector<Client>* getClientsPtr() 
    { return &clients; }

    std::vector<User>* getUsersPtr() 
    { return &users; }

    std::vector<Currency>* getCurrenciesPtr() 
    { return &currencies; }

    const std::vector<Client>* getConstClientsPtr() const 
    { return &clients; }

    const std::vector<User>* getConstUsersPtr() const 
    { return &users; }

    const std::vector<Currency>* getConstCurrenciesPtr() const 
    { return &currencies; }

    DataFile* getClientsDataFile() 
    { return &clientsDataFile; } 

    DataFile* getUsersDataFile() 
    { return &usersDataFile; } 

    DataFile* getCurrenciesDataFile() 
    { return &currenciesDataFile; } 

   
    Client* findClient(const std::string& identifier, bool by_password = false, const std::string& password = "")
    {
        for (Client& c : clients)
        {
            if (c.getIdentifier() == identifier && (!by_password || c.getPassword() == password))
                return &c;
        }
        return nullptr;
    }

  
    const std::vector<User> &getUsers() const
    {
        return users;
    }

    const std::vector<Client> &getClients() const
    {
        return clients;
    }

    const std::vector<Currency> &getCurrencies() const
    {
        return currencies;
    }

    User* findUser(const std::string& identifier, bool by_password = false, const std::string& password = "")
    {
        for (User& u : users)
        {
            if (u.getIdentifier() == identifier && (!by_password || u.getPassword() == password))
                return &u;
        }
        return nullptr;
    }

    Currency* findCurrency(Currency::Identifier id_type,const std::string &id)
    {
        for (Currency &c : currencies)
        {
            if (clsString::LowerAllString(c.getId(id_type)) == clsString::LowerAllString(id))
                return &c;
        }
        return nullptr;
    }
    
    const Client* findClient(const std::string &identifier, const bool &by_password = false, const std::string &password = "") const
    {
        for (const Client &c : clients)
        {
            if (c.getAccountNumber() == identifier) return &c;
        }
        return nullptr;
    }

    const User* findUser(const std::string &identifier, const bool &by_password = false, const std::string &password = "") const
    {
        for (const User &u : users)
        {
            if (u.getUsername() == identifier) return &u;
        }
        return nullptr;
    }

    ExcepAndErr::errState addClient(const Client &client, bool add_to_file = true)
    {
        clients.push_back(client);
        if (add_to_file) return clientsDataFile.add(client);
        return ExcepAndErr::noErr;
    }

    ExcepAndErr::errState addUser(const User& user, bool add_to_file = true)
    {
        users.push_back(user);
        if (add_to_file) return usersDataFile.add(user);
        return ExcepAndErr::noErr;
    }

    ExcepAndErr::errState addCurrency(const Currency& currency, bool add_to_file = true)
    {
        currencies.push_back(currency);
        if (add_to_file) return currenciesDataFile.add(currency);
        return ExcepAndErr::noErr;
    }

    ExcepAndErr::errState deleteClient(const std::string& identifier, bool delete_from_file = true)
    {
        for (auto it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->getIdentifier() == identifier)
            {
                clients.erase(it);
                break;
            }
        }
        if (delete_from_file) return clientsDataFile.save(clients);
        return ExcepAndErr::noErr;
    }

    ExcepAndErr::errState deleteUser(const std::string& identifier, bool delete_from_file = true)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->getIdentifier() == identifier)
            {
                users.erase(it);
                break;
            }
        }
        if (delete_from_file) return usersDataFile.save(users);
        return ExcepAndErr::noErr;
    }

    //اخديت مستحدم
    ExcepAndErr::errState updateClient(const std::string& identifier, Client& new_data)
    {
        Client* c = findClient(identifier);
        if (!c) return ExcepAndErr::invalidePtr;
        *c = new_data;
        return clientsDataFile.save(clients);
    }

    ExcepAndErr::errState updateUser(const std::string& identifier, User& new_data)
    {
        User* u = findUser(identifier);
        if (!u) return ExcepAndErr::invalidePtr;
        *u = new_data;
        return usersDataFile.save(users);
    }

    ExcepAndErr::errState updateCurrencyRate(Currency::Identifier id_type,const std::string &id,const short new_rate)
    {
        Currency* c = findCurrency(id_type,id);
        if (!c) return ExcepAndErr::invalidePtr;
        c->setRate(new_rate);
        return currenciesDataFile.save(currencies);
    }

    ExcepAndErr::errState makeClientBalanceProcess(const std::string& account_number, float amount)
    {
        Client* c = findClient(account_number);
        if (!c) return ExcepAndErr::invalideAccountNumber;
        ExcepAndErr::errState state = c->setBalance(c->getBalance() + amount);
        if (state == ExcepAndErr::noErr)
            return clientsDataFile.save(clients);
        return state;
    }

    ExcepAndErr::errState transfer(const std::string& acc_num1, const std::string& acc_num2, float amount)
    {
        if (acc_num1 == acc_num2) return ExcepAndErr::noErr;

        Client* c1 = findClient(acc_num1);
        Client* c2 = findClient(acc_num2);

        ExcepAndErr::errState prccssStt;

        if (!c1 || !c2) return ExcepAndErr::invalideAccountNumber;

        float c1Back = c1->getBalance();
        float c2Back = c2->getBalance();

        if ((prccssStt = makeClientBalanceProcess(acc_num1, -amount)) != ExcepAndErr::noErr)
        {
            c1->setBalance(c1Back);
            return prccssStt;
        }

        if ((prccssStt = makeClientBalanceProcess(acc_num2, amount)) != ExcepAndErr::noErr)
        {
            c1->setBalance(c1Back);
            c2->setBalance(c2Back);
            return prccssStt;
        }

        loger::registerTransfer(c1, c2, amount, currentUser::instance().getUser().getUsername());
        return ExcepAndErr::noErr;
    }

    Bank(const std::string& clients_file_path, bool clientq_file_content_encrypt,const std::string& users_file_path,bool users_file_content_encrypt, const std::string& currencies_file_path,bool currencies_file_content_encrypt, const std::string& data_delimiter)
        : clientsDataFile(clients_file_path, data_delimiter,clientq_file_content_encrypt),
          usersDataFile(users_file_path, data_delimiter,users_file_content_encrypt),
          currenciesDataFile(currencies_file_path, data_delimiter,currencies_file_content_encrypt)
    {
        clientsDataFile.load<Client>(clients);
        usersDataFile.load<User>(users);
        currenciesDataFile.load<Currency>(currencies);

        if (users.empty())
        {
            users.push_back(User("admin","admin","admin@example.com","0001","admin","admin",Permissions::getAllPermissions()));
            usersDataFile.save(users);
        }
    }
};
