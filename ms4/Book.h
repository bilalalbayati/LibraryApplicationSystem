

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include"Publication.h"
namespace sdds {
	class Book : public Publication {
		char* m_authorname{};
	private:
		void set(const char* authorname);
	public:		
		Book& operator=(const Book& bk);
		Book();
		Book(const Book& bk);
		~Book();		
		void set(int member_id);
		char type()const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);
		operator bool()const;
	};
	std::ostream& operator<<(std::ostream& os, const Book& obj);
	std::istream& operator>>(std::istream& is, Book& obj);
}

#endif