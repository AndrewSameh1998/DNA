#include <iostream>
#include <omp.h>
#include <fstream>
#include <cstring>
#include <string>
#include <Bits.h>

using namespace std;

void print(float freq[]);

int x = 0;
int y = 0;

string readfile()
{
	string line;
	string s;
	ifstream mf("D:\\College\\Semester 8\\Distributed Computing\\Final Project\\DNA\\InputSeq.dat.txt");
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
	//cout << s << '\n';
	return s;
}

void removedigits(char* c_p)
{
	string s = readfile();
	int n = s.length();
	char c_arr[102248];
	strcpy_s(c_arr, s.c_str());
	for (int i = 0; i < n-1; i++)
	{
		if (isdigit(c_arr[i]))
		{
			continue;
		}
		else if(isalpha(c_arr[i]))
		{
			c_p[i] = c_arr[i];
			//cout << c_p[i];
		}
	}
}

void Check_Amino(char * c_p,string* amino)
{
	while (c_p[x] != NULL)
	{
		switch (c_p[x])
		{
		case 't':
			switch (c_p[x + 1])
			{
			case 't':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Phe";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Leu";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}

			case 'c':
				amino[y] = "Ser";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				continue;
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Tyr";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					continue;
				}
				else
				{
					amino[y] = "Stop";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					continue;
				}
			case 'g':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Cys";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					continue;
				}
				else if (c_p[x + 2] == 'a')
				{
					amino[y] = "Stop";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					continue;
				}
				else
				{
					amino[y] = "Trp";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					continue;
				}
			}
		case 'c':
			switch (c_p[x + 1])
			{
			case 't':
			{
				amino[y] = "Leu";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			case 'c':
			{
				amino[y] = "Pro";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "His";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Gin";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
			case 'g':
			{
				amino[y] = "Arg";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			}
		case 'a':
			switch (c_p[x + 1])
			{
			case 't':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c' || c_p[x + 2] == 'a')
				{
					amino[y] = "Ile";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Met";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
			case 'c':
			{
				amino[y] = "Thr";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Asn";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Lys";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
			case 'g':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c' || c_p[x + 2] == 'a')
				{
					amino[y] = "Ser";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Arg";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
			}
		case 'g':
			switch (c_p[x + 1])
			{
			case 't':
			{
				amino[y] = "Val";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			case 'c':
			{
				amino[y] = "Ala";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Asp";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Glu";
					//cout << amino[y] << endl;
					y++;
					x += 3;
					break;
				}
			case 'g':
			{
				amino[y] = "Gly";
				//cout << amino[y] << endl;
				y++;
				x += 3;
				break;
			}
			}
		}
		x++;
	}
}

void frequency(string* amino, int y) 
{
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0, 
		Met = 0, Thr = 0,Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;
	float freq_arr[21] = {};

	for (int j = 0; j <= y; j++)
	{
		//cout << amino[j] << endl;

		if (amino[j] == "Phe")
			Phe++;
		if (amino[j] == "Leu")
			Leu++;
		if (amino[j] == "Ser")
			Ser++;
		if (amino[j] == "Tyr")
			Tyr++;
		if (amino[j] == "Stop")
			Stop++;
		if (amino[j] == "Cys")
			Cys++;
		if (amino[j] == "Trp")
			Trp++;
		if (amino[j] == "Pro")
			Pro++;
		if (amino[j] == "His")
			His++;
		if (amino[j] == "Gin")
			Gin++;
		if (amino[j] == "Arg")
			Arg++;
		if (amino[j] == "Ile")
			Ile++;
		if (amino[j] == "Met")
			Met++;
		if (amino[j] == "Thr")
			Thr++;
		if (amino[j] == "Asn")
			Asn++;
		if (amino[j] == "Lys")
			Lys++;
		if (amino[j] == "Val")
			Val++;
		if (amino[j] == "Ala")
			Ala++;
		if (amino[j] == "Asp")
			Asp++;
		if (amino[j] == "Glu")
			Glu++;
		if (amino[j] == "Gly")
			Gly++;
	}
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };
	for (int i = 0; i < 21; i++)
	{
		freq_arr[i] = ((float)(amino_arr[i]) / (float)y) * 100;
		//cout << freq_arr[i] << endl;
	}
	print(freq_arr);
}

void print(float freq[])
{
	string names[21] = { "Phe", "Leu", "Ser", "Tyr", "Stop", "Cys", "Trp", "Pro", "His", "Gin", "Arg", "Ile", "Met", "Thr", "Asn", "Lys", "Val", "Ala", "Asp", "Glu", "Gly" };
	for (int i = 0; i < 21; i++)
	{
		cout << names[i] << " Amino Acid Frequency : " << freq[i] << endl;
	}
}

void main()
{
	
	int size = 0;
	char* c_p = new char[102248];
	string* amino = new string[24600];
	removedigits(c_p);
	Check_Amino(c_p, amino);
	// y = 24526
	// X = 102252
	cout << x << endl;
	cout << y << endl;
	frequency(amino, y);
}