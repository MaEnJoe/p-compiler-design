#include <memory>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class A
{
public:
	A()
	{
		for(int i = 0 ; i != 5 ; i++)
		{
			vec.push_back(i);
		}
	}
	void print()
	{
		for(auto e : vec)
		{
			printf("%d\n",e);
		}
	}
	vector<int> get(){return vec;}
	vector<int> vec;
};


int main()
{
	A a;
	vector<int> vec = a.get();
	a.print();

	return 0;
}
