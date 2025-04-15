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
