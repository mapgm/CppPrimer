#ifndef DATE_H
#define DATE_H

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#include <iostream>
#include <vector>

class Date
{
	friend  bool operator == (const Date& lhs, const Date& rhs);
	friend  bool operator < (const Date &lhs, const Date &rhs);
	friend  bool check(const Date &d);
	friend  std::ostream& operator << (std::ostream& os, const Date& d);
public:
	typedef std::size_t Size;
	
	// default constructor
	Date() = default;
	// constructor taking Size as days
	explicit Date(Size days);
	// constructor taking three Size
	Date(Size d, Size m, Size y) : day(d), month(m), year(y) {}
	// constructor taking iostream
	Date(std::istream &is, std::ostream &os);
	
	// copy constructor
	Date(const Date& d);
	// move constructor
	Date(Date&& d) NOEXCEPT;
	
	// copy operator=
	Date& operator= (const Date& d);
	// move operator=
	Date& operator= (Date&& rhs) NOEXCEPT;
	
	// destructor  --  in this case, user-defined destructor is not nessary.
	~Date() { std::cout << "destroying\n"; }
	
	// members
	Size toDays() const;  //not implemented yet.
	Date& operator +=(Size offset);
	Date& operator -=(Size offset);
	
	
private:
	Size    day = 1;
	Size    month = 1;
	Size    year = 0;
};

static const Date::Size YtoD_400 = 146097;    //365*400 + 400/4 -3 == 146097
static const Date::Size YtoD_100 = 36524;    //365*100 + 100/4 -1 ==  36524
static const Date::Size YtoD_4 = 1461;    //365*4 + 1          ==   1461
static const Date::Size YtoD_1 = 365;    //365

// normal year
static const std::vector<Date::Size> monthsVec_n =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// leap year
static const std::vector<Date::Size> monthsVec_l =
{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// non-member operators:  <<  >>  -   ==  !=  <   <=  >   >=
//
std::ostream&
operator <<(std::ostream& os, const Date& d);
std::istream&
operator >>(std::istream& is, Date& d);
int
operator - (const Date& lhs, const Date& rhs);
bool
operator ==(const Date& lhs, const Date& rhs);
bool
operator !=(const Date& lhs, const Date& rhs);
bool
operator < (const Date& lhs, const Date& rhs);
bool
operator <=(const Date& lhs, const Date& rhs);
bool
operator  >(const Date& lhs, const Date& rhs);
bool
operator >=(const Date& lhs, const Date& rhs);
Date
operator - (const Date& lhs, Date::Size  rhs);
Date
operator  +(const Date& lhs, Date::Size  rhs);



//  utillities:
bool check(const Date &d);
inline bool
isLeapYear(Date::Size y);




// check if the date object passed in is valid
inline bool
check(const Date &d)
{
	if (d.month == 0 || d.month >12)
		return false;
	else
	{
		//    month == 1 3 5 7 8 10 12
		if (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 ||
			d.month == 8 || d.month == 10 || d.month == 12)
		{
			if (d.day == 0 || d.day > 31) return false;
			else
				return true;
		}
		else
		{
			//    month == 4 6 9 11
			if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11)
			{
				if (d.day == 0 || d.day > 30) return false;
				else
					return true;
			}
			else
			{
				//    month == 2
				if (isLeapYear(d.year))
				{
					if (d.day == 0 || d.day >29)  return false;
					else
						return true;
				}
				else
				{
					if (d.day == 0 || d.day >28)  return false;
					else
						return true;
				}
			}
		}
	}
}

inline bool
isLeapYear(Date::Size y)
{
	if (!(y % 400))
	{
		return true;
	}
	else
	{
		if (!(y % 100))
		{
			return false;
		}
		else
			return !(y % 4);
	}
}
#endif // DATE_H
