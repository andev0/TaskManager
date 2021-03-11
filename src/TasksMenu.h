#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <regex>
#include <vector>
#include <map>
#include <iostream>
#include <functional>

#include "Task.h"
#include "Console.h"
#include "Saves.h"

class TasksMenu
{
public:
    static void print(Task& parentTask);

private:
    enum class Result 
    {
        Success,
        Back
    };

    static void printTasks(std::vector<Task>& tasks);
    static Result inputCommands(Task& parentTask, bool generalCommands = true);
    static void createSubTask(Task& parentTask);
    static void printHelp(Task& parentTask);
    static void taskAction(Task& parentTask, std::string command,
                           std::function<void(int)> action);
    
};

#endif // MAIN_MENU_H