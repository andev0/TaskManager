#include "Task.h"

Task::Task(std::string name, bool isCompletable, std::string description, 
           Task* parentTask, std::vector<Task> subTasks)
{
    _name = name;
    _description = description;
    _isCompletable = isCompletable;
    _isCompleted = false;
    _subTasks = subTasks;
    _parentTask = parentTask;
}

void Task::setName(std::string name)
{
    _name = name;
}
std::string Task::getName()
{
    return _name;
}

void Task::setDescription(std::string description)
{
    _description = description;
}
std::string Task::getDescription()
{
    return _description;
}

void Task::setCompletable(bool isCompletable)
{
    _isCompletable = isCompletable;
}
bool Task::getCompletable()
{
    return _isCompletable;
}

void Task::setCompleted(bool isCompleted)
{
    _isCompleted = isCompleted;

    if (isCompleted)
    {
        for (auto& subTask : _subTasks)
        {
            subTask.setCompleted(true);
        }
    }
    else
    {
        if (_subTasks.size() > 0 && getSubTasksCompleted())
        {
            _subTasks[_subTasks.size() - 1].setCompleted(false);
        }
    }
}
bool Task::getCompleted()
{
    return _subTasks.size() > 0 ?
        getSubTasksCompleted() : _isCompleted;
}
bool Task::getSubTasksCompleted()
{
    bool isCompleted = true;
    // If there are no subtasks, let's assume that they are completed.

    for (auto& subTask : _subTasks)
    {
        if (!subTask.getCompleted())
        {
            isCompleted = false;
            break;
        }
    }

    return isCompleted;
}

void Task::addSubTask(Task task)
{
    _subTasks.push_back(task);
}
Task Task::getSubTask(size_t index)
{
    return _subTasks.at(index);
}
std::vector<Task>& Task::getSubTasks()
{
    return _subTasks;
}