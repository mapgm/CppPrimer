#include "13.44.h"
#include <algorithm>
#include <iostream>

std::pair<char*, char*>
String::alloc_n_copy(const char *b, const char *e)
{
	auto str = alloc.allocate(e - b);
	return{ str, std::uninitialized_copy(b, e, str) };
}

void String::range_initializer(const char *first, const char *last)
{
	auto newstr = alloc_n_copy(first, last);
	elements = newstr.first;
	end = newstr.second;
}

String::String(const char *s)
{
	char *sl = const_cast<char*>(s);
	while (*sl)
		++sl;
	range_initializer(s, ++sl);
}

String::String(const String& rhs)
{
	range_initializer(rhs.elements, rhs.end);
	std::cout << "copy constructor" << std::endl;
}

void String::free()
{
	if (elements) {
		std::for_each(elements, end, [this](char &c){ alloc.destroy(&c); });
		alloc.deallocate(elements, end - elements);
	}
}

String::~String()
{
	free();
}

String& String::operator = (const String &rhs)
{
	auto newstr = alloc_n_copy(rhs.elements, rhs.end);
	free();
	elements = newstr.first;
	end = newstr.second;
	std::cout << "copy-assignment" << std::endl;
	return *this;
}

void foo(String x)
{
	std::cout << x.c_str() << std::endl;
}

void bar(const String& x)
{
	std::cout << x.c_str() << std::endl;
}

String baz()
{
	String ret("world");
	return ret;
}

int main()
{
	char text[] = "world";
	
	String s0;
	String s1("hello");
	String s2(s0);
	String s3 = s1;
	String s4(text);
	s2 = s1;
	
	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	String s5 = baz();
	
	std::vector<String> svec;
	svec.reserve(8);
	svec.push_back(s0);
	svec.push_back(s1);
	svec.push_back(s2);
	svec.push_back(s3);
	svec.push_back(s4);
	svec.push_back(s5);
	svec.push_back(baz());
	svec.push_back("good job");
	
	for (const auto &s : svec) {
		std::cout << s.c_str() << std::endl;
	}
	
	return 0;
}
