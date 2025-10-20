#pragma once

#include <limits>  

class Input
{
public:
    template <typename T> static T read(const std::string &request_message,const std::string &err_message)
    {
        T N;

        std::cout << request_message;
        std::cout << "\n\\\033[32mready\033[0m>" ;
        std::cin >> N;

        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\033[31m"+ err_message +"\033[0m" ;

            std::cout << request_message;
            std::cin >> N;
        }

        return N;
    }

    template <typename T> static bool isBtw(T number, T min, T max)
    {
        if (min > max) std::swap(min,max);

        return (number >= min && number <= max);
    }

    template <typename T> static T read(T min,T max,const std::string &request_message, const std::string &type_err_message,const std::string &out_of_range_message)
    {
        T N = read<T>(request_message , type_err_message);

        while (!isBtw<T>(N,min,max))
        {
            std::cout << "\033[31m"+ out_of_range_message +"\033[0" ;

            N = read<T>(request_message,type_err_message);
        }
        
        return N;
    }
};
