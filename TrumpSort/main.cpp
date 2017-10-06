#include <iostream>
#include <ctime>
#include <algorithm>
#include <chrono>
#include "Trump.h"

using namespace std;
using namespace Trump;

template <class _T> void print_vector(vector<typename _T> & vec)
{
	bool first(true);
	for (vector<typename _T>::iterator it(vec.begin()), end(vec.end()); it != end; ++it)
	{
		if (first)
			first = false;
		else
			cout << ", ";
		cout << *it;
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	static const int vc = 100;
	static const int sc = 100000;
	vector<int> values, trumpified, minorities, sorted;
	chrono::time_point<chrono::system_clock> a, b, c, d;
	values.resize(vc);
	srand(static_cast<unsigned int>(time(nullptr)));
	cout << "Initializing values...\r\n";
	for (int i(0); i < vc; i++)
		values[i] = rand();
	cout << "Trump::trumpify() " << sc << " times...\r\n";
	a = chrono::system_clock::now();
	for (int i = 0; i < sc; i++)
		trumpify(values, &minorities);
	b = chrono::system_clock::now();
	cout << "Trump::sort() " << sc << " times...\r\n";
	c = chrono::system_clock::now();
	for (int i = 0; i < sc; i++)
		sort(values);
	d = chrono::system_clock::now();
	trumpified = trumpify(values, &minorities);
	sorted = sort(values);
	cout << "Trumpified with " << trumpified.size() << " elements and " << minorities.size() << " minorities left.\r\n";
	cout << "Original:\r\n";
	print_vector(values);
	cout << "Trumpified: (" << (b - a).count() << " ns)\r\n";
	print_vector(trumpified);
	cout << "Minorities:\r\n";
	print_vector(minorities);
	cout << "Sorted: (" << (d - c).count() << " ns)\r\n";
	print_vector(sorted);
	getchar();
	return 0;
}