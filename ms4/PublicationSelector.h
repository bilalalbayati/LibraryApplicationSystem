



#ifndef SDDS_PUBLICATIONSELECTOR_H
#define SDDS_PUBLICATIONSELECTOR_H
#include "Publication.h"
namespace sdds {
    class PublicationSelector {   
        const int allocationUnit{ 10 };
        char m_title[81]{};
        int m_currentPage{ 1 };
        int m_arraySize{};        
        const int m_pageSize{ };
        const Publication** m_pub{};
        int m_noOfPubs{};
        void display(int page)const;
        int getSelectedLibRef()const;
    public:       
        PublicationSelector& operator=(const PublicationSelector&) = delete;
        PublicationSelector& operator<<(const Publication* pub);
        PublicationSelector& operator<<(const Publication& pub);
        PublicationSelector(const char* title = "Select a publication: ", int pageSize = 15);
        ~PublicationSelector();
        PublicationSelector(const PublicationSelector&) = delete;
        operator bool()const;
        void reset();
        void sort();
        int run();
    };
}
#endif