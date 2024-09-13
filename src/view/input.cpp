#include <iostream>

#include <view/input.h>
#include <ansicodes/ansicodes.h>

std::string Input::get_text(std::string prompt, int min_len, std::string default_value)
{
    std::string in {};

    do {
        std::cout << prompt << ": ";

        std::getline(std::cin, in);

        if (min_len > 0 && in.length() < min_len) {
            std::cout << ANSICodes::RED << "Error: input must be at least " << min_len << " characters long" << ANSICodes::RESET << std::endl;
        }

    } while (min_len > 0 && in.length() < min_len);

    return in.length() > 0 ? in : default_value;
}

int Input::get_number(std::string prompt, int default_value)
{
    std::string in {};
    int number {};

    do {
        std::cout << prompt << ": ";

        std::getline(std::cin, in);

        try {
            number = in.length() > 0 ? std::stoi(in) : default_value;
        } catch (std::invalid_argument e) {
            std::cout << ANSICodes::RED << "Error: non-numeric input for certificate" << ANSICodes::RESET << std::endl;
            continue;
        } catch (std::out_of_range e) {
            std::cout << ANSICodes::RED << "Error: number too large" << ANSICodes::RESET << std::endl;
            continue;
        }
        break;
    } while (true);

    return number;
}
