#ifndef CONSOLE_H
#define CONSOLE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <map>

class Console
{
public:
    static void clear();
    static void pause(std::string text = "Press Enter to continue.");

    static void printTable(std::map<std::string, std::string> text,
                           std::string separator = " ");
};

#endif //CONSOLE_H