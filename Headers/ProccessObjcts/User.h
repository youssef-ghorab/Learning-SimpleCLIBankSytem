#pragma once

#include "Person.h"
#include "../../../Strings/Headers/clsString.h"
#include "../ExcepAndErr/ExcepAndErr.h"
#include "Permissions.h"

class User : public Person<User>
{
private:
    std::string username;
    std::string password;
    Permissions permissions;

public:
    //constractor
    User(const std::string &first_name,const std::string &last_name,const std::string &email,const std::string &phone_number,const std::string &username,const std::string &password,Permissions permissions) 
    : Person(first_name,last_name,email,phone_number) , username(username) , password(password),permissions(permissions){}

    User() 
    : Person("","","","") , username("") , password(""),permissions(Permissions()){}

    //copy constractor
    User(const User &User) : Person(User.getFirstName(),User.getLastName(),User.getEmail(),User.getPhoneNumber())
    {
        username = User.getUsername();
        password = User.getPassword();
        permissions = User.getPermissions();
    }

    //setters
    void setUsername(const std::string &username)
    {
        this->username = username;
    }

    void setPassword(const std::string &password)
    {
        this->password = password;
    }

    void setPermissions(const Permissions &permissions) 
    {
        this->permissions = permissions;
    }

    //getters
    const std::string &getUsername() const
    {
        return username;
    }

    const std::string &getPassword() const
    {
        return password;
    }

    const Permissions getPermissions() const
    {
        return permissions;
    }

    static User lineToSelf(const std::string &line,const std::string &delimiter)
    {
        std::vector <std::string> UserParts = clsString::Split(line,delimiter);
        
        if (UserParts.size() < 7) ExcepAndErr::throwOutOfRangExcep("Users part is less than 7 !");

        User user = User();

        user.setFirstName(UserParts[0]);
        user.setLastName(UserParts[1]);
        user.setEmail(UserParts[2]);
        user.setPhoneNumber(UserParts[3]);
        user.setUsername(UserParts[4]);
        user.setPassword(UserParts[5]);
        user.setPermissions(Permissions(std::stoi(UserParts[6])));

        return user;
    }

    static std::string selfToLine(const User &usr,const std::string &delimiter)
    {
        return Person::personToLine((Person)usr,delimiter) + delimiter + usr.getUsername() + delimiter + usr.getPassword() + delimiter + std::to_string(Permissions::permissionsVecToInt(usr.getPermissions().getHasPermission()));
    }

    std::string toLine(const std::string &delimiter) const override
    {
        return Person::toLine(delimiter) + delimiter + username + delimiter + password + delimiter + std::to_string(Permissions::permissionsVecToInt(permissions.getHasPermission()));
    }

    std::string getIdentifier() const
    {
        return username;
    }

    static TypeId getTypeId()
    {return TypeId::User;} 

    void setIdentifier(const std::string &new_val)
    {
        username = new_val;
    }

};