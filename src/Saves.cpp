#include "Saves.h"

std::string Saves::getSavingPath(bool fileName)
{
    std::string path = FileSystem::getUserFolder() + "\\TaskManagerData";

    if (fileName)
    {
        path += "\\Tasks.save";
    }

    return path;
}

void Saves::save(Task& anyTask)
{
    // Saving function will recursively save task beginning from given as
    // argument so it's important to begin saving from main task (task without
    // parent task).

    if (anyTask._parentTask == nullptr)
    {
        if ( FileSystem::isDirectoryExist(getSavingPath(false)) )
        {
            FileSystem::createDirectory(getSavingPath(false));
        }

        std::ofstream file(getSavingPath());

        Saves::saveTaskToFile(anyTask, file);

        file.close();
    }
    else
    {
        save(*anyTask._parentTask);
    }
}

void Saves::saveTaskToFile(Task& task, std::ofstream& file)
{
    file << task._name << "\n";
    file << task._description << "\n";
    file << task._isCompletable << "\n";
    file << task._isCompleted << "\n";
    file << task._subTasks.size() << "\n";

    for (auto& subtask : task.getSubTasks())
    {
        saveTaskToFile(subtask, file);
    }
}

void Saves::load(Task& targetTask)
{
    std::ifstream file(getSavingPath());

    if (file.is_open())
    {
        loadTaskFromFile(&targetTask, file);
    }

    file.close();
}

void Saves::loadTaskFromFile(Task* parentTask, std::ifstream& file, 
                             bool isFirst)
{
    Task readedTask("");

    size_t subtasksCount;

    ///////////////////////////////////////////////////////////////////////

    std::getline(file, readedTask._name);

    std::getline(file, readedTask._description);

    std::string line;

    std::getline(file, line);
    readedTask._isCompletable = (line == "1");

    std::getline(file, line);
    readedTask._isCompleted = (line == "1");

    std::getline(file, line);
    subtasksCount = std::stoull(line); // std::stoull(std::string) converts
                                       // std::string to unsigned long long

    ///////////////////////////////////////////////////////////////////////

    Task* task;

    if (isFirst)
    {
        // First loaded task (main task) have not parent and already
        // initialized by name, description, etc. so function should only get
        // sub tasks' count and call function recursively for all sub tasks.

        task = parentTask;
    }
    else
    {
        parentTask->_subTasks.push_back(readedTask);
        task = &parentTask->_subTasks[parentTask->_subTasks.size() - 1];
    }

    for (size_t i = 0; i < subtasksCount; i++)
    {
        loadTaskFromFile(task, file, false);
    }
}
