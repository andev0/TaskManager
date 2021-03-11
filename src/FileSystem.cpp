#include "FileSystem.h"

std::string FileSystem::getUserFolder()
{
#ifdef WINDOWS
    return getenv("APPDATA");
#elif LINUX
    return std::string(getenv("HOME")) + "/.local/share";
#endif // WINDOWS
    return "";
}

bool FileSystem::isDirectoryExist(const std::string path)
{
    // system() returns 0 if command was successfully executed.
    // If no specified folder exists, then system() will returns number
    // that not equals 0.

    #ifdef WINDOWS
    return system(("cd \"" + path + "\"").c_str()) == 0;
    #elif LINUX
    return system(("cd \"" + path + "\" > /dev/null").c_str()) == 0;
    #endif // WINDOWS
}

bool FileSystem::createDirectory(const std::string path)
{
    // system() returns 0 if command was successfully executed.

    #ifdef WINDOWS
    return system(("mkdir \"" + path + "\"").c_str()) == 0;
    #elif LINUX
    return system(("mkdir \"" + path + "\" > /dev/null").c_str()) == 0;
    #endif // WINDOWS
}
