#include "Templater.h"
#include <sstream>
#include <fstream>


Templater::Templater()
{
    this->stream = new std::stringstream();
    this->type = T_STRING;
}

Templater::Templater(std::string s)
{
    this->stream = new std::stringstream();
    *this->stream << s;
    this->type = T_STRING;
}

Templater::~Templater()
{
    delete this->stream;
}

void Templater::streamFromFile(char const *file_name)
{
    this->type = T_FILE;
    std::fstream *fs = new std::fstream();
    fs->open(file_name, std::fstream::in);
    delete this->stream;
    this->stream = static_cast<std::iostream*>(fs);
}

std::string Templater::render()
{
    std::stringbuf normal_text;
    std::string var_data;

    while(!this->stream->eof()) {
        //Get raw text till var start
        this->stream->get(normal_text, '{');

        if (this->stream->good()) {
            var_data = this->getVarFromStream();
            if (var_data.length())
                normal_text.sputn(var_data.c_str(), var_data.length());
        } else {
            if (this->stream->bad()) throw "Bad stream";
            if (this->stream->fail()) throw "Fail stream";
        }
    }

    var_data = normal_text.str();

    return var_data;
}

std::string Templater::getVarFromStream()
{
    if (this->stream->fail()) throw "bad stream";
    char trash;
    char var_name[MAX_VAR_SIZE];
    std::string string_var;

    //Get {
    this->stream->get(trash);
    if (this->stream->fail()) throw "bad stream";

    //Get var name
    this->stream->get(var_name, MAX_VAR_SIZE, '}');
    if (this->stream->fail()) throw "bad stream";
    string_var = var_name;

    //Get }
    this->stream->get(trash);
    if (this->stream->fail()) throw "bad stream";

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
