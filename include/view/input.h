#ifndef INPUT_H
#define INPUT_H

#include <string>

class Input
{
public:
    static std::string get_text(std::string prompt, int max_len = 0, std::string default_value = "");
    static int get_number(std::string prompt, int default_value = 0);
};

#endif // INPUT_H
