#include <iostream>

using namespace std;

int main()
{
	setlocale (LC_ALL, "Russian");

	float z1, z2, a;
	cout << "¬ведите а" << endl;
	cin >> a;
	z1 = (((a + 2) / (sqrt(2 * a))) - (a / (sqrt(2 * a) + 2)) + (2 / (a - sqrt(2 * a)))) * ((sqrt(a) - sqrt(2)) / (a + 2));
	cout << "z1 = " << z1 << endl;
	z2 = 1 / (sqrt(a + sqrt(2)));
	cout << "z2 = " << z2 << endl;

	return 0;
}