#include "Console.h"

void Console::clear()
{
#ifdef WINDOWS
    system("cls");
#elif LINUX
    system("clear");
#endif // WINDOWS
}

void Console::pause(std::string text)
{
    std::cout << text << '\n';
    getchar();
}

void Console::printTable(std::map<std::string, std::string> text,
                         std::string separator) 
{
    size_t maxCommandLength = 0;

    for (auto& commandPair : text)
    {
        maxCommandLength = std::max(maxCommandLength, commandPair.first.length());
    }

    for (auto& commandPair : text)
    {
        std::cout << commandPair.first;

        for (size_t i = commandPair.first.length(); i < maxCommandLength; i++)
        {
            std::cout << ' ';
        }

        std::cout << separator << commandPair.second << '\n';
    }
}