#include <iostream>
#include <string>
#include "Templater.h"

#include <fstream>

int main()
{
    Templater *t = new Templater;
    std::string s;
    s = t->render();
    std::cout << s << std::endl;
    delete t;

    t = new Templater("naujas test");
    s = t->render();
    std::cout << s << std::endl;

    t->streamFromFile("test.txt");

    s = t->render();
    std::cout << s << std::endl;
    delete t;


    t = new Templater("{type} {faction} {min_lvl}-{max_lvl}");
    t->set("type", "vienas")
        ->set("faction", "du")
        ->set("min_lvl", "trys")
        ->set("max_lvl", "keturi");

    s = t->render();
    std::cout << s << std::endl;
    delete t;


    return 0;
}
