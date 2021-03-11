#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>

class FileSystem
{
public:
    static std::string getUserFolder();

    static bool isDirectoryExist(const std::string path);

    static bool createDirectory(const std::string path);
};

#endif // FILESYSTEM_H