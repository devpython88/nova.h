#include "novafile.h"


std::string NovaFile::fullPath()
{
    if (extension.empty()) return path;
    return path + "." + extension;
}

void NovaFile::close()
{
    file.close();
}

std::string NovaFile::fetchContents(std::string file)
{
    // Open file
    std::ifstream f(file);

    // Handle error
    if (!f.is_open()){
        throw std::runtime_error("Couldn't fetch contents from file `" + file + "`.");
    }

    // Return contents
    std::string fetched;

    std::string line;
    while (std::getline(f, line)){
        fetched += line + "\n";
    }

    return fetched;
}

int NovaFS::mkdir(std::string path)
{
    std::string p2 = path;

    #if defined(_WIN32)
        // Use modern c++ features to batchify the path
        std::replace(p2.begin(), p2.end(), '/', '\\');
    #endif

    // Create dir
    return system(("mkdir " + p2).c_str());
}

int NovaFS::touch(std::string path)
{
    // Make file
    return system(("touch " + path).c_str());
}

int NovaFS::rm(std::string path, std::string dest, bool force, bool recursive)
{
    // Command
    std::string cmd = "rm ";

    // Options
    if (force) cmd += "-f ";
    if (recursive) cmd += "-r ";

    // Finalization
    cmd += path + " " + dest;

    // Return
    return system(cmd.c_str());
}

int NovaFS::cp(std::string path, std::string dest, bool force, bool recursive)
{
    // Command
    std::string cmd = "cp ";

    // Options
    if (force) cmd += "-f ";
    if (recursive) cmd += "-r ";

    // Finalization
    cmd += path + " " + dest;

    // Return
    return system(cmd.c_str());
}



int NovaFS::mv(std::string path, std::string dest, bool force, bool recursive)
{
    // COmmand
    std::string cmd = "mv ";
    
    // Options
    if (force) cmd += "-f ";
    if (recursive) cmd += "-r ";

    // Finalize
    cmd += path + " " + dest;

    // Return
    return system(cmd.c_str());
}




int NovaFS::Win32FS::rmdir(std::string paTh)
{
    // Remove dir recursively
    return system(("rmdir " + paTh).c_str());
}

int NovaFS::Win32FS::copy(std::string path, std::string dest)
{
    // Copy
    return system(("copy " + path + " " + dest).c_str());
}

int NovaFS::Win32FS::move(std::string path, std::string dest)
{
    // Move (Cut)
    return system(("move " + path + " " + dest).c_str());
}

int NovaFS::Win32FS::xcopy(std::string path, std::string dest)
{
    // Copy dir
    return system(("xcopy " + path + " " + dest + " " + "/E").c_str());
}

bool NovaFileWatcher::isDifferent()
{
    return !(NovaFile::fetchContents(file) == capturedContents);
}

void NovaFileWatcher::reload()
{
    capturedContents = NovaFile::fetchContents(file);
}
