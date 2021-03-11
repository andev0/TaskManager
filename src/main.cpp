#include <iostream>
#include <string>

#include "Console.h"
#include "TasksMenu.h"

using namespace std;

int main()
{
    Task mainTask("Task Manager");

    Saves::load(mainTask);

    TasksMenu::print(mainTask);

    Console::clear();
    Console::pause("Press Enter to exit.");

    return 0;
}