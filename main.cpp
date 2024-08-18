#include <iostream>
#include <chrono>
#include "model/zodiac.h"

using namespace std;

int main()
{
    Zodiac zodiac;
    zodiac.set_start_date(std::chrono::system_clock::now());

    std::cout << zodiac.get_start_date() << std::endl;
    return 0;
}
