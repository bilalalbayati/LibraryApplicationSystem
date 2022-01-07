

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

namespace sdds {
	class Streamable {
	public:		
		virtual bool conIO(std::ios& io)const = 0;
		virtual std::ostream& write(std::ostream& os)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual operator bool()const = 0;
		virtual ~Streamable() {};
	};
	std::ostream& operator<<(std::ostream& os, const Streamable& obj);
	std::istream& operator>>(std::istream& is, Streamable& obj);
}

#endif