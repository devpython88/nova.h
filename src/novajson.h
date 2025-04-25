#pragma
#include "json.hpp"
#include <fstream>
#include <stdexcept>
#include <type_traits>


class novajson_null_val_error : public std::exception {
    public:

    std::string info;
    novajson_null_val_error(std::string info): info(info){}

    const char* what() const noexcept override {
        return info.c_str();
    }
};

class novajson_type_mismatch_error : public std::exception {
    public:

    std::string info;
    novajson_type_mismatch_error(std::string info): info(info){}

    const char* what() const noexcept override {
        return info.c_str();
    }
};



class NovaJSON {
    public:
    nlohmann::json _nlJsonData;


    NovaJSON() = default;

    void loadFile(const std::string& path);
    void writeFile(const std::string& path, int indent = 4);
    std::string prettify(int indent);
    

    // Template functions
    template <typename T>
    void set(std::string name, T value){
        _nlJsonData[name] = value;
    }

    template <typename T>
    T get(std::string name){
        if (!_nlJsonData.contains(name)){
            throw novajson_null_val_error("The following item is not in the json: " + name);
        }

        auto value = _nlJsonData[name];

        if constexpr (!std::is_same<decltype(value), T>::value){
            throw novajson_type_mismatch_error("The entry and value were found but the value's type is not the same as the required type.");
        }

        return value;
    }
};