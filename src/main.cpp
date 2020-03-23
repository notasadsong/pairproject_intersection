#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<vector>
#include<utility>
#include <regex>
#include "core.h"
#include<windows.h>

#pragma comment(lib, "core.lib")

using namespace std;

void getInput(vector<Line>* lines, vector<Circle>* circles, int argc, char* argv[])
{
	ifstream input;
	int n;

	try {
		if (argc != 5 || strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-o") != 0 || !regex_match(argv[2], regex("\\S+\\.txt")) || !regex_match(argv[4], regex("\\S+\\.txt")))
		{
			throw "command line parameter error you need *.exe -i *.txt -o *.txt";
		}

	}
	catch (const char* msg) {
		cerr << msg << endl;
		return;
	}
	
	input = ifstream(argv[2]);


	string l;
	getline(input, l);
	n = atoi(l.c_str());
	regex reg("(\\+|-)?\\d+");//整数
	try {
		if (!regex_match(l, reg) || n < 1)
		{
			throw "几何对象数目应为正整数";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return;
	}

	char op;
	int a, b, c, d;
	int i = 0;
	while (getline(input, l))
	{
		if (i >= n)
		{
			break;
		}
		if (l == "")
		{
			continue;
		}
		i++;
		vector<string> res;
		string result;
		stringstream ss(l);
		while (ss >> result)
		{
			res.push_back(result);
		}
		if (res.size() != 0 && (res[0] == "L" || res[0] == "R" || res[0] == "S"))
		{
			op = res[0][0];
			try {
				if (res.size() != 5)
				{
					throw"L,R,S只能4个参数";
				}
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}

			a = atoi(res[1].c_str());
			b = atoi(res[2].c_str());
			c = atoi(res[3].c_str());
			d = atoi(res[4].c_str());
			
			try {
				if (!regex_match(res[1], reg) || !regex_match(res[2], reg) || !regex_match(res[3], reg) || !regex_match(res[4], reg))
				{
					throw"输入的几何图形的参数应为整数";
				}
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}
			try {
				if (a > 100000 || a < -100000 || b > 100000 || b < -100000 || c > 100000 || c < -100000 || d > 100000 || d < -100000)
				{
					throw "坐标范围超限";
				}

			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}
			try {
				if (a == c && b == d)
				{
					throw "直线定义中两点重合";
				}

			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}

			Line l((double)a, (double)b, (double)c, (double)d, op);
			lines->push_back(l);
		}
		else if (res.size() != 0 && res[0] == "C")
		{
			op = res[0][0];
			try {
				if (res.size() != 4)
				{
					throw"C只能为3个参数";
				}
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}

			a = atoi(res[1].c_str());
			b = atoi(res[2].c_str());
			d = atoi(res[3].c_str());

			try {
				if (!regex_match(res[1], reg) || !regex_match(res[2], reg) || !regex_match(res[3], reg))
				{
					throw"输入的几何图形的参数应为整数";
				}
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}

			try {
				if (a > 100000 || a < -100000 || b > 100000 || b < -100000 || d > 100000 || d < -100000)
				{
					throw "坐标范围超限";
				}

			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}

			try {
				if (d <= 0)
				{
					throw "圆半径不为正数";
				}

			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}
			Circle c((double)a, (double)b, (double)d);
			circles->push_back(c);
		}
		else
		{
			try {
				throw"几何图形只能为L,R,S,C";
			}
			catch (const char* msg) {
				cerr << msg << endl;
				return;
			}
		}
	}
	if (i < n)
	{
		try {
			throw"输入数据过少";
		}
		catch (const char* msg) {
			cerr << msg << endl;
			return;
		}
	}

}

void getIntersection(vector<Line> lines, vector<Circle> circles, set<pair<double, double>, cmp>* intersections)
{

	Solve solve;

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		for (unsigned int j = i + 1; j < lines.size(); j++)
		{
			if (lines[i].type == 'L' && lines[j].type == 'L')  solve.LLintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'R') solve.RRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'S' && lines[j].type == 'S') solve.SSintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'L') solve.LRintersect(intersections, lines[j], lines[i]);
			else if (lines[i].type == 'L' && lines[j].type == 'R') solve.LRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'L' && lines[j].type == 'S') solve.LSintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'S' && lines[j].type == 'L') solve.LSintersect(intersections, lines[j], lines[i]);
			else if (lines[i].type == 'S' && lines[j].type == 'R') solve.SRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'S') solve.SRintersect(intersections, lines[j], lines[i]);
		}
	}

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		for (unsigned int j = 0; j < circles.size(); j++)
		{
			if (lines[i].type == 'L') solve.LCintersect(intersections, lines[i], circles[j]);
			else if (lines[i].type == 'R') solve.RCintersect(intersections, lines[i], circles[j]);
			else if (lines[i].type == 'S') solve.SCintersect(intersections, lines[i], circles[j]);
		}
	}

	for (unsigned int i = 0; i < circles.size(); i++)
	{
		for (unsigned int j = i + 1; j < circles.size(); j++) solve.CCintersect(intersections, circles[i], circles[j]);
	}
}

int main(int argc, char* argv[])
{
	vector<Line> lines;
	vector<Circle> circles;
	set<pair<double, double>, cmp> intersections;

	getInput(&lines, &circles, argc, argv);

	getIntersection(lines, circles, &intersections);

	ofstream output;
	output = ofstream(argv[4]);
	output << intersections.size() << endl;
}
