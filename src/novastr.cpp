#include <string>
#include "novastr.h"

//
// Created by sadik on 4/20/2025.
//
std::string NovaTypeWriter::getCurrentText() const {
    return currentText;
}

void NovaTypeWriter::reset() {
    currentText = "";
    timer = timeBetweenCharacter;
}

void NovaTypeWriter::update() {
    if (paused) return;
    if (timer > 0.0f) {
        timer -= GetFrameTime();
        return;
    }
    timer = timeBetweenCharacter;

    if (index >= targetText.size()) return;

    currentText += targetText.at(index);
    index++;
}

bool NovaString::hasPrefix(std::string prefix) {
    return substr(0, prefix.length()) == prefix;
}

bool NovaString::hasSuffix(std::string suffix) {
    return substr(length() - suffix.length(), length()) == suffix;
}

std::vector<NovaString> NovaString::split(char delimiter) {
    // Create vector
    std::vector<NovaString> tokens;
    NovaString token;
    std::stringstream ss(*this);

    while (std::getline(ss, token, delimiter)){
        tokens.push_back(token);
    }

    return tokens;
}

NovaString NovaString::replace_(std::string _old, std::string _new) {
    size_t oldStartPos = find(_old);
    NovaString tempStr = *this;

    if (oldStartPos == std::string::npos){
        return {};
    }

    size_t oldEndPos = _old.length();
    tempStr.replace(oldStartPos, oldEndPos, _new);
    return tempStr;
}

std::string NovaCommandBuilder::build()
{
    std::string cmd = command + " ";

    for (std::string option : options) cmd += option + " ";
    for (std::string value : values) cmd += value;

    return cmd;
}
