#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <iostream>

class Task
{

friend class Saves;

public:
    Task(std::string name, bool isCompletable = false,
         std::string description = "", Task* parentTask = nullptr,
         std::vector<Task> subTasks = std::vector<Task>());

    void setName(std::string name);
    std::string getName();

    void setDescription(std::string description);
    std::string getDescription();

    void setCompletable(bool isCompletable);
    bool getCompletable();

    void setCompleted(bool isCompleted);
    bool getCompleted();
    bool getSubTasksCompleted();

    void addSubTask(Task task);
    Task getSubTask(size_t index);
    std::vector<Task>& getSubTasks();

private:
    std::string _name;
    std::string _description;

    bool _isCompletable;
    bool _isCompleted;

    std::vector<Task> _subTasks;

    Task* _parentTask;

};

#endif // TASK_H