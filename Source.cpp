#include <iostream>
#include <omp.h>
#include <fstream>
#include <cstring>
#include <string>
#include <Bits.h>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std::chrono;

void print(float freq[], float freq_p[], int number_arr[]);

int x = 0;
int y = 0;

string readfile()
{
	string line;
	string s;
	ifstream mf("../InputSeq.dat.txt");
	if (mf.is_open())
	{
		while (getline(mf, line))
		{
			s += line;
		}
		mf.close();
	}
	else
	{
		cout << "Error";
	}
	return s;
}

void removedigits(char* c_p)
{
	string s = readfile();
	int x = 0;
	int n = s.length();
	char c_arr[102248];
	strcpy_s(c_arr, s.c_str());
	for (int i = 0; i < n - 1; i++)
	{
		if (isalpha(c_arr[i]))
		{
			c_p[x] = c_arr[i];
			x++;
		}
	}
}

void Check_Amino(char* c_p, string* amino)
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
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Leu";
					y++;
					x += 3;
					break;
				}

			case 'c':
				amino[y] = "Ser";
				y++;
				x += 3;
				continue;
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Tyr";
					y++;
					x += 3;
					continue;
				}
				else
				{
					amino[y] = "Stop";
					y++;
					x += 3;
					continue;
				}
			case 'g':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Cys";
					y++;
					x += 3;
					continue;
				}
				else if (c_p[x + 2] == 'a')
				{
					amino[y] = "Stop";
					y++;
					x += 3;
					continue;
				}
				else
				{
					amino[y] = "Trp";
					y++;
					x += 3;
					continue;
				}
			}
			break;
		case 'c':
			switch (c_p[x + 1])
			{
			case 't':
			{
				amino[y] = "Leu";
				y++;
				x += 3;
				break;
			}
			case 'c':
			{
				amino[y] = "Pro";
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "His";
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Gin";
					y++;
					x += 3;
					break;
				}
			case 'g':
			{
				amino[y] = "Arg";
				y++;
				x += 3;
				break;
			}
			}
			break;
		case 'a':
			switch (c_p[x + 1])
			{
			case 't':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c' || c_p[x + 2] == 'a')
				{
					amino[y] = "Ile";
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Met";
					y++;
					x += 3;
					break;
				}
			case 'c':
			{
				amino[y] = "Thr";
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Asn";
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Lys";
					y++;
					x += 3;
					break;
				}
			case 'g':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c' || c_p[x + 2] == 'a')
				{
					amino[y] = "Ser";
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Arg";
					y++;
					x += 3;
					break;
				}
			}
			break;
		case 'g':
			switch (c_p[x + 1])
			{
			case 't':
			{
				amino[y] = "Val";
				y++;
				x += 3;
				break;
			}
			case 'c':
			{
				amino[y] = "Ala";
				y++;
				x += 3;
				break;
			}
			case 'a':
				if (c_p[x + 2] == 't' || c_p[x + 2] == 'c')
				{
					amino[y] = "Asp";
					y++;
					x += 3;
					break;
				}
				else
				{
					amino[y] = "Glu";
					y++;
					x += 3;
					break;
				}
			case 'g':
			{
				amino[y] = "Gly";
				y++;
				x += 3;
				break;
			}
			}
			break;
		}
	}
}

void frequency(string* amino, int y)
{
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};

	for (int j = 0; j <= y; j++)
	{
		if (amino[j] == "Phe")
			amino_arr[0]++;
		if (amino[j] == "Leu")
			amino_arr[1]++;
		if (amino[j] == "Ser")
			amino_arr[2]++;
		if (amino[j] == "Tyr")
			amino_arr[3]++;
		if (amino[j] == "Stop")
			amino_arr[4]++;
		if (amino[j] == "Cys")
			amino_arr[5]++;
		if (amino[j] == "Trp")
			amino_arr[6]++;
		if (amino[j] == "Pro")
			amino_arr[7]++;
		if (amino[j] == "His")
			amino_arr[8]++;
		if (amino[j] == "Gin")
			amino_arr[9]++;
		if (amino[j] == "Arg")
			amino_arr[10]++;
		if (amino[j] == "Ile")
			amino_arr[11]++;
		if (amino[j] == "Met")
			amino_arr[12]++;
		if (amino[j] == "Thr")
			amino_arr[13]++;
		if (amino[j] == "Asn")
			amino_arr[14]++;
		if (amino[j] == "Lys")
			amino_arr[15]++;
		if (amino[j] == "Val")
			amino_arr[16]++;
		if (amino[j] == "Ala")
			amino_arr[17]++;
		if (amino[j] == "Asp")
			amino_arr[18]++;
		if (amino[j] == "Glu")
			amino_arr[19]++;
		if (amino[j] == "Gly")
			amino_arr[20]++;
	}

	for (int i = 0; i < 21; i++)
	{
		freq_arr[i] = (((float)(amino_arr[i]) / (float)y));
		freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
	}
	print(freq_arr, freq_arr_percent, amino_arr);
}

void frequency_parallel(string* amino, int y)
{
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;

	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};

#pragma omp parallel
	{
#pragma omp for schedule(guided,100)
		for (int j = 0; j <= y; j++)
		{
			if (amino[j] == "Phe")
#pragma omp atomic
				amino_arr[0]++;
			if (amino[j] == "Leu")
#pragma omp atomic
				amino_arr[1]++;
			if (amino[j] == "Ser")
#pragma omp atomic
				amino_arr[2]++;
			if (amino[j] == "Tyr")
#pragma omp atomic
				amino_arr[3]++;
			if (amino[j] == "Stop")
#pragma omp atomic
				amino_arr[4]++;
			if (amino[j] == "Cys")
#pragma omp atomic
				amino_arr[5]++;
			if (amino[j] == "Trp")
#pragma omp atomic
				amino_arr[6]++;
			if (amino[j] == "Pro")
#pragma omp atomic
				amino_arr[7]++;
			if (amino[j] == "His")
#pragma omp atomic
				amino_arr[8]++;
			if (amino[j] == "Gin")
#pragma omp atomic
				amino_arr[9]++;
			if (amino[j] == "Arg")
#pragma omp atomic
				amino_arr[10]++;
			if (amino[j] == "Ile")
#pragma omp atomic
				amino_arr[11]++;
			if (amino[j] == "Met")
#pragma omp atomic
				amino_arr[12]++;
			if (amino[j] == "Thr")
#pragma omp atomic
				amino_arr[13]++;
			if (amino[j] == "Asn")
#pragma omp atomic
				amino_arr[14]++;
			if (amino[j] == "Lys")
#pragma omp atomic
				amino_arr[15]++;
			if (amino[j] == "Val")
#pragma omp atomic
				amino_arr[16]++;
			if (amino[j] == "Ala")
#pragma omp atomic
				amino_arr[17]++;
			if (amino[j] == "Asp")
#pragma omp atomic
				amino_arr[18]++;
			if (amino[j] == "Glu")
#pragma omp atomic
				amino_arr[19]++;
			if (amino[j] == "Gly")
#pragma omp atomic
				amino_arr[20]++;
		}
#pragma omp for schedule(guided,3)
		for (int i = 0; i < 21; i++)
		{
			freq_arr[i] = ((float)(amino_arr[i]) / (float)y);
			freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
		}
	}

	print(freq_arr, freq_arr_percent, amino_arr);
}

void frequency_sections_2(string* amino, int y)
{
	omp_set_num_threads(2);
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Phe")
#pragma omp atomic
						amino_arr[0]++;
					if (amino[j] == "Leu")
#pragma omp atomic
						amino_arr[1]++;
					if (amino[j] == "Ser")
#pragma omp atomic
						amino_arr[2]++;
					if (amino[j] == "Tyr")
#pragma omp atomic
						amino_arr[3]++;
					if (amino[j] == "Stop")
#pragma omp atomic
						amino_arr[4]++;
					if (amino[j] == "Cys")
#pragma omp atomic
						amino_arr[5]++;
					if (amino[j] == "Trp")
#pragma omp atomic
						amino_arr[6]++;
					if (amino[j] == "Pro")
#pragma omp atomic
						amino_arr[7]++;
					if (amino[j] == "His")
#pragma omp atomic
						amino_arr[8]++;
					if (amino[j] == "Gin")
#pragma omp atomic
						amino_arr[9]++;

				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Arg")
#pragma omp atomic
						amino_arr[10]++;
					if (amino[j] == "Ile")
#pragma omp atomic
						amino_arr[11]++;
					if (amino[j] == "Met")
#pragma omp atomic
						amino_arr[12]++;
					if (amino[j] == "Thr")
#pragma omp atomic
						amino_arr[13]++;
					if (amino[j] == "Asn")
#pragma omp atomic
						amino_arr[14]++;
					if (amino[j] == "Lys")
#pragma omp atomic
						amino_arr[15]++;
					if (amino[j] == "Val")
#pragma omp atomic
						amino_arr[16]++;
					if (amino[j] == "Ala")
#pragma omp atomic
						amino_arr[17]++;
					if (amino[j] == "Asp")
#pragma omp atomic
						amino_arr[18]++;
					if (amino[j] == "Glu")
#pragma omp atomic
						amino_arr[19]++;
					if (amino[j] == "Gly")
#pragma omp atomic
						amino_arr[20]++;
				}
			}
		}
#pragma omp parallel
		{
#pragma omp for schedule(dynamic,3)
			for (int i = 0; i < 21; i++)
			{
				freq_arr[i] = ((float)(amino_arr[i]) / (float)y);
				freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
			}
		}
	}
	print(freq_arr, freq_arr_percent, amino_arr);
}

void frequency_sections_4(string* amino, int y)
{
	omp_set_num_threads(4);
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Phe")
#pragma omp atomic
						amino_arr[0]++;
					if (amino[j] == "Leu")
#pragma omp atomic
						amino_arr[1]++;
					if (amino[j] == "Ser")
#pragma omp atomic
						amino_arr[2]++;
					if (amino[j] == "Tyr")
#pragma omp atomic
						amino_arr[3]++;
					if (amino[j] == "Stop")
#pragma omp atomic
						amino_arr[4]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Cys")
#pragma omp atomic
						amino_arr[5]++;
					if (amino[j] == "Trp")
#pragma omp atomic
						amino_arr[6]++;
					if (amino[j] == "Pro")
#pragma omp atomic
						amino_arr[7]++;
					if (amino[j] == "His")
#pragma omp atomic
						amino_arr[8]++;
					if (amino[j] == "Gin")
#pragma omp atomic
						amino_arr[9]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Arg")
#pragma omp atomic
						amino_arr[10]++;
					if (amino[j] == "Ile")
#pragma omp atomic
						amino_arr[11]++;
					if (amino[j] == "Met")
#pragma omp atomic
						amino_arr[12]++;
					if (amino[j] == "Thr")
#pragma omp atomic
						amino_arr[13]++;
					if (amino[j] == "Asn")
#pragma omp atomic
						amino_arr[14]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Lys")
#pragma omp atomic
						amino_arr[15]++;
					if (amino[j] == "Val")
#pragma omp atomic
						amino_arr[16]++;
					if (amino[j] == "Ala")
#pragma omp atomic
						amino_arr[17]++;
					if (amino[j] == "Asp")
#pragma omp atomic
						amino_arr[18]++;
					if (amino[j] == "Glu")
#pragma omp atomic
						amino_arr[19]++;
					if (amino[j] == "Gly")
#pragma omp atomic
						amino_arr[20]++;
				}
			}

		}
#pragma omp parallel
		{
#pragma omp for schedule(dynamic,3)
			for (int i = 0; i < 21; i++)
			{
				freq_arr[i] = ((float)(amino_arr[i]) / (float)y);
				freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
			}
		}
	}
	print(freq_arr, freq_arr_percent, amino_arr);
}

void frequency_sections_8(string* amino, int y)
{
	omp_set_num_threads(8);
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Phe")
#pragma omp atomic
						amino_arr[0]++;
					if (amino[j] == "Leu")
#pragma omp atomic
						amino_arr[1]++;
					if (amino[j] == "Ser")
#pragma omp atomic
						amino_arr[2]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Tyr")
#pragma omp atomic
						amino_arr[3]++;
					if (amino[j] == "Stop")
#pragma omp atomic
						amino_arr[4]++;
					if (amino[j] == "Cys")
#pragma omp atomic
						amino_arr[5]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{

					if (amino[j] == "Trp")
#pragma omp atomic
						amino_arr[6]++;
					if (amino[j] == "Pro")
#pragma omp atomic
						amino_arr[7]++;
					if (amino[j] == "His")
#pragma omp atomic
						amino_arr[8]++;

				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Gin")
#pragma omp atomic
						amino_arr[9]++;
					if (amino[j] == "Arg")
#pragma omp atomic
						amino_arr[10]++;
					if (amino[j] == "Ile")
#pragma omp atomic
						amino_arr[11]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{

					if (amino[j] == "Met")
#pragma omp atomic
						amino_arr[12]++;
					if (amino[j] == "Thr")
#pragma omp atomic
						amino_arr[13]++;
					if (amino[j] == "Asn")
#pragma omp atomic
						amino_arr[14]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Lys")
#pragma omp atomic
						amino_arr[15]++;
					if (amino[j] == "Val")
#pragma omp atomic
						amino_arr[16]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Ala")
#pragma omp atomic
						amino_arr[17]++;
					if (amino[j] == "Asp")
#pragma omp atomic
						amino_arr[18]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Glu")
#pragma omp atomic
						amino_arr[19]++;
					if (amino[j] == "Gly")
#pragma omp atomic
						amino_arr[20]++;
				}
			}
		}
	}
#pragma omp parallel
	{
#pragma omp for schedule(dynamic,3)
		for (int i = 0; i < 21; i++)
		{
			freq_arr[i] = ((float)(amino_arr[i]) / (float)y);
			freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
		}
	}
	print(freq_arr, freq_arr_percent, amino_arr);
}

void frequency_sections_16(string* amino, int y)
{
	omp_set_num_threads(16);
	int Phe = 0, Leu = 0, Ser = 0, Tyr = 0, Stop = 0, Cys = 0, Trp = 0, Pro = 0, His = 0, Gin = 0, Arg = 0, Ile = 0,
		Met = 0, Thr = 0, Asn = 0, Lys = 0, Val = 0, Ala = 0, Asp = 0, Glu = 0, Gly = 0;

	float freq_arr[21] = {};
	float freq_arr_percent[21] = {};
	int amino_arr[] = { Phe, Leu, Ser, Tyr, Stop, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asn, Lys, Val, Ala, Asp, Glu, Gly };

#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Phe")
#pragma omp atomic
						amino_arr[0]++;
					if (amino[j] == "Leu")
#pragma omp atomic
						amino_arr[1]++;

				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Ser")
#pragma omp atomic
						amino_arr[2]++;
					if (amino[j] == "Tyr")
#pragma omp atomic
						amino_arr[3]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Stop")
#pragma omp atomic
						amino_arr[4]++;
					if (amino[j] == "Cys")
#pragma omp atomic
						amino_arr[5]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Trp")
#pragma omp atomic
						amino_arr[6]++;
					if (amino[j] == "Pro")
#pragma omp atomic
						amino_arr[7]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "His")
#pragma omp atomic
						amino_arr[8]++;
					if (amino[j] == "Gin")
#pragma omp atomic
						amino_arr[9]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Arg")
#pragma omp atomic
						amino_arr[10]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Ile")
#pragma omp atomic
						amino_arr[11]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Met")
#pragma omp atomic
						amino_arr[12]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Thr")
#pragma omp atomic
						amino_arr[13]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Asn")
#pragma omp atomic
						amino_arr[14]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Lys")
#pragma omp atomic
						amino_arr[15]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Val")
#pragma omp atomic
						amino_arr[16]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Ala")
#pragma omp atomic
						amino_arr[17]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Asp")
#pragma omp atomic
						amino_arr[18]++;
				}
			}

#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Glu")
#pragma omp atomic
						amino_arr[19]++;
				}
			}
#pragma omp section
			{
				for (int j = 0; j <= y; j++)
				{
					if (amino[j] == "Gly")
#pragma omp atomic
						amino_arr[20]++;

				}
			}

		}
	}
#pragma omp parallel
	{
#pragma omp for schedule(dynamic,3)
		for (int i = 0; i < 21; i++)
		{
			freq_arr[i] = ((float)(amino_arr[i]) / (float)y);
			freq_arr_percent[i] = ((float)(amino_arr[i]) / (float)y) * 100;
		}
	}
	print(freq_arr, freq_arr_percent, amino_arr);
}

void print(float freq[], float freq_p[], int number_arr[])
{
	string names[21] = { "Phe", "Leu", "Ser", "Tyr", "Stop", "Cys", "Trp", "Pro", "His", "Gin", "Arg", "Ile", "Met", "Thr", "Asn", "Lys", "Val", "Ala", "Asp", "Glu", "Gly" };
	for (int i = 0; i < 21; i++)
	{
		cout << names[i] << " Amino Acid Frequency Percentage : " << freq_p[i] << ' ' << '%' << endl;
		cout << names[i] << " Amino Acid Number of instances : " << number_arr[i] << endl;
		cout << names[i] << " Amino Acid Frequency   : " << freq[i] << endl;

	}
}

void sequential(string* amino)
{
	auto start1 = high_resolution_clock::now();
	frequency(amino, y);
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Time taken to check frequency Sequential : " << (float)(duration1.count()) / 1000000 << " Seconds" << endl;
}

void Loop_level(string* amino)
{
	omp_set_num_threads(16);
	auto start2 = high_resolution_clock::now();
	frequency_parallel(amino, y);
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "Time taken to check frequency Loop Level Parallel : " << (float)(duration2.count()) / 1000000 << " Seconds" << endl;
}

void Sections_2(string* amino)
{
	auto start3 = high_resolution_clock::now();
	frequency_sections_2(amino, y);
	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);
	cout << "Time taken to check frequency 2 Sections Parallel: " << (float)(duration3.count()) / 1000000 << " Seconds" << endl;
}

void Sections_4(string* amino)
{
	auto start4 = high_resolution_clock::now();
	frequency_sections_4(amino, y);
	auto stop4 = high_resolution_clock::now();
	auto duration4 = duration_cast<microseconds>(stop4 - start4);
	cout << "Time taken to check frequency 4 Sections Parallel: " << (float)(duration4.count()) / 1000000 << " Seconds" << endl;
}

void Sections_8(string* amino)
{
	auto start5 = high_resolution_clock::now();
	frequency_sections_8(amino, y);
	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast<microseconds>(stop5 - start5);
	cout << "Time taken to check frequency 8 Sections Parallel: " << (float)(duration5.count()) / 1000000 << " Seconds" << endl;
}

void Sections_16(string* amino)
{
	auto start6 = high_resolution_clock::now();
	frequency_sections_16(amino, y);
	auto stop6 = high_resolution_clock::now();
	auto duration6 = duration_cast<microseconds>(stop6 - start6);
	cout << "Time taken to check frequency 16 Sections Parallel: " << (float)(duration6.count()) / 1000000 << " Seconds" << endl;
}

void main()
{
	int size = 0;
	char* c_p = new char[81781];
	string* amino = new string[27262];
	removedigits(c_p);
	Check_Amino(c_p, amino);
	//-------------------------------------------Sequential Part-------------------------------------------------------
	sequential(amino);
	//-------------------------------------------Loop Level Parallelism------------------------------------------------
	Loop_level(amino);
	//-----------------------------------------2 Sections--------------------------------------------------------------
	Sections_2(amino);
	//-----------------------------------------4 Sections--------------------------------------------------------------
	Sections_4(amino);
	//-----------------------------------------8 Sections---------------------------------------------------------------
	Sections_8(amino);
	//-----------------------------------------16 Sections--------------------------------------------------------------
	Sections_16(amino);
}