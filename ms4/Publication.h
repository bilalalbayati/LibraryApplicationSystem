



#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include"Date.h"
#include"Lib.h"
#include"Streamable.h"

namespace sdds {
	class Publication : Streamable {		
		int m_membership = 0;
		int m_libRef = -1;
		char* m_title{};
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		Date m_date;

		void extractChar(std::istream& istr, char ch)const;
		void set(const char* title, const char* shelfId, int membership, int libRef, Date date);
	public:		
		void resetDate();
		virtual char type()const;
		bool onLoan()const;
		Publication();
		virtual void set(int member_id);
		void setRef(int value);
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
		bool conIO(std::ios& io)const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);
		operator bool() const;
		Publication(const Publication& cnt);
		Publication& operator=(const Publication& cnt);
		~Publication();
	};
	std::ostream& operator<<(std::ostream& os, const Publication& obj);
	std::istream& operator>>(std::istream& is, Publication& obj);
}

#endif