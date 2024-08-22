#include <iostream>
#include <chrono>
#include <ansicodes.h>
#include "model/zodiac.h"

using namespace std;

int main()
{
    Model::Zodiac zodiac;
    zodiac.set_start_date(std::chrono::system_clock::now());

    std::cout << ANSICodes::BLUE << "Welcome to the Book of Shadows" << ANSICodes::RESET << std::endl;
    return 0;
}
