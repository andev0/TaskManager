#ifndef SAVES_H
#define SAVES_H

#include <fstream>
#include <string>

#include "FileSystem.h"
#include "Task.h"

class Saves
{
public:
    static void save(Task& anyTask);

    static void load(Task& targetTask);

private:
    static std::string getSavingPath(bool fileName = true);

    static void saveTaskToFile(Task& task, std::ofstream& file);

    static void loadTaskFromFile(Task* parentTask, std::ifstream& file, bool isFirst = true);
};

#endif // SAVES_H