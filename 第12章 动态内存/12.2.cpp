#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>
#include <iostream>

using std::vector;
using std::string;

class StrBlob {
public:
	using size_type = vector<string>::size_type;
	
	StrBlob():data(std::make_shared<vector<string>>()) { }
	StrBlob(std::initializer_list<string> il):data(std::make_shared<vector<string>>(il)) { }
	
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	
	void push_back(const string &t) { data->push_back(t); }
	void pop_back(){
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}
	
	string& front() {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	
	string& back() {
		check(0, "back on empty StrBlob");
		return data->back();
	}
	
	const string& front() const {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	const string& back() const {
		check(0, "back on empty StrBlob");
		return data->back();
	}
	
private:
	void check(size_type i, const string &msg) const {
		if (i >= data->size()) throw std::out_of_range(msg);
	}
	
private:
	std::shared_ptr<vector<string>> data;
};

int main()
{
	const StrBlob csb{"hello", "world", "pezy"};
	StrBlob sb{"hello", "world", "Mooophy"};
	
	std::cout << csb.front() << " " << csb.back() << std::endl;
	std::cout << sb.front() << " " << sb.back() << std::endl;
	sb.back() = "pezy";
	std::cout << sb.front() << " " << sb.back() << std::endl;
	
	return 0;
}
