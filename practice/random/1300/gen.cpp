#include <bits/stdc++.h>
using namespace std;

int main() {
	ofstream out("test");
	out << 1 << endl;
	out << 40 << endl;
	for (int r = 40; r >= 1; r--)
		out << r << " ";
	out << endl;
	for (int r = 80; r >= 41; r--)
		out << r << " ";
	return 0;
}