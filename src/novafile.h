#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class NovaFile {
    private:
    std::ofstream file;

    public:
    std::string path, extension;
    std::string contents;

    // Constructor
    NovaFile(std::string path, std::string extension):
        path(path), extension(extension), contents(""){
        file = std::ofstream(fullPath());
        // Terminate if file not open
        if (!file.is_open()){
            throw std::runtime_error("Could not open file: `" + fullPath() + "`.");
        }
    }

    // Get path with extension
    std::string fullPath();

    // Close file
    void close();

    // Add contents
    void operator<<(std::string text){
        file << text;
        contents += text;
    }



    // Read files
    static std::string fetchContents(std::string file);
};



class NovaFS {
    public:
    // Returns int: 0 = success, else = failure
    static int mkdir(std::string path);
    static int touch(std::string path);

    // Based on UNIX `rm`, `-f` is the force arg, `-r` is the recursive arg
    static int rm(std::string path, std::string dest, bool force = false, bool recursive = false);

    static int cp(std::string path, std::string dest, bool force = false, bool recursive = false);

    static int mv(std::string path, std::string dest, bool force = false, bool recursive = false);

    class Win32FS {
        public:
        static int rmdir(std::string paTh);
        static int copy(std::string path, std::string dest);
        static int move(std::string path, std::string dest);
        static int xcopy(std::string path, std::string dest);
    };
};