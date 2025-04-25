#include "novajson.h"

void NovaJSON::loadFile(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open()){
        throw std::runtime_error("Could not load json from file: " + path);
    }

    file >> _nlJsonData;
    file.close();
}

void NovaJSON::writeFile(const std::string &path, int indent)
{
    std::ofstream file(path);

    if (!file.is_open()){
        throw std::runtime_error("Could not open file: " + path);
    }

    file << prettify(indent);
    file.close();
}

std::string NovaJSON::prettify(int indent)
{
    return _nlJsonData.dump(indent);
}
