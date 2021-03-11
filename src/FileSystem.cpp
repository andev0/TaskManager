#include "FileSystem.h"

std::string FileSystem::getUserFolder()
{
#ifdef WINDOWS
    return getenv("APPDATA");
#elif LINUX
    return getenv("HOME") + "\\.local\\share";
#endif // WINDOWS
    return "";
}

bool FileSystem::isDirectoryExist(const std::string path)
{
    // system() returns 0 if command was successfully executed.
    // If no specified folder exists, then system() will returns number
    // that not equals 0 and "mkdir" command will create needed folder.

    return system(("cd \"" + path + "\"").c_str()) == 0;
}

bool FileSystem::createDirectory(const std::string path)
{
    // system() returns 0 if command was successfully executed.

    return system(("mkdir \"" + path + "\"").c_str()) == 0;
}
