#include <string>
#include <iostream>
#include<fstream>
#include <vector>
#include <map>

using namespace std;

void read(vector<string>& word_v) {
	ifstream dict;
	dict.open("dictionary.txt");

	string buffer;
	while (!dict.eof()) {
		getline(dict, buffer);
		word_v.push_back(buffer);
	}
	dict.close();
}

bool isexist(vector<string> v, string s) {
	if (v.size == 0)
		return false;

	for (int i = 0; i < v.size(); i++) {
		if (s == v[i])
			return true;
	}
	return false;
}

struct suffix
{
	string suffix_str;
	int suffix_num;
};

void group(int n, vector<suffix> struct_v, vector<string>& suffix_v, vector<string>& word_v) {

	for (int i = 0; i < word_v.size(); i++) {
		if (word_v[i].length() < n)
			continue;
		
		string suffix_str = word_v[i].substr(word_v[i].length() - n, word_v[i].length());

		if (!isexist(suffix_v, suffix_str))//²»´æÔÚ
		{
			suffix_v.push_back(suffix_str);
			suffix tmp = { suffix_str ,1 };
			struct_v.push_back(tmp);
		}
		else
		{
			for (int i = 0; i < struct_v.size(); i++) {
				if (struct_v[i].suffix_str == suffix_str)
					struct_v[i].suffix_num += 1;
			}
		}
	}
}



int main()
{
	vector<string> word_v;

	read(word_v);

	cout << "Please input the number of letters of suffix" << endl;
	int suffix_n;
	cin >> suffix_n;

	vector<string> suffix_v;
	vector<suffix> struct_v;

	group(suffix_n, struct_v, suffix_v, word_v);
	
	for (int i = 0; i < suffix_v.size(); i++) {

	}



	system("PAUSE");
}