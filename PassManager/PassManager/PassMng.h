#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <Windows.h>
#include <locale>

using namespace std;

class PassMngr
{
public:
	struct fileDATA{
		string pswd, comment, name;
		int id;
	};
	void firstMassage() {
		cout << "\n\n\n\t==========PASSWOR MANAGER==========\n";
	}
	int initFile()
	{
		data.open("C:/Users/gutro/dataFile.txt");
		if (!data.is_open())
		{
			cout << "\n#WARNING! Cannot open dataFile!";
		}
		else
		{
			SetConsoleTextAttribute(hwnd, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\n#File is open!";
			SetConsoleTextAttribute(hwnd, 0x0033 | 0x0040);
		}
		while (!data.eof()) //получает количество записанных учеток в файле
		{
			string tmp;
			data >> tmp;
			if (tmp[0] == '#')
				sizeFile++;
		}
		try {
			d = new fileDATA[sizeFile];
		}
		catch(const exception& err)
		{
			cout << "\nERROR! " << err.what() << endl;
		}
		data.close();
		return 1;
	}
	int get_data()
	{
		data.open("C:/Users/gutro/dataFile.txt");
		int position, it = 0;
		string tmp;
		while (!data.eof())
		{
			try 
			{
				data >> tmp;		
				tmp.erase(0, 1);
				d[it].id = stoi(tmp);
			}
			catch (const exception& err)
			{
				cout << "\nERROR! " << err.what() << endl;
			}

			data >> d[it].name >> d[it].pswd;
			while (1)
			{
				data >> tmp;
				if (tmp[0] == '#')
				{
					position = data.tellg();
					data.seekg(position - 2);
					break;
				}
				else if (data.eof() == true)
					break;
				d[it].comment += " " + tmp;
			}
			it++;
		}
		return 1;
	}
	void print_data()
	{
		//SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		for (int i = 0; i < sizeFile; i++)
		{
			cout << "\n-----------------------------------------";
			cout << "\nID: " << d[i].id << "\nNAME: " << d[i].name << "\nPASS: " << d[i].pswd << "\nCOMMENT: " << d[i].comment;
		}
	}

private:
	fstream data;
	int sizeFile;
	fileDATA *d;
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	
};