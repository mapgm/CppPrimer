#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1 = {1, 2, 3}, v2 = {1, 2}, v3 = {1, 2, 3};
	
	if (v1 == v2) cout << "v1 == v2" << endl;
	if (v1 == v3) cout << "v1 == v3" << endl;
	if (v2 == v3) cout << "v2 == v3" << endl;
	
	return 0;
}
