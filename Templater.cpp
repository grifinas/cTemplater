#include "Templater.h"
#include <sstream>


Templater::Templater(const char* file_name)
{
    this->fs.open(file_name, std::fstream::in);
}

Templater::~Templater()
{
    this->fs.close();
}

std::string Templater::render()
{
    std::stringbuf normal_text;
    std::string var_data;

    while(!this->fs.eof()) {
        //Get raw text till var start
        this->fs.get(normal_text, '{');

        if (this->fs.good()) {
            var_data = this->getVarFromStream();
            if (var_data.length())
                normal_text.sputn(var_data.c_str(), var_data.length());
        }
    }

    return normal_text.str();
}

std::string Templater::getVarFromStream()
{
    if (this->fs.fail()) throw "bad stream";
    char trash;
    char var_name[MAX_VAR_SIZE];
    std::string string_var;

    //Get {
    this->fs.get(trash);
    if (this->fs.fail()) throw "bad stream";

    //Get var name
    this->fs.get(var_name, MAX_VAR_SIZE, '}');
    if (this->fs.fail()) throw "bad stream";
    string_var = var_name;

    //Get }
    this->fs.get(trash);
    if (this->fs.fail()) throw "bad stream";

    if (!this->hasKey(string_var)) {
        std::string tmp = "No key named: " + string_var;
        throw tmp;
    }

    return this->datamap.at(string_var);
}

void Templater::set(std::string key, std::string val)
{
    this->datamap[key] = val;
}

void Templater::clearData()
{
    this->datamap.clear();
}

bool Templater::hasKey(std::string key) const
{
    return this->datamap.find(key) == this->datamap.end() ? false : true;
}
