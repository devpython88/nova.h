#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

class NovaFile {
    private:
    std::ofstream file;

    public:
    std::string path, extension;
    std::string contents;

    // Constructor
    NovaFile(std::string path, std::string extension):
        path(path), extension(extension), contents(""), file(fullPath()){
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