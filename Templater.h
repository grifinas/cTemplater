#pragma once

#include <string>
#include <map>
#include <fstream>

#define MAX_VAR_SIZE 100

class Templater {
    public:
        Templater(char const *file_name);
        ~Templater();
        std::string render();
        void set(std::string, std::string);
        void clearData();
        bool hasKey(std::string) const;

    private:
        std::fstream fs;
        std::map<std::string, std::string> datamap;

        std::string getVarFromStream();
};
