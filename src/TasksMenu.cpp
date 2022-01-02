#include "TasksMenu.h"

void TasksMenu::printTasks(std::vector<Task>& tasks)
{
    size_t tasksCount = tasks.size();

    if (tasksCount == 0)
    {
        std::cout << "No tasks here. Type \"create\" to add one.\n";
    }
    else
    {
        for (size_t i = 0; i < tasksCount; i++)
        {
            std::cout << i + 1 << ". ";

            if (tasks.at(i).getCompletable())
            {
                if (tasks.at(i).getCompleted())
                {
                    std::cout << "|#| ";
                }
                else
                {
                    std::cout << "| | ";
                }
            }

            std::cout << tasks.at(i).getName();

            if (tasks.at(i).getDescription() == "")
            {
                std::cout << ";\n";
            }
            else
            {
                std::cout << " (" << tasks.at(i).getDescription() << ");\n";
            }
        }
    }
}

TasksMenu::Result TasksMenu::inputCommands(Task& parentTask, bool generalCommands) 
{
    std::vector<Task>& subTasks = parentTask.getSubTasks();

    std::cout << "> ";
    std::string command;
    std::getline(std::cin, command); // For reading line including spaces.

    if (command == "back" || command == "b")
    {
        return Result::Back;
    }
    else if (command == "exit" || command == "e")
    {
        Console::clear();
        std::exit(0);
    }
    else if (!generalCommands)
    {
        if (command == "help" || command == "h")
        {
            printHelp(parentTask);
        }
        else if (command == "new" || command == "n")
        {
            createSubTask(parentTask);
        }
        else if (std::regex_match(command, std::regex("^complete \\d+$")) 
                 || std::regex_match(command, std::regex("^c \\d+$")))
            // "complete [number]", "c [number]"
        {
            taskAction(parentTask, command, 
                [&parentTask, &subTasks](int selectedTask) { 
                    subTasks.at(selectedTask - 1).setCompleted(true);
                    Saves::save(parentTask);
                }
            );
        }
        else if (std::regex_match(command, std::regex("^uncomplete \\d+$"))
                 || std::regex_match(command, std::regex("^u \\d+$")))
            // "uncomplete [number]", "u [number]"
        {
            taskAction(parentTask, command, 
                [&parentTask, &subTasks](int selectedTask) { 
                    subTasks.at(selectedTask - 1).setCompleted(false);
                    Saves::save(parentTask);
                }
            );
        }
        else if (std::regex_match(command, std::regex("^select \\d+$"))
                 || std::regex_match(command, std::regex("^sel \\d+$"))
                 || std::regex_match(command, std::regex("^s \\d+$")))
            // "select [number]", "sel [number]", "s [number]"
        {
            taskAction(parentTask, command, 
                [&subTasks](int selectedTask) { 
                    print(subTasks.at(selectedTask - 1));
                }
            );
        }
        else if (std::regex_match(command, std::regex("^delete \\d+$"))
                 || std::regex_match(command, std::regex("^del \\d+$"))
                 || std::regex_match(command, std::regex("^d \\d+$")))
            // "delete [number]", "del [number]", "d [number]"
        {
            taskAction(parentTask, command, 
                [&parentTask, &subTasks](int selectedTask) { 
                    subTasks.erase(subTasks.begin() + selectedTask - 1);
                    Saves::save(parentTask);
                }
            );
        }
    }

    return Result::Success;
}

void TasksMenu::print(Task& parentTask)
{
    while (true)
    {
        Console::clear();

        std::cout << parentTask.getName() << "\n\n";

        printTasks(parentTask.getSubTasks());

        std::cout << "\nEnter \"help\" or \"h\" to get list of available commands.\n";

        if (inputCommands(parentTask, false) == Result::Back)
        {
            break;
        }
    }
}

void TasksMenu::printHelp(Task& parentTask)
{
    while (true)
    {
        Console::clear();

        std::cout << "Help\n\n";

        std::map<std::string, std::string> commandsDescriptions = {
            {"h, help", "Opens this menu."},
            {"b, back", "Turns back to previous menu."},
            {"e, exit", "Exit app."},
            {"s, sel, select [number]", "Selects task by the index."},
            {"c, complete [number]", "Complete task and all its subtasks by the index."},
            {"u, uncomplete [number]", "Uncomplete task by the index."},
            {"n, new", "Creates a new task"},
            {"d, del, delete [number]", "Deletes a task by the index."}
        };

        Console::printTable(commandsDescriptions, " - ");

        if (inputCommands(parentTask, false) == Result::Back)
        {
            break;
        }
    }
}

void TasksMenu::createSubTask(Task& parentTask)
{
    while (true)
    {
        Console::clear();

        std::string name;
        std::string description;
        std::string isCompletableString; // "y" or "n"
        bool isCompletable;

        std::cout << "Enter task's name (\"cancel\" to cancel task creation).\n";
        std::cout << "> ";
        
        std::getline(std::cin, name);

        if (name == "cancel")
        {
            break;
        }
        else if (name == "")
        {
            Console::clear();

            std::cout << "Please, enter the name\n";

            Console::pause();
            continue;
        }

        std::cout << "Enter task's description (press Enter if no description, \"cancel\" to cancel task creation).\n> ";
        std::getline(std::cin, description);
        
        if (description == "cancel") break;

        std::cout << "do you want the task to be completable? (y/n/cancel)\n> ";
        std::getline(std::cin, isCompletableString);
        
        if (isCompletableString == "cancel") break;

        if (isCompletableString == "y")
        {
            isCompletable = true;
        }
        else if (isCompletableString == "n")
        {
            isCompletable = false;
        }
        else
        {
            Console::clear();

            std::cout << "Wrong answer format\n";

            Console::pause();
            continue;
        }

        parentTask.getSubTasks().push_back( Task (name, isCompletable, 
                                                  description, &parentTask) );
        Saves::save(parentTask);
        break;
    }
}

void TasksMenu::taskAction(Task& parentTask, std::string command,
                           std::function<void(int)> action)
{
    std::vector<Task>& subTasks = parentTask.getSubTasks();

    std::smatch mathes;
    std::regex_search(command, mathes, std::regex("(\\d+)")); // Getting number

    size_t selectedTask = 0;
    sscanf(mathes[0].str().c_str(), "%zu", &selectedTask); // String to size_t

    if (selectedTask <= subTasks.size())
    {
        action(selectedTask);
    }
    else
    {
        Console::clear();

        std::cout << "There is no " << selectedTask << "-th task here.\n";

        Console::pause();
    }
}
