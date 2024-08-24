#include <memory>
#include "../include/menu/menu.h"
#include "../include/menu/option.h"
#include "../include/controllers/colourcontroller.h"

std::unique_ptr<Menu> make_main_menu();

int main()
{
    std::unique_ptr<Menu> main_menu = make_main_menu();
    char selection {};

    do {
        main_menu->render();
        selection = main_menu->get_selection();
        if (selection != 'Q') {
            main_menu->invoke(selection);
        }
    } while (selection != 'Q');

    return 0;
}

std::unique_ptr<Menu> make_main_menu()
{
    std::unique_ptr<Menu> main_menu = std::make_unique<Menu>("Main Menu", "Enter your choice");
    main_menu->add_option(Option {'R', "Manage Runestones", nullptr});
    main_menu->add_option(Option {'T', "Manage Tarot Cards", nullptr});
    main_menu->add_option(Option {'C', "Manage Colours", handle_colour_menu});
    main_menu->add_option(Option {'G', "Manage Gods", nullptr});
    main_menu->add_option(Option {'H', "Manage Herbs", nullptr});
    main_menu->add_option(Option {'P', "Manage Planets", nullptr});
    main_menu->add_option(Option {'L', "Manage Planets", nullptr});
    main_menu->add_option(Option {'E', "Manage Trees", nullptr});
    main_menu->add_option(Option {'Z', "Manage Zodiacs", nullptr});
    main_menu->add_option(Option {'Q', "Quit", nullptr});

    return main_menu;
}