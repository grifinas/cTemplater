#pragma once

#include <string>
#include <map>
#include <iostream>

#define MAX_VAR_SIZE 100

enum streamType{
    T_FILE,
    T_STRING
};

class Templater {
    public:
        Templater();
        Templater(std::string);
        ~Templater();
        std::string render();
        void set(std::string, std::string);
        void clearData();
        bool hasKey(std::string) const;
        void streamFromFile(char const *file_name);

    private:
        streamType type = T_STRING;
        std::iostream *stream = nullptr;
        std::map<std::string, std::string> datamap;

        std::string getVarFromStream();
};
