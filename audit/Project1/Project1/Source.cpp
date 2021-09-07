#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

bool myFunc(string &s1, string &s2)
{
	return s1[0] < s2[0];
}

void output(const vector<string> &str)
{
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i] << endl;
	}
	cout << endl;
}

int main()
{
	vector<string>str;
	string tmp;
	ifstream in;
	in.open("input.txt", ios_base::in);
	while (getline(in, tmp))
	{
		tmp[0] = tolower(tmp[0]);
		str.push_back(tmp);
	}
	cout << "The original text:" << endl<<"===========================================================================> "<<endl;
	output(str);
	sort(str.begin(), str.end(), [](string& s1, string& s2) 
		{
			return s1.length() < s2.length(); 
		}
	);
	auto last = unique(str.begin(), str.end());
	str.erase(last, str.end());
	cout << "Sorted text:" << endl << "============================================================================>" << endl;
	output(str);
	sort(str.begin(), str.end(), myFunc);
	cout << "Sorted text:" << endl << "============================================================================>" << endl;
	output(str);
	cout << endl;
	system("pause");
	return 0;
}