#pragma once

#include <iostream>

template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x <= 0)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}