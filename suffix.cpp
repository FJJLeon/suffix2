#include <string>
#include <iostream>
#include<fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void read(vector<string>& word_v) {//�����ļ����ݵ� word_v ��vector
	ifstream dict;
	dict.open("dictionary.txt");

	string buffer;
	while (!dict.eof()) {
		getline(dict, buffer);
		word_v.push_back(buffer);
	}
	dict.close();
}

bool isexist(vector<string> v, string s) {//�ж�һ��vector<string>���Ƿ����ĳ��string
	if (v.size() == 0)
		return false;

	for (int i = 0; i < v.size(); i++) {
		if (s == v[i])
			return true;
	}
	return false;
}

struct suffix   //ÿ�ֲ�ͬ�ĺ�׺�Ľṹ
{
	string str;
	int num;
	vector<string> member;
};

void group(int n, vector<suffix>& struct_v, vector<string>& str_v, vector<string>& word_v) {

	for (int i = 0; i < word_v.size(); i++) {
		if (word_v[i].length() < n)
			continue;
		
		string str = word_v[i].substr(word_v[i].length() - n, word_v[i].length());//��ȡ n -letter suffix

		if (!isexist(str_v, str))//������
		{
			str_v.push_back(str);
			//suffix tmp = { str ,1, vector<string>{word_v[i]} };
			struct_v.push_back(suffix{ str ,1, vector<string>{word_v[i]} });  //�����д�������������
		}
		else{
			for (int j = 0; j < struct_v.size(); j++) {
				if (struct_v[j].str == str){
					struct_v[j].num += 1;
					struct_v[j].member.push_back(word_v[i]);
				}				
			}
		}
	}
}

bool myless(suffix&s1, suffix&s2) {
	return s1.num < s2.num;
}

int main()
{
	vector<string> word_v;
	read(word_v);

	cout << "Please input the number of letters of suffix" << endl; //���� ��׺�ĳ���
	int n;
	cin >> n;

	vector<string> str_v; //ֱ�ӱ��� ���в�ͬ�� n -letter suffix
	vector<suffix> struct_v; //���� ���� n -letter suffix�Ľṹ

	group(n, struct_v, str_v, word_v);
	
	sort(struct_v.begin(), struct_v.end(), myless);

	for (int i = struct_v.size()-1; i > struct_v.size() - 11; i--) {
		cout << "top" << struct_v.size()-i << "  " << struct_v[i].str << " number is" << struct_v[i].num<<endl;
	}

	cout << "Now you can query a n-letter suffix by inputting the  suffix"<<endl;
	while (true) {
		string tmp;
		cin >> tmp;
		if (tmp == "quit") break;
		int pos;
		for (int i = 0; i < struct_v.size(); i++) {
			if (struct_v[i].str == tmp) {
				pos = i;
				break;
			}				
		}
		sort(struct_v[pos].member.begin(), struct_v[pos].member.end());
		for (int i = struct_v[pos].member.size()-1; i >=0; i--) {
			cout << struct_v[pos].member[i] << " ";
		}
		cout << endl << "Now you can query next(input quit to quit)";
	}

	system("PAUSE");
}