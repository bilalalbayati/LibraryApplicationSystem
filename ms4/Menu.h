

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds {
    int const MAX_MENU_ITEMS = 20;
    class Menu;
    class MenuItem {
        char* m_menuItem{};
        MenuItem();
        MenuItem(const char* item);
        ~MenuItem();
        operator bool() const;
        void display();
        friend Menu;
    };
    class Menu {
        char* m_menuTitle{};
        MenuItem* m_items[MAX_MENU_ITEMS];
        int m_noofmenu = 0;
    public:     
        int run();
        char* operator[](int i) const;
        operator bool() const;
        int operator~();
        Menu();
        Menu(const char* title);
        ~Menu();
        void display();
        std::ostream& write(std::ostream& os = std::cout)const;
        Menu& operator<<(const char* menuitemConent);
        operator unsigned int() const;
    };
    std::ostream& operator<<(std::ostream& os, const Menu& m);
}
#endif