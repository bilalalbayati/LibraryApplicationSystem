
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <cstring>
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
namespace sdds {
    class LibApp {
        char m_filename[256];
        Publication* PPA[SDDS_LIBRARY_CAPACITY]{};
        int NOLP;
        int LLRN;
        bool m_changed = false;
        bool confirm(const char* message);
        void load();
        void save();
        int search(int option, char type);
        Menu m_publicationMenu{ "Choose the type of publication:" };
        Menu m_mainMenu{ "Seneca Library Application" };
        Menu m_exitMenu{ "Changes have been made to the data, what would you like to do?" };      
        void removePublication();
        void checkOutPub();
        void returnPub();
        void newPublication();
        Publication* getPub(int libRef);
    public:
        LibApp();
        ~LibApp();
        LibApp(const char filename[256]);
        void run();
    };
}
#endif 