#include <iostream>
#include <string>

#include <vector>

class allNames
{
public:
    allNames(std::string);
    ~allNames();

    std::string clean_name(std::string);  //take out capitalization and blank spaces

    void invert_names();     // inverts full name to make each backbone a primary backbone at least once and then puts each name in the names vector

    void strip_names();     // strips sub compounds down to backbones

    void set_namesSize();

    unsigned int get_namesSize();

    std::string get_name(unsigned int);

    std::string get_inputName();

private:
    std::string inputName;

    std::vector <std::string> names;

    int namesSize;
};
