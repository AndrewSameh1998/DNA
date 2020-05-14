#include <iostream>
#include <omp.h>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void main()
{
	string line;
	string s;
	ifstream mf("D:\\College\\Semester 8\\Distributed Computing\\Final Project\\InputSeq.dat.txt");
	if (mf.is_open())
	{
		while (getline(mf, line))
		{
			s += line;
			//cout << line << '\n';
		}
		mf.close();
	}
	else
	{
		cout << "Error";
	}
	for (int i = 0; i < 1; i++)
	{
		cout << s << '\n';
	}
}