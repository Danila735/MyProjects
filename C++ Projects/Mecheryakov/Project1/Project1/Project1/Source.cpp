#include <iostream>
#include <iterator>
#include <set>
#include <fstream>
#include <vector>

using namespace std;

struct letter_only : ctype <char>
{
	letter_only() : ctype <char>(get_table()) {};

	static ctype::ctype_base::mask const* get_table()
	{
		static vector <ctype_base::mask>
			rc(ctype<char>::table_size, ctype_base::space);
			fill(&rc['A'], &rc['z' + 1], ctype_base::alpha);
			return &rc[0];
	}
};

int main()
{
	ifstream inFile ("D:/важные/генератор.txt");
	inFile.imbue(locale(locale(), new letter_only));
	ostream_iterator <string> out_it(cout, "\n");
	istream_iterator <string> input_Iter(inFile);
	istream_iterator <string> eof;

	set <string> store (input_Iter, eof);

	copy(begin(store), end(store), out_it);
	//for (const auto &item : store)
	//{
	//	cout << item << "\n";
	//}
	cout << "-----" << endl;
	cout << store.size() << endl;
	return 0;
}