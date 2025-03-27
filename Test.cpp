#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string path = "D:\\students.txt";

string createPersonName();
unsigned createPersonAge();
unsigned createPersonMark();
void writeInfoAboutPersonInFile(int number, string name, unsigned age, unsigned mark);
int proverka();
void showInfo();

class Student
{
public:
	string name;
	unsigned age;
	unsigned mark;
};

int main()
{
	while (true)
	{
		string guess;
		cout << "You want add Student (add) or show info about Student (show) ? If you want exit write (exit).\n";
		cin >> guess;
		cout << endl;
		if (guess == "add")
		{
			unsigned amountPeople;
			cout << "How people? ";
			cin >> amountPeople;

			for (int i = 0; i < amountPeople; i++)
			{
				Student person;
				int res = proverka();
				person.name = createPersonName();
				person.age = createPersonAge();
				person.mark = createPersonMark();
				writeInfoAboutPersonInFile(res, person.name, person.age, person.mark);
				cout << endl;
			}
		}
		else if (guess == "show")
		{
			showInfo();
		}
		else if (guess == "exit")
		{
			cout << "Closed program...";
			break;
		}
		else
		{
			cout << "Wrong choice";
			continue;
		}
	}
}

string createPersonName()
{
	string name;
	cout << "Enter student name: ";
	cin >> name;
	return name;
}

unsigned createPersonAge()
{
	unsigned age;
	cout << "Enter age: ";
	cin >> age;
	return age;
}

unsigned createPersonMark()
{
	unsigned mark;
	cout << "Enter people mark: ";
	cin >> mark;
	return mark;
}

void writeInfoAboutPersonInFile(int number, string name, unsigned age, unsigned mark)
{
	ofstream file(path, ios::app);
	if (!file.is_open())
	{
		cerr << "File is not open!" << endl;
		return;
	}
	else
	{
		file << "Student number " << number + 1;
		for (int i = 0; i < 3; i++)
		{
			file << endl;
			switch (i)
			{
			case 0:
				file << "Name: " << name;
				break;
			case 1:
				file << "Age: " << age;
				break;
			case 2:
				file << "Mark: " << mark;
				break;
			}
		}
		file << endl << endl;
		file.close();
	}
}

int proverka()
{
	ifstream file(path);
	string currentline;
	string lastline;
	const int SIZE = 20;

	if (!file.is_open())
	{
		cerr << "File is not open!" << endl;
		return -1;
	}
	else
	{
		while (getline(file, currentline))
		{
			if (currentline.find("Student") != string::npos)
			{
				lastline = currentline;
			}
		}
	}


	if (lastline.empty())
	{
		return 0;
	}
	else
	{
		vector<char> lastVEC;
		for (size_t i = 0; i < lastline.length(); i++)
		{
			lastVEC.push_back(lastline[i]);
		}

		file.close();
		return lastVEC.back() - '0';
	}
}

void showInfo()
{
	string number;
	cout << "Enter Student number for show info about him: ";
	cin >> number;
	cout << endl;

	ifstream file(path);
	if (!file.is_open())
	{
		cerr << "File is not open!" << endl;
		return;
	}
	else
	{
		string currentLine;
		int perek = 0;
		string name;
		int age;
		int mark;

		while (getline(file, currentLine))
		{
			if (perek == 1 or perek == 2 or perek == 3)
			{
				size_t lastSpace = currentLine.find_last_of(' ');
				switch (perek)
				{
				case 1:
					cout << "Student " << currentLine.substr(lastSpace + 1);
					break;
				case 2:
					cout << " is " << currentLine.substr(lastSpace + 1) << " years older";
					break;
				case 3:
					cout << " and has a grade of " << currentLine.substr(lastSpace + 1) << endl;;
					break;
				}

				perek++;
				continue;
			}
			else if (perek == 4)
			{
				break;
			}
			else if (currentLine == "Student number " + number)
			{
				perek = 1;
				continue;
			}
		}
		cout << endl;
		file.close();
		return;
	}
}