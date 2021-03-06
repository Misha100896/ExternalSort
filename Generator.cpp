#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int stringToInt(char* num)
{
	stringstream str(num);
	int x;
	str >> x;
	return x;
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "Usage: Generator.exe Test.txt countLines sizeLine";
		return 0;
	}

	int countLines = stringToInt(argv[2]);
	int sizeLine = stringToInt(argv[3]);
	ofstream cout(argv[1]);
	for (int i = 0; i < countLines; ++i)
	{
		for (int j = 0; j < sizeLine; ++j)
		{
			cout << char(rand() % 26 + 'a');
		}
		cout << '\n';
	}
	return 0;
}