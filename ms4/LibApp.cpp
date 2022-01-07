

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include "PublicationSelector.h"

namespace sdds {  

    void prnPub(Publication* p[], int size, int ref) {
        int i;
        for (i = 0; i < size; i++) {
            if (ref == p[i]->getRef()) {
                std::cout << *p[i] << std::endl;
                i = size;
            }
        }
    }

    LibApp::~LibApp()
    {

        for (int i = 0; i < NOLP; i++) {
            delete PPA[i];
        }
    }

    void LibApp::load() {
        std::cout << "Loading Data\n";
        std::ifstream infile(m_filename);
        char type{};
        for (int i = 0; infile; i++) {
            infile >> type;
            infile.ignore();
            if (infile) {

                if (type == 'P')
                    PPA[i] = new Publication;
                else if (type == 'B')
                    PPA[i] = new Book;
                else std::cout << "no data\n";

                if (PPA[i] && i < SDDS_LIBRARY_CAPACITY) {

                    infile >> *PPA[i];

                    LLRN = PPA[i]->getRef();

                    NOLP++;
                }

            }
        }

    } 
    void LibApp::save() {
        std::cout << "Saving Data\n";
        std::ofstream outfile(m_filename);
        for (int i = 0; i < NOLP; i++) {
            if (PPA[i]->getRef() != 0) {
                outfile << *PPA[i] << std::endl;  

            }
        }
    }  
    bool LibApp::confirm(const char* message)
    {
        Menu conf(message);
        conf << "Yes";
        int t_return = conf.run();

        if (t_return) return true;

        return false;

    }

    LibApp::LibApp(const char filename[256])
    {


        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

        strcpy(m_filename, filename);


        m_publicationMenu << "Book" << "Publication";

        NOLP = 0;
        load();
    }    

    int LibApp::search(int option, char type) {     
        PublicationSelector ps("Select one of the following found matches:", 15);
        std::cout << "Publication Title: ";
        char title[256];
        std::cin.getline(title, 256);
        if (option == 1)
        {
            for (int i = 0; i < NOLP; i++) {               
                if (strstr(*PPA[i], title) && PPA[i]->getRef() != 0 && type == PPA[i]->type())
                    ps << PPA[i]; 
            }
        }
        else if (option == 2)
        {
            for (int i = 0; i < NOLP; i++) {
                if (strstr(*PPA[i], title) && !PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type())
                    ps << PPA[i]; 
            }
        }
        else if (option == 3)
        {
            for (int i = 0; i < NOLP; i++) {
                if (strstr(*PPA[i], title) && PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type())
                    ps << PPA[i];
            }
        }


        int ref = 0;

        if (ps) {
            ps.sort(); 
            ref = ps.run(); 
            if (ref) {
                prnPub(PPA, NOLP, ref);
            }
            else {
                std::cout << "Aborted!\n";
            }
        }
        else {
            std::cout << "No matches to found!" << std::endl;
        }
        return ref;
    }   

    
    void LibApp::newPublication()
    {
        if (NOLP >= SDDS_LIBRARY_CAPACITY)
        {
            std::cout << "Library is at its maximum capacity!\n";
            return;
        }
        std::cout << "Adding new publication to the library\n";
        int i = m_publicationMenu.run();
        Publication* p = nullptr;
        if (i == 0)
        {
            std::cout << "Aborted!\n";
            return;
        }
        else if (i == 1)
        {
            p = new Book;
            std::cin >> *p;
        }
        else if (i == 2)
        {
            p = new Publication;
            std::cin >> *p;
        }

        if (std::cin.fail())
        {
            std::cout << "\nAborted!\n";
            exit(0);
        }


        if (confirm("Add this publication to the library?"))
        {
            m_changed = true;
            LLRN++;
            p->setRef(LLRN);
            PPA[NOLP] = p;



            NOLP++;

            std::cout << "Publication added\n";
        }

        if (!*p)
        {
            std::cout << "Failed to add publication!\n";
            delete p;
        }

    }


    Publication* LibApp::getPub(int libRef)
    {
        for (int i = 0; i < NOLP; i++)
        {
            if (libRef == PPA[i]->getRef()) return PPA[i];
        }

        return nullptr;

    }
    void LibApp::run()
    {
        while (1)
        {
            int option = m_mainMenu.run();

            if (option == 1)
            {
                newPublication();
            }
            else if (option == 2)
            {
                removePublication();
            }
            else if (option == 3)
            {
                checkOutPub();
            }
            else if (option == 4)
            {
                returnPub();
            }
            else if (option == 0)
            {
                if (m_changed)
                {

                    int opn = m_exitMenu.run();

                    if (opn == 1)
                    {
                        save();
                        break;
                    }
                    else if (opn == 2)
                    {
                        ;
                    }
                    else if (opn == 0)
                    {
                        if (confirm("This will discard all the changes are you sure?"))
                            break;
                    }
                }
                else break;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "-------------------------------------------\n";
        std::cout << "Thanks for using Seneca Library Application\n";
    }

    void LibApp::returnPub()
    {
        std::cout << "Return publication to the library\n";
        int i = m_publicationMenu.run();


        char type;
        if (i == 1) type = 'B';
        else type = 'P';
        int ref = search(3, type);
        if (ref != 0 && confirm("Returning publication?"))
        {
            Date date = getPub(ref)->checkoutDate();
            Date today;
            int days = today - date;
            days -= 15;
            if (days > 0)
            {
                std::cout << std::fixed;
                std::cout << std::setprecision(2);
                std::cout << "Please pay $" << float(days) * (0.5) << " penalty for being " << days << " days late!\n";
            }
            getPub(ref)->set(0);
            std::cout << "Publication returned\n";
            m_changed = true;
        }
    }

    void LibApp::removePublication()
    {
        std::cout << "Removing publication from the library\n";
        int i = m_publicationMenu.run();
        char type;
        if (i == 1) type = 'B';
        else
        {
            type = 'P';
        }
        int ref = search(1, type);
        if (ref != 0 && confirm("Remove this publication from the library?"))
        {
            m_changed = true;
            getPub(ref)->setRef(0);
            std::cout << "Publication removed\n";
        }
    }

    void LibApp::checkOutPub()
    {
        std::cout << "Checkout publication from the library\n";
        int i = m_publicationMenu.run();
        char type;
        if (i == 1) type = 'B';
        else type = 'P';
        int ref = search(2, type);
        if (ref != 0 && confirm("Check out publication?"))
        {
            m_changed = true;
            int mn;
            std::cout << "Enter Membership Number: ";
            while (1)
            {
                std::cin >> mn;
                if (mn > 9999 && mn <= 99999) break;
                std::cout << "Invalid membership number, try again: ";            }
            getPub(ref)->set(mn);
            std::cout << "Publication checked out\n";
        }
    }
    LibApp::LibApp()
    {
        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        load();
    }
    
}