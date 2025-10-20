#pragma once

#include <iostream>

template<typename Derived> class Person
{
    
public:
    enum class TypeId{Client , User};

private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phoneNumber;

public:
    //constractor
    Person(const std::string &first_name,const std::string &last_name,const std::string &email,const std::string &phone_number) : firstName(first_name),lastName(last_name),email(email),phoneNumber(phone_number)
    {
    }

    virtual ~Person(){};

    //setters 
    void setFirstName(const std::string &first_name)
    {
        firstName = first_name;
    }

    void setLastName(const std::string &last_name)
    {
        lastName = last_name;
    }

    void setEmail(const std::string &email)
    {
        this->email = email;
    }

    void setPhoneNumber(const std::string &phone_number)
    {
        phoneNumber = phone_number;
    }

    //getters
    const std::string &getFirstName() const
    {
        return firstName;
    }

    const std::string &getLastName() const
    {
        return lastName;
    }

    const std::string &getEmail() const 
    {
        return email;
    }

    const std::string &getPhoneNumber() const
    {
        return phoneNumber;
    }

    //statics
    static std::string personToLine(const Person &p , const std::string &delimiter)
    {
        return p.getFirstName() + delimiter + p.getLastName() + delimiter + p.getEmail() + delimiter + p.getPhoneNumber();
    }

    //methods
    virtual std::string toLine(const std::string &delimiter) const
    {
        return personToLine(*this,delimiter);
    }

    static TypeId getTypeId()
    {
        return Derived::getTypeId();
    }
};