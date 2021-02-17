#include <iostream>
#include <random>


using namespace std;

string generationKey()
{
	string ABC = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";

	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> distribution(0, ABC.length());

	string keyWord = "";

	for (int i = 0; i < 5; i++)
keyWord += ABC[distribution(generator)];

	return keyWord;
}

int main() 
{
	string random_word = generationKey();
	cout << random_word << endl;
	return 0;
}